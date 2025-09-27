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

inline void solve() {
	int64_t n, s, m;
	char ch;
	std::cin >> n >> ch >> s >> ch >> m;
	if (n < 1 || s < 1 || m < 1) {
		std::cout << "n,m,k must bigger than 0.\n";
		return;
	}
	if (s > n) {
		std::cout << "k should not bigger than n.\n";
		return;
	}
	std::deque<int64_t> dq;
	for (int64_t i = 1; i <= n; ++i) {
		dq.emplace_back(i);
	}
	--s;
	int64_t cnt_out = 0;
	while (dq.size()) {
		s = (s + m - 1) % dq.size();
		auto iter = dq.begin() + s;
		std::cout << *iter << (((++cnt_out) % 10 && dq.size() > 1) ? ' ' : '\n');
		dq.erase(iter);
	}
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