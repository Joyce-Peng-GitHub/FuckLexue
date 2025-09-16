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

inline void solve(size_t m, size_t n) {
	std::vector<std::vector<bool>> grid(m, std::vector<bool>(n));
	std::pair<size_t, size_t> src;
	for (size_t i = 0; i < m; ++i) {
		for (size_t j = 0; j < n; ++j) {
			char ch;
			std::cin >> ch;
			if (ch == '#') {
				grid[i][j] = true;
			} else {
				if (ch == '@') {
					src.first = i;
					src.second = j;
				} else if (ch != '.') {
					assert(0);
				}
			}
		}
	}
	constexpr ssize_t DX[] = {-1, 0, 1, 0}, DY[] = {0, 1, 0, -1};
	std::queue<std::pair<size_t, size_t>> q;
	std::vector<std::vector<bool>> vis(m, std::vector<bool>(n));
	size_t cnt_vis;
	q.emplace(src);
	vis[src.first][src.second] = true;
	cnt_vis = 1;
	while (q.size()) {
		auto x0 = q.front().first, y0 = q.front().second;
		q.pop();
		for (size_t i = 0; i < 4; ++i) {
			size_t x = x0 + DX[i], y = y0 + DY[i];
			if (~x && x < m && ~y && y < n && !grid[x][y] && !vis[x][y]) {
				q.emplace(x, y);
				vis[x][y] = true;
				++cnt_vis;
			}
		}
	}
	std::cout << cnt_vis << '\n';
}

int mainLoop() {
	size_t m, n;
	while (std::cin >> n >> m) {
		if (!n && !m) {
			break;
		}
		solve(m, n);
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