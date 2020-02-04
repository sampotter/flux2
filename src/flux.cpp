#include "pybind11_common.hpp"

#include "form_factors.hpp"

void init_form_factors(py::module & m);

PYBIND11_MODULE (flux, m) {
  m.doc() = R"pbdoc(
flux
----

TODO
)pbdoc";

  init_form_factors(m);

#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}
