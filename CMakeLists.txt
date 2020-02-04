project (flux)

cmake_minimum_required (VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)

include (GoogleTest)

find_package (Eigen3 REQUIRED NO_MODULE)
find_package (pybind11 REQUIRED)

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -Werror")
set (CMAKE_CXX_VISIBILITY_PRESET hidden)

set (FLUX_SRC_FILES
  src/form_factors.hpp
  src/form_factors.cpp
  )

pybind11_add_module (flux MODULE src/flux.cpp ${FLUX_SRC_FILES})
target_compile_definitions (flux PRIVATE USING_PYBIND11=1)
set_property (TARGET flux PROPERTY CXX_STANDARD 17)
target_link_libraries (flux PRIVATE Eigen3::Eigen)
