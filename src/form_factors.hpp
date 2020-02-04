#pragma once

#include <Eigen/Dense>

constexpr double EPS = 1e-5;

using verts_t = Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>;
using verts_ref_t = Eigen::Ref<verts_t>;

using index_t = int64_t;

using faces_t = Eigen::Matrix<index_t, Eigen::Dynamic, 3, Eigen::RowMajor>;
using faces_ref_t = Eigen::Ref<faces_t>;

struct FormFactorBlock
{
};

struct FormFactorLeafBlock
{
};

struct FormFactorNullBlock: public FormFactorLeafBlock
{
};

struct FormFactorZeroBlock: public FormFactorLeafBlock
{
};

struct FormFactorDenseBlock: public FormFactorLeafBlock
{
};

struct FormFactorSparseBlock: public FormFactorLeafBlock
{
};

struct FormFactorCsrBlock: public FormFactorSparseBlock
{
};

struct FormFactorSvdBlock: public FormFactorLeafBlock
{
};

struct FormFactor2dTreeBlock: public FormFactorBlock
{
};

struct FormFactorQuadtreeBlock: public FormFactor2dTreeBlock
{
};

struct FormFactorOctreeBlock: public FormFactor2dTreeBlock
{
};

struct FormFactorMatrix
{
};
