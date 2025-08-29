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

constexpr uint32_t T = 1e6;
std::array<uint32_t, T + 2> cnt;

inline void preprocess() {}

inline void solve() {
	size_t n;
	std::cin >> n;
	while (n--) {
		uint32_t l, r;
		std::cin >> l >> r;
		++cnt[l];
		--cnt[r + 1];
	}
	for (uint32_t i = 1; i <= T + 1; ++i) {
		cnt[i] += cnt[i - 1];
	}
	std::cout << *std::max_element(cnt.begin(), cnt.end()) << std::endl;
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