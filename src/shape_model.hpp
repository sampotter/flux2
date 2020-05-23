#pragma once

#include "common.hpp"

#include <embree3/rtcore.h>
RTC_NAMESPACE_OPEN

namespace Flux {

using coef_t = float;

using vec_t = Eigen::Array<coef_t, Eigen::Dynamic, 1>;

using vert_t = Eigen::Matrix<coef_t, 3, 1>;

using verts_t = Eigen::Matrix<coef_t, Eigen::Dynamic, 3, Eigen::RowMajor>;
using verts_ref_t = Eigen::Ref<verts_t>;

using index_t = int32_t;

constexpr index_t NO_INDEX = -1;

using tris_t = Eigen::Matrix<index_t, Eigen::Dynamic, 3, Eigen::RowMajor>;
using tris_ref_t = Eigen::Ref<tris_t>;

using indices_t = Eigen::Array<index_t, Eigen::Dynamic, 1>;

using index_pairs_t = Eigen::Matrix<index_t, Eigen::Dynamic, 2, Eigen::RowMajor>;

constexpr float PI = 3.14159265;

struct ShapeModel
{
  ShapeModel(verts_ref_t verts, tris_ref_t faces):
    verts {verts},
    faces {faces},
    centroids(num_faces(), 3),
    normals(num_faces(), 3),
    areas(num_faces())
  {
    for (size_t i = 0; i < num_faces(); ++i) {
      size_t i0 = faces(i, 0), i1 = faces(i, 1), i2 = faces(i, 2);
      vert_t v0 = verts.row(i0), v1 = verts.row(i1), v2 = verts.row(i2);
      centroids.row(i) = (v0 + v1 + v2)/3;
      normals.row(i) = (v1 - v0).cross(v2 - v0);
      areas(i) = normals.row(i).norm();
      normals.row(i) /= areas(i);
      areas(i) /= 2;
    }

    init_embree();
  }

  ShapeModel(verts_ref_t verts, tris_ref_t faces, verts_ref_t normals):
    verts {verts},
    faces {faces},
    centroids(num_faces(), 3),
    normals {normals},
    areas(num_faces())
  {
    for (size_t i = 0; i < num_faces(); ++i) {
      size_t i0 = faces(i, 0), i1 = faces(i, 1), i2 = faces(i, 2);
      vert_t v0 = verts.row(i0), v1 = verts.row(i1), v2 = verts.row(i2);
      centroids.row(i) = (v0 + v1 + v2)/3;
      areas(i) = (v1 - v0).cross(v2 - v0).norm()/2;
    }

    init_embree();
  }

  void init_embree() {
    device = rtcNewDevice(NULL);
    scene = rtcNewScene(device);
    geometry = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);

    // TODO: is there a way to do this without allocating more memory
    // for these buffers? It would be nice to be able to just pass
    // pointers to the memory held by verts and faces.

    vertex_buffer = rtcSetNewGeometryBuffer(
      geometry,               // geometry
      RTC_BUFFER_TYPE_VERTEX, // type
      0,                      // slot
      RTC_FORMAT_FLOAT3,      // format
      3*sizeof(coef_t),       // byteStride
      verts.rows()            // itemCount
      );
    if (rtcGetDeviceError(device) != RTC_ERROR_NONE) {
      throw std::runtime_error("error when creating vertex beffer");
    }
    memcpy(vertex_buffer, verts.data(), sizeof(coef_t)*verts.size());

    index_buffer = rtcSetNewGeometryBuffer(
      geometry,              // geometry
      RTC_BUFFER_TYPE_INDEX, // type
      0,                     // slot
      RTC_FORMAT_UINT3,      // format
      3*sizeof(index_t),     // byteStride,
      faces.rows()           // itemCount
      );
    if (rtcGetDeviceError(device) != RTC_ERROR_NONE) {
      throw std::runtime_error("error when creating index beffer");
    }
    memcpy(index_buffer, faces.data(), sizeof(index_t)*faces.size());

    rtcCommitGeometry(geometry);
    rtcAttachGeometry(scene, geometry);
    rtcReleaseGeometry(geometry);
    rtcCommitScene(scene);
  }

  ~ShapeModel() {
    rtcReleaseScene(scene);
    rtcReleaseDevice(device);
  }

  inline size_t num_verts() const {
    return verts.rows();
  }

  inline size_t num_faces() const {
    return faces.rows();
  }

