#include "shape_model.hpp"

#if USING_PYBIND11
#include "pybind11_common.hpp"
#endif

#if USING_PYBIND11
void init_shape_model(py::module & m) {
  py::class_<Flux::ShapeModel>(m, "ShapeModel", R"delim(
Testing testing
)delim")
    .def(py::init<Flux::verts_ref_t, Flux::tris_ref_t>())
    .def(py::init<Flux::verts_ref_t, Flux::tris_ref_t, Flux::verts_ref_t>())
    .def_readonly("verts", &Flux::ShapeModel::verts)
    .def_readonly("faces", &Flux::ShapeModel::faces)
    .def_readonly("centroids", &Flux::ShapeModel::centroids)
    .def_readonly("normals", &Flux::ShapeModel::normals)
    .def_readonly("areas", &Flux::ShapeModel::areas)
    .def("same_side", &Flux::ShapeModel::same_side, POLICY_MOVE)
    .def("intersect", &Flux::ShapeModel::intersect, POLICY_MOVE)
    .def("ff", &Flux::ShapeModel::ff)
    .def("mul_with_ff", &Flux::ShapeModel::mul_with_ff, POLICY_MOVE)
    ;
}
#endif
