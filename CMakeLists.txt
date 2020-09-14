cmake_minimum_required (VERSION 3.10)

project (flux VERSION 0.1.0 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package (Armadillo REQUIRED)
find_package (TBB REQUIRED)
find_package (embree 3.0 REQUIRED)
find_package (pybind11 REQUIRED)

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -Werror")
set (CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library (flux SHARED
  main.cpp
  form_factor.hpp
  shape_model.hpp
  )

set_property (TARGET flux PROPERTY CXX_STANDARD 17)
target_include_directories (flux PRIVATE ${ARMADILLO_INCLUDE_DIRS})
target_link_libraries (flux PRIVATE ${ARMADILLO_LIBRARIES})
target_link_libraries (flux PRIVATE ${EMBREE_LIBRARY})
