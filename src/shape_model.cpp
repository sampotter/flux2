#include "shape_model.hpp"

#if USING_PYBIND11
#include "pybind11_common.hpp"
#endif

// TODO: ...

#if USING_PYBIND11
void init_shape_model(py::module & m) {
  py::class_<Flux::ShapeModel>(m, "ShapeModel", R"delim(
Testing testing
)delim")
    .def(py::init<Flux::verts_ref_t, Flux::faces_ref_t>())
    .def_readonly("verts", &Flux::ShapeModel::verts)
    .def_readonly("faces", &Flux::ShapeModel::faces)
    ;
}
#endif
