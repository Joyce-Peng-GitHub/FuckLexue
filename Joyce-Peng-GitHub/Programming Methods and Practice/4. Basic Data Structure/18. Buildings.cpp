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

constexpr size_t N = 1e6;
constexpr uint32_t C = 1e6;

size_t n;
std::array<uint32_t, N> colors, heights;
std::array<uint32_t, C + 1> cnt_colors;
size_t stk_sz;
std::array<size_t, N> stk;

inline void preprocess() {}

inline void solve() {
	std::cin >> n;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> colors[i];
	}
	for (size_t i = 0; i < n; ++i) {
		std::cin >> heights[i];
	}
	size_t unq = 0;
	for (size_t i = 0; i < n; ++i) {
		while (stk_sz && heights[stk[stk_sz - 1]] < heights[i]) {
			if (!(--cnt_colors[colors[stk[--stk_sz]]])) {
				--unq;
			}
		}
		stk[stk_sz++] = i;
		if (!(cnt_colors[colors[i]]++)) {
			++unq;
		}
		std::cout << unq << ((i + 1 == n) ? '\n' : ' ');
	}
	while (stk_sz) {
		--cnt_colors[colors[stk[--stk_sz]]];
	}
	unq = 0;
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