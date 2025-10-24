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

inline void outputError(size_t p) {
	std::cout << "ERROR: T[" << p << "] is NULL\n";
}

inline void solve() {
	size_t n;
	std::cin >> n;
	std::unique_ptr<uint64_t[]> arr(new uint64_t[n]);
	for (size_t i = 0; i < n; ++i) std::cin >> arr.get()[i];
	size_t p, q;
	std::cin >> p >> q;
	if (!arr.get()[p - 1]) {
		outputError(p);
		return;
	}
	if (!arr.get()[q - 1]) {
		outputError(q);
		return;
	}
	if (p > q) p ^= (q ^= (p ^= q));
	q >>= __builtin_clzll(p) - __builtin_clzll(q);
	if (p != q) p >>= sizeof(size_t) * 8 - __builtin_clzll(p ^ q);
	std::cout << p << ' ' << arr.get()[p - 1] << std::endl;
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