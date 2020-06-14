#include "pybind11_common.hpp"

#include "form_factor.hpp"
#include "shape_model.hpp"

void init_form_factor(py::module & m);
void init_shape_model(py::module & m);

PYBIND11_MODULE (flux, m) {
  m.doc() = R"pbdoc(
flux
----

TODO
)pbdoc";

  init_form_factor(m);
  init_shape_model(m);

#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}
