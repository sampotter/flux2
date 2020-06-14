#pragma once

#include "common.hpp"
#include "shape_model.hpp"

namespace Flux {

struct Block {
	virtual ~Block() {}
	virtual int depth() const = 0;
	virtual bool is_leaf() const = 0;
	virtual vec_t operator()(vec_ref_t rhs) const = 0;
};

struct OctreeNodeBlock: public Block {
	std::array<std::unique_ptr<Block>, 8> blocks;
	std::array<permutation_t, 8> perms;

	int depth() const final {
		int d = 0;
		for (auto & block: blocks) {
			d = std::max(d, block->depth());
		}
		return d + 1;
	}

	bool is_leaf() const final {
		return false;
	}


};

struct LeafBlock: public Block {
	int depth() const final {
		return 0;
	}

	bool is_leaf() const final {
		return true;
	}
};

struct EmptyBlock: public LeafBlock {};

struct ZeroBlock: public LeafBlock {};

struct DenseBlock: public LeafBlock {};

struct SparseBlock: public LeafBlock {};

struct SvdBlock: public LeafBlock {};

}
