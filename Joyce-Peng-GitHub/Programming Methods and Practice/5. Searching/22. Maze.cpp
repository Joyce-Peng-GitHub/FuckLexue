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

inline void solve() {
	size_t m, n, p;
	std::cin >> m >> n >> p;
	std::vector<std::string> grid(m);
	for (auto &row : grid) {
		row.reserve(n);
		std::cin >> row;
	}
	constexpr int DX[] = {-1, 0, 1, 0}, DY[] = {0, 1, 0, -1};
	std::queue<std::tuple<size_t, size_t, uint32_t>> q;
	std::vector<std::vector<std::vector<bool>>>
		vis(p, std::vector<std::vector<bool>>(m, std::vector<bool>(n)));
	for (size_t i = 0; i < m && q.empty(); ++i) {
		for (size_t j = 0; j < n; ++j) {
			if (grid[i][j] == 'S') {
				grid[i][j] = '.';
				q.emplace(i, j, 0);
				vis[0][i][j] = true;
				break;
			}
		}
	}
	while (q.size()) {
		auto x0 = std::get<0>(q.front()), y0 = std::get<1>(q.front());
		auto t = std::get<2>(q.front()) + 1;
		q.pop();
		for (unsigned i = 0; i < 4; ++i) {
			size_t x = x0 + DX[i], y = y0 + DY[i];
			if (x == size_t(-1) || x == m || y == size_t(-1) || y == n ||
				grid[x][y] == '#' || (grid[x][y] == '*' && t % p) || vis[t % p][x][y]) {
				continue;
			}
			if (grid[x][y] == 'E') {
				std::cout << t << '\n';
				return;
			}
			q.emplace(x, y, t);
			vis[t % p][x][y] = true;
		}
	}
	std::cout << "-1\n";
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