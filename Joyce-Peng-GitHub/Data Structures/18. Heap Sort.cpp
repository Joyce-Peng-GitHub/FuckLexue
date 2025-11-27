#include <bits/stdc++.h>

inline void redirectIO() {
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

inline void output(const std::vector<int64_t> &arr) {
	for (auto e : arr) std::cout << e << ' ';
	std::cout << '\n';
}

inline void solve() {
	size_t n;
	std::cin >> n;
	std::vector<int64_t> arr(n);
	for (auto &e : arr) std::cin >> e;
	std::make_heap(arr.begin(), arr.end());
	output(arr);
	std::pop_heap(arr.begin(), arr.end()), arr.pop_back();
	output(arr);
	std::pop_heap(arr.begin(), arr.end()), arr.pop_back();
	output(arr);
}

inline int mainLoop() {
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