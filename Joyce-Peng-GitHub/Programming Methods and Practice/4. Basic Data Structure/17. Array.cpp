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

std::queue<std::string> q;

inline void preprocess() {}

inline void solve() {
	char op[10];
	std::cin >> op;
	if (!std::strcmp(op, "Arrive")) {
		std::string name;
		std::cin >> name;
		q.emplace(std::move(name));
	} else if (q.empty()) {
		if (std::strcmp(op, "Leave")) {
			std::cout << "Empty queue\n";
		}
	} else if (!std::strcmp(op, "Leave")) {
		q.pop();
	} else if (!std::strcmp(op, "QueueHead")) {
		std::cout << q.front() << '\n';
	} else if (!std::strcmp(op, "QueueTail")) {
		std::cout << q.back() << '\n';
	} else {
		assert(false);
	}
}

int mainLoop() {
	uint64_t cnt_testcases;
	std::cin >> cnt_testcases;
	while (cnt_testcases--) {
		solve();
	}
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