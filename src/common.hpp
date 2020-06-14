#pragma once

#include <experimental/propagate_const>
#include <iostream>
#include <memory>
#include <vector>

#include <Eigen/Dense>

namespace Flux {

template <class T>
constexpr T infty = std::numeric_limits<T>::infinity();

template <class T>
using pimpl_ptr = std::experimental::propagate_const<std::unique_ptr<T>>;

using coef_t = float;

using vec_t = Eigen::Array<coef_t, Eigen::Dynamic, 1>;
using vec_ref_t = Eigen::Ref<vec_t>;

using vert_t = Eigen::Matrix<coef_t, 3, 1>;

using verts_t = Eigen::Matrix<coef_t, Eigen::Dynamic, 3, Eigen::RowMajor>;
using verts_ref_t = Eigen::Ref<verts_t>;

using index_t = int32_t;

constexpr index_t NO_INDEX = -1;

using tris_t = Eigen::Matrix<index_t, Eigen::Dynamic, 3, Eigen::RowMajor>;
using tris_ref_t = Eigen::Ref<tris_t>;

using indices_t = Eigen::Array<index_t, Eigen::Dynamic, 1>;

using index_pairs_t = Eigen::Matrix<index_t, Eigen::Dynamic, 2, Eigen::RowMajor>;

using permutation_t = Eigen::PermutationMatrix<Eigen::Dynamic>;

constexpr float PI = 3.14159265;

}
