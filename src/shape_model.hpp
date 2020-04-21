#pragma once

#include "common.hpp"

namespace Flux {

using verts_t = Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>;
using verts_ref_t = Eigen::Ref<verts_t>;

using index_t = int64_t;

using faces_t = Eigen::Matrix<index_t, Eigen::Dynamic, 3, Eigen::RowMajor>;
using faces_ref_t = Eigen::Ref<faces_t>;

struct ShapeModel
{
  ShapeModel(verts_ref_t verts, faces_ref_t faces):
    verts {verts}, faces {faces}
  {}

  verts_ref_t verts;
  faces_ref_t faces;
};

}
