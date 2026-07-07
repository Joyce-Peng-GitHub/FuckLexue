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

constexpr unsigned N = 24;
unsigned n;
std::array<uint32_t, N + 1> ans;

inline unsigned popcount32(uint32_t x) {
	return
#if UINT_MAX == UINT16_MAX
		__builtin_popcountl
#else
		__builtin_popcount
#endif
		(x);
}

inline uint32_t next(uint32_t cur, bool bit, unsigned len) {
	assert(cur < (uint32_t(1) << (len - 1)));
	assert(len <= 32);

	uint32_t nxt = ((~cur << 1) | bit);
	for (unsigned offset = 1; offset < 32; offset <<= 1) {
		nxt ^= (nxt << offset);
	}
	return (nxt & (~uint32_t(0) >> (32 - len)));
}

void dfs(unsigned len, uint32_t cur, unsigned cnt1) {
	unsigned tot = ((len * (len + 1)) >> 1);
	unsigned cnt0 = tot - cnt1;

	unsigned half = (((n * (n + 1)) >> 1) >> 1);
	if (cnt0 > half || cnt1 > half) return;

	if (cnt0 == cnt1) {
		++ans[len];
	}

	if (len == n) return;
	++len;

	for (unsigned bit = 0; bit < 2; ++bit) {
		auto nxt = next(cur, bit, len);
		dfs(len, nxt, cnt1 + popcount32(nxt));
	}
}

inline void preprocess() {}

inline void solve() {
	std::cin >> n;
	dfs(0, 0, 0);
	std::cout << ans[n] << '\n';
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