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

constexpr uint32_t MOD = INT32_MAX;
size_t n;
std::vector<size_t> arr;
std::vector<uint32_t> mem;

inline void preprocess() {
	std::cin >> n;
	arr.resize(n + 1);
	for (auto &x : arr) {
		std::cin >> x;
		--x;
	}
	mem.resize((n + 1) * (n + 1));
}

inline size_t pairToKey(size_t l, size_t r) {
	return (l * (n + 1) + r);
}
inline std::pair<size_t, size_t> keyToPair(size_t key) {
	return {key / (n + 1), key % (n + 1)};
}

uint32_t dfs(size_t i, size_t l, size_t r) {
	if (i == n) {
		return 1;
	}
	auto &res = mem[pairToKey(l, r)];
	if (res) {
		return res;
	}
	if (arr[i + 1] <= l) {
		return (res = dfs(i + 1, arr[i + 1], r));
	}
	if (arr[i + 1] >= r) {
		return (res = dfs(i + 1, l, arr[i + 1]));
	}
	return (res = (dfs(i + 1, arr[i + 1], r) + dfs(i + 1, l, arr[i + 1])) % MOD);
}

inline void solve() {
	std::cout << dfs(1, arr[0], arr[1]) << std::endl;
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