#pragma once

#include <array>
#include <experimental/propagate_const>
#include <iostream>
#include <memory>
#include <vector>

namespace Flux {

template <class T>
constexpr T infty = std::numeric_limits<T>::infinity();

template <class T>
using pimpl_ptr = std::experimental::propagate_const<std::unique_ptr<T>>;

}
