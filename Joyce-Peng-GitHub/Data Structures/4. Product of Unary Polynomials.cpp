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

struct Node {
	int coef, exp;
	std::unique_ptr<Node> next;
};

inline void preprocess() {}

inline void emplace(Node *prev, int coef, int exp) {
	auto tmp = std::move(prev->next);
	prev->next.reset(new Node{coef, exp, std::move(tmp)});
}

inline void erase(Node *prev) {
	prev->next = std::move(prev->next->next);
}

std::unique_ptr<Node> input() {
	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	std::unique_ptr<Node> head(new Node{0, 0, nullptr});
	Node *last = head.get();
	char ch;
	int coef, exp;
	while (iss >> ch >> coef >> ch >> exp >> ch >> ch) {
		emplace(last, coef, exp);
		last = last->next.get();
	}
	return head;
}

void output(const Node *head) {
	for (; head->next; head = head->next.get()) {
		std::cout << '<' << head->next->coef << ',' << head->next->exp << '>' << ',';
	}
	std::cout << '\n';
}

struct Term {
	int coef, exp;
};

std::unique_ptr<Node> vectorToList(const std::vector<Term> &vec) {
	std::unique_ptr<Node> head(new Node{0, 0, nullptr});
	Node *last = head.get();
	for (const auto &term : vec) {
		if (!term.coef) {
			continue;
		}
		emplace(last, term.coef, term.exp);
		last = last->next.get();
	}
	if (!head->next) {
		head->next = std::unique_ptr<Node>(new Node{0, 0, nullptr});
	}
	return head;
}

std::unique_ptr<Node> multiply(const Node *lhs, const Node *rhs) {
	if (!lhs->next || !rhs->next) {
		return std::unique_ptr<Node>(new Node{0, 0,
											  std::unique_ptr<Node>(new Node{0, 0, nullptr})});
	}
	std::vector<Term> buf;
	for (const Node *p = lhs; p->next; p = p->next.get()) {
		for (const Node *q = rhs; q->next; q = q->next.get()) {
			buf.push_back({p->next->coef * q->next->coef, p->next->exp + q->next->exp});
		}
	}
	std::sort(buf.begin(), buf.end(),
			  [](const Term &lhs, const Term &rhs) {
				  return (lhs.exp < rhs.exp);
			  });
	size_t unq = 1;
	for (size_t i = 1; i < buf.size(); ++i) {
		if (buf[unq - 1].exp == buf[i].exp) {
			buf[unq - 1].coef += buf[i].coef;
		} else {
			buf[unq++] = buf[i];
		}
	}
	buf.erase(buf.begin() + unq, buf.end());
	return vectorToList(buf);
}

inline void solve() {
	output(multiply(input().get(), input().get()).get());
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