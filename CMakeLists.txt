cmake_minimum_required (VERSION 3.10)

project (flux VERSION 0.1.0 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

include (GoogleTest)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package (Eigen3 REQUIRED NO_MODULE)
find_package (TBB REQUIRED)
find_package (embree 3.0 REQUIRED)
find_package (pybind11 REQUIRED)

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -Werror")
set (CMAKE_CXX_VISIBILITY_PRESET hidden)

set (FLUX_SRC_FILES
  src/form_factor.hpp
  src/form_factor.cpp
  src/shape_model.hpp
  src/shape_model.cpp
  )

pybind11_add_module (flux MODULE src/flux.cpp ${FLUX_SRC_FILES})
target_compile_definitions (flux PRIVATE USING_PYBIND11=1)
set_property (TARGET flux PROPERTY CXX_STANDARD 17)
target_link_libraries (flux PRIVATE Eigen3::Eigen)
target_link_libraries (flux PRIVATE ${EMBREE_LIBRARY})