  index_pairs_t same_side(size_t i0, size_t i1, size_t j0, size_t j1) {
    index_pairs_t index_pairs;
    for (size_t i = i0; i < i1; ++i) {
      vert_t pi = centroids.row(i);
      vert_t ni = normals.row(i);
      for (size_t j = j0; j < j1; ++j) {
        vert_t pj = centroids.row(j);
        vert_t nj = normals.row(j);
        vert_t nij = pi - pj;
        if (nj.dot(nij) > 0 && ni.dot(nij) < 0) {
          size_t row = index_pairs.rows();
          index_pairs.conservativeResize(index_pairs.rows() + 1, Eigen::NoChange);
          index_pairs(row, 0) = i;
          index_pairs(row, 1) = j;
        }
      }
    }
    return index_pairs;
  }

  /**
   * Shoot rays from the points in `points` in the direction of
   * `dirs`. Returns a vector of the indices of each element that was
   * hit.
   */
  indices_t intersect(verts_ref_t const & points, verts_ref_t const & dirs,
                      float tnear = 1e-5) {
    size_t i = 0;

    std::vector<RTCRayHit> rayhits(points.rows());
    for (auto & rayhit: rayhits) {
      RTCRay & ray = rayhit.ray;
      ray.org_x = points(i, 0);
      ray.org_y = points(i, 1);
      ray.org_z = points(i, 2);
      ray.tnear = tnear;
      ray.tfar = std::numeric_limits<coef_t>::infinity();
      ray.dir_x = dirs(i, 0);
      ray.dir_y = dirs(i, 1);
      ray.dir_z = dirs(i, 2);
      ray.flags = 0;
      rayhit.hit.geomID = RTC_INVALID_GEOMETRY_ID;
      ++i;
    }

    RTCIntersectContext context;
    rtcIntersect1M(
      scene,
      &context,
      &rayhits[0],
      rayhits.size(),
      sizeof(RTCRayHit)
      );

    i = 0;
    indices_t inds(points.rows());
    for (auto const & rayhit: rayhits) {
      inds[i++] = rayhit.hit.geomID != RTC_INVALID_GEOMETRY_ID ?
        rayhit.hit.primID :
        NO_INDEX;
    }

    return inds;
  }

  float ff(size_t i, size_t j) {
    vert_t pij = centroids.row(j) - centroids.row(i);
    float s_sq = pij.dot(pij);
    vert_t ni = normals.row(i);
    vert_t nj = normals.row(j);
    float Aj = areas(j);
    return fmax(0, ni.dot(pij))*fmax(0, -nj.dot(pij))*Aj/(PI*s_sq*s_sq);
  }

  vec_t mul_with_ff(size_t i0, size_t i1, size_t j0, size_t j1,
                    vec_t rhs, size_t di = 512) {
    // TODO: check arguments

    vec_t lhs(i1 - i0);
    lhs.setConstant(0.0);

    for (size_t iblk = i0; iblk < i1; iblk += di) {
      index_pairs_t ssinds = same_side(iblk, std::min(i1, iblk + di), j0, j1);

      size_t nss = ssinds.rows();

      // Gather points
      verts_t points(nss, 3);
      for (size_t k = 0; k < nss; ++k) {
        points.row(k) = centroids.row(ssinds(k, 0));
      }

      // Compute directions
      verts_t dirs(nss, 3);
      for (size_t k = 0; k < nss; ++k) {
        dirs.row(k) = centroids.row(ssinds(k, 1)) - centroids.row(ssinds(k, 0));
      }

      // Cast rays and find indices of hits
      indices_t visinds = intersect(points, dirs);

      // Do dot products between rows of form factor matrix and `rhs`
      for (size_t k = 0; k < nss; ++k) {
        size_t j = ssinds(k, 1);
        if (j == (size_t) visinds(k)) {
          size_t i = ssinds(k, 0);
          lhs(i - i0) += ff(i, j)*rhs(j - j0);
        }
      }
    }

    return lhs;
  }

  // Data coming from shape model
  verts_ref_t verts;
  tris_ref_t faces;

  // Precomputed geometry
  verts_t centroids;
  verts_t normals;
  vec_t areas;

  RTCDevice device;
  RTCScene scene;
  RTCGeometry geometry;
  void * vertex_buffer;
  void * index_buffer;
  int geom_id;
};

}
