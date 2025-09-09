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

size_t m, n;
std::vector<bool> ori, cur;

inline void flip(size_t x, size_t y) {
	cur[x * n + y].flip();
	if (x) {
		cur[(x - 1) * n + y].flip();
	}
	if (x + 1 < m) {
		cur[(x + 1) * n + y].flip();
	}
	if (y) {
		cur[x * n + (y - 1)].flip();
	}
	if (y + 1 < n) {
		cur[x * n + (y + 1)].flip();
	}
}

inline void preprocess() {
	std::cin >> m >> n;
	ori.resize(m * n);
	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			char ch;
			std::cin >> ch;
			ori[i * n + j] = (ch == '1');
		}
	}
}

inline void solve() {
	size_t res = m * n + 1;
	for (size_t mask = 0; mask < (uint32_t(1) << n); ++mask) {
		cur = ori;
		size_t cnt = 0;
		for (size_t j = 0; j < n; j++) {
			if ((mask >> j) & 1) {
				flip(0, j);
				++cnt;
			}
		}
		for (size_t i = 1; i < m; i++) {
			for (size_t j = 0; j < n; j++) {
				if (cur[(i - 1) * n + j]) {
					flip(i, j);
					++cnt;
				}
			}
		}
		bool all_clear = true;
		for (size_t j = 0; j < n; j++) {
			if (cur[(m - 1) * n + j]) {
				all_clear = false;
				break;
			}
		}
		if (all_clear && cnt < res) {
			res = cnt;
		}
	}
	std::cout << res << std::endl;
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