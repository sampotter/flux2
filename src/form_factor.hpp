#pragma once

#include "common.hpp"

constexpr double EPS = 1e-5;

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
