#pragma once

#include <experimental/propagate_const>
#include <iostream>
#include <vector>

#include <Eigen/Dense>

namespace Flux {

template <class T>
using pimpl_ptr = std::experimental::propagate_const<std::unique_ptr<T>>;

}
