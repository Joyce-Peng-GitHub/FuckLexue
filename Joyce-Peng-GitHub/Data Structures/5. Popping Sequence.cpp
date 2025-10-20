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

inline void preprocess() {}

inline void solve(uint64_t n, uint64_t q) {
	std::vector<uint64_t> stk;
	uint64_t nxt;
	stk.reserve(n);
	while (q--) {
		stk.clear();
		nxt = 1;
		bool not_valid = false;
		for (uint64_t i = 0; i < n; ++i) {
			uint64_t x;
			std::cin >> x;
			if (not_valid) continue;
			while (nxt <= x) stk.push_back(nxt++);
			if (stk.back() == x) {
				stk.pop_back();
			} else {
				not_valid = true;
			}
		}
		std::cout << (not_valid ? "No\n" : "Yes\n");
	}
}

int mainLoop() {
	uint64_t n, q;
	bool not_first = false;
	while (std::cin >> n >> q, n || q) {
		if (not_first) {
			std::cout << '\n';
		} else {
			not_first = true;
		}
		solve(n, q);
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