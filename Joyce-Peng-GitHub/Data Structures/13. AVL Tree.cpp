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

struct AvlTree {
	struct Node {
		Node *lch, *rch;
		size_t h; // height of the tree whose root is this
		char val;

		explicit Node(char val)
			: lch(nullptr), rch(nullptr), h(1), val(val) {}

		~Node() {
			if (lch) delete lch;
			if (rch) delete rch;
		}

		void updateHeight() {
			h = std::max((lch ? lch->h : 0), (rch ? rch->h : 0)) + 1;
		}
		ssize_t factor() const {
			return ((rch ? rch->h : 0) - (lch ? lch->h : 0));
		}

		static Node *rotateLeft(Node *rt) noexcept {
			Node *new_rt = rt->rch;
			rt->rch = new_rt->lch;
			new_rt->lch = rt;
			rt->updateHeight();
			new_rt->updateHeight();
			return new_rt;
		}
		static Node *rotateRight(Node *rt) noexcept {
			Node *new_rt = rt->lch;
			rt->lch = new_rt->rch;
			new_rt->rch = rt;
			rt->updateHeight();
			new_rt->updateHeight();
			return new_rt;
		}
		static void fixBalance(Node *&rt) noexcept {
			if (rt->factor() < -1) {
				if (rt->lch->factor() >= 0) rt->lch = rotateLeft(rt->lch);
				rt = rotateRight(rt);
			} else if (rt->factor() > 1) {
				if (rt->rch->factor() <= 0) rt->rch = rotateRight(rt->rch);
				rt = rotateLeft(rt);
			}
		}

		static void insert(Node *&rt, char val) {
			assert(rt);

			if (val == rt->val) return;

			if (val < rt->val) {
				if (rt->lch) {
					insert(rt->lch, val);
					rt->updateHeight();
					fixBalance(rt);
				} else {
					rt->lch = new Node(val);
					rt->updateHeight();
				}
			} else {
				if (rt->rch) {
					insert(rt->rch, val);
					rt->updateHeight();
					fixBalance(rt);
				} else {
					rt->rch = new Node(val);
					rt->updateHeight();
				}
			}
		}
	};

	Node *rt = nullptr;

	void insert(char val) {
		if (rt) {
			Node::insert(rt, val);
		} else {
			rt = new Node(val);
		}
	}
};

constexpr size_t INDENT = 4;
AvlTree at;

inline void preprocess() {}

inline void solve(char ch) {
	at.insert(ch);
}

void outputPreorder(const AvlTree::Node *rt) {
	std::cout << rt->val;
	if (rt->lch) outputPreorder(rt->lch);
	if (rt->rch) outputPreorder(rt->rch);
}
void outputInorder(const AvlTree::Node *rt) {
	if (rt->lch) outputInorder(rt->lch);
	std::cout << rt->val;
	if (rt->rch) outputInorder(rt->rch);
}
void outputPostorder(const AvlTree::Node *rt) {
	if (rt->lch) outputPostorder(rt->lch);
	if (rt->rch) outputPostorder(rt->rch);
	std::cout << rt->val;
}
void outputConvex(const AvlTree::Node *rt, size_t dep) {
	if (rt->rch) outputConvex(rt->rch, dep + 1);
	for (size_t i = 0; i < dep * INDENT; ++i) std::cout << ' ';
	std::cout << rt->val << '\n';
	if (rt->lch) outputConvex(rt->lch, dep + 1);
}

inline void output() {
	std::cout << "Preorder: ";
	if (at.rt) outputPreorder(at.rt);
	std::cout << '\n'
			  << "Inorder: ";
	if (at.rt) outputInorder(at.rt);
	std::cout << '\n'
			  << "Postorder: ";
	if (at.rt) outputPostorder(at.rt);
	std::cout << '\n'
			  << "Tree:\n";
	if (at.rt) outputConvex(at.rt, 0);
}

inline int mainLoop() {
	char ch;
	while (std::cin >> ch) solve(ch);
	output();
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	redirectIO();
	return mainLoop();
}