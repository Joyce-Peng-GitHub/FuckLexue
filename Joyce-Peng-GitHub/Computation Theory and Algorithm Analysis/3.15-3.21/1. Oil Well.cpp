#include <bits/stdc++.h>

#define SC static_cast

inline void redirectIo() {
#ifndef ONLINE_JUDGE
	char filename[] = __FILE__;
	size_t len = sizeof(filename) / sizeof(filename[0]) - 1;
	filename[len - 3] = 'i';
	filename[len - 2] = 'n';
	filename[len - 1] = '\0';
	std::freopen(filename, "r", stdin);
	filename[len - 3] = 'o';
	filename[len - 2] = 'u';
	filename[len - 1] = 't';
	std::freopen(filename, "w", stdout);
#endif
}

inline void preprocess() {}

inline void solve() {
	std::vector<uint32_t> arr;
	for (uint32_t x;
		 (std::cin >> x) && (std::cin.get() != EOF) && (std::cin >> x);
		 arr.emplace_back(x));
	if (arr.empty()) {
		std::cout << '0' << '\n';
		return;
	}
	size_t mid = ((arr.size() - 1) >> 1);
	std::nth_element(arr.begin(), arr.begin() + mid, arr.end());
	std::cout << arr[mid] << '\n';
}

inline int mainLoop() {
	uint64_t tc_num = 1;
	// std::cin >> tc_num;
	for (uint64_t tc = 0; tc < tc_num; ++tc) {
		solve();
	}
	return 0;
}

int main() {
	redirectIo();
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	preprocess();
	return mainLoop();
}