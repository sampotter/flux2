#include "form_factor.hpp"

#if USING_PYBIND11
#include "pybind11_common.hpp"
#endif

#if USING_PYBIND11
void init_form_factor(py::module & m) {
	py::class_<Flux::Block>(m, "Block")
		.def("depth", &Flux::Block::depth)
		.def("is_leaf", &Flux::Block::is_leaf)
		;

	py::class_<Flux::OctreeNodeBlock, Flux::Block>(m, "OctreeNodeBlock")
		;

	py::class_<Flux::LeafBlock, Flux::Block>(m, "LeafBlock")
		;

	py::class_<Flux::EmptyBlock, Flux::Block>(m, "EmptyBlock")
		;

	py::class_<Flux::ZeroBlock, Flux::Block>(m, "ZeroBlock")
		;

	py::class_<Flux::DenseBlock, Flux::Block>(m, "DenseBlock")
		;

	py::class_<Flux::SparseBlock, Flux::Block>(m, "SparseBlock")
		;

	py::class_<Flux::SvdBlock, Flux::Block>(m, "SvdBlock")
		;
}
#endif
