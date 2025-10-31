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

constexpr unsigned S = 26;
char in_ord[S + 1], post_ord[S + 1];
size_t pos_in_in_ord[S];
char lch_of[S], rch_of[S];

inline void preprocess() {}

char construct(size_t in_beg, size_t post_beg, size_t len) {
	if (!len) return '\0';
	char cur_rt = post_ord[post_beg + len - 1] - 'a';
	size_t lch_len = pos_in_in_ord[cur_rt] - in_beg;
	lch_of[cur_rt] = construct(in_beg, post_beg, lch_len);
	rch_of[cur_rt] = construct(pos_in_in_ord[cur_rt] + 1, post_beg + lch_len, len - lch_len - 1);
	return cur_rt;
}

inline void solve() {
	std::cin >> in_ord >> post_ord;
	for (size_t i = 0; in_ord[i]; ++i) pos_in_in_ord[in_ord[i] - 'a'] = i;
	size_t len = std::strlen(post_ord);
	if (!len) {
		std::cout << std::endl;
		return;
	}
	char q[S];
	size_t q_beg = 0, q_end = 0;
	q[q_end++] = construct(0, 0, len);
	while (q_beg != q_end) {
		auto frm = q[q_beg++];
		std::cout << static_cast<char>('a' + frm);
		if (lch_of[frm]) q[q_end++] = lch_of[frm];
		if (rch_of[frm]) q[q_end++] = rch_of[frm];
	}
	std::cout << std::endl;
}

inline int mainLoop() {
	solve();
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	redirectIO();
	preprocess();
	return mainLoop();
}