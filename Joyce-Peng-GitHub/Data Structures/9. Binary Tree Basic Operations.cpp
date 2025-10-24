#include <bits/stdc++.h>

inline void redirectIO() {
#ifndef ONLINE_JUDGE
	char filename[] = __FILE__;
	filename[sizeof(filename) - 4] = 'i';
	filename[sizeof(filename) - 3] = 'n';
	filename[sizeof(filename) - 2] = '\0';
	std::freopen(filename, "r", stdin);
	filename[sizeof(filename) - 4] = 'o';
	filename[sizeof(filename) - 3] = 'u';
	filename[sizeof(filename) - 2] = 't';
	std::freopen(filename, "w", stdout);
#endif
}

struct TreeNode {
	std::unique_ptr<TreeNode> lch, rch;
	char val;

	TreeNode() : lch(nullptr), rch(nullptr), val(0) {}
	TreeNode(char val,
			 std::unique_ptr<TreeNode> lch = nullptr,
			 std::unique_ptr<TreeNode> rch = nullptr)
		: lch(std::move(lch)), rch(std::move(rch)), val(val) {}
};

std::unique_ptr<TreeNode> rt;
size_t leaf_num;

std::unique_ptr<TreeNode> build() {
	char val;
	std::cin >> val;
	if (val == '#') return nullptr;
	std::unique_ptr<TreeNode> node(new TreeNode(val, build(), build()));
	if (!node->lch && !node->rch) ++leaf_num;
	return node;
}

inline void preprocess() { rt = build(); }

void overturn(TreeNode *rt) {
	if (rt) {
		std::swap(rt->lch, rt->rch);
		overturn(rt->lch.get());
		overturn(rt->rch.get());
	}
}

template <size_t indent = 4>
void outputConcave(TreeNode *rt, size_t depth) {
	if (rt) {
		for (size_t i = 0; i < indent * depth; ++i) std::cout << ' ';
		std::cout << rt->val << '\n';
		outputConcave<indent>(rt->lch.get(), depth + 1);
		outputConcave<indent>(rt->rch.get(), depth + 1);
	}
}

void outputPreorder(TreeNode *rt) {
	if (rt) {
		std::cout << rt->val;
		outputPreorder(rt->lch.get());
		outputPreorder(rt->rch.get());
	}
}
void outputInorder(TreeNode *rt) {
	if (rt) {
		outputInorder(rt->lch.get());
		std::cout << rt->val;
		outputInorder(rt->rch.get());
	}
}
void outputPostorder(TreeNode *rt) {
	if (rt) {
		outputPostorder(rt->lch.get());
		outputPostorder(rt->rch.get());
		std::cout << rt->val;
	}
}

inline void solve(TreeNode *rt) {
	constexpr size_t INDENT = 4;
	outputConcave<INDENT>(rt, 0);
	std::cout << "pre_sequence  : ";
	outputPreorder(rt);
	std::cout << '\n'
			  << "in_sequence   : ";
	outputInorder(rt);
	std::cout << '\n'
			  << "post_sequence : ";
	outputPostorder(rt);
	std::cout << '\n';
}

inline void solve() {
	std::cout << "BiTree\n";
	solve(rt.get());
	overturn(rt.get());
	std::cout << "Number of leaf: " << leaf_num << '\n'
			  << "BiTree swapped\n";
	solve(rt.get());
}

int mainLoop() {
	solve();
	return 0;
}

int main() {
	redirectIO();
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	preprocess();
	return mainLoop();
}