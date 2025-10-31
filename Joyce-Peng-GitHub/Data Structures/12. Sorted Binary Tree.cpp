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

struct Node;
using Tree = std::unique_ptr<Node>;
struct Node {
	Tree lch, rch;
	int64_t val;

	Node(int64_t val, Node *lch = nullptr, Node *rch = nullptr)
		: lch(lch), rch(rch), val(val) {}
};

constexpr size_t INDENT = 4;
Tree tree;

inline void insert(Tree *p, int64_t val) {
	while (*p) {
		if (p->get()->val == val) return;
		if (val < p->get()->val) {
			p = &p->get()->lch;
		} else {
			p = &p->get()->rch;
		}
	}
	p->reset(new Node(val));
}

inline void preprocess() {}

inline void solve(int64_t val) {
	insert(&tree, val);
}

inline void outputConcave(Tree *p, size_t dep) {
	if (p->get()->lch) outputConcave(&p->get()->lch, dep + 1);
	for (size_t i = 0; i < INDENT * dep; ++i) std::cout << ' ';
	std::cout << p->get()->val << '\n';
	if (p->get()->rch) outputConcave(&p->get()->rch, dep + 1);
}

inline void outputInOrder(Tree *p) {
	if (p->get()->lch) outputInOrder(&p->get()->lch);
	std::cout << ' ' << p->get()->val;
	if (p->get()->rch) outputInOrder(&p->get()->rch);
}

inline void output() {
	if (tree) outputConcave(&tree, 0);
	std::cout << '\n';
	if (tree) outputInOrder(&tree);
	std::cout << std::endl;
}

inline int mainLoop() {
	int64_t val;
	while (std::cin >> val && val) solve(val);
	output();
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	redirectIO();
	preprocess();
	return mainLoop();
}