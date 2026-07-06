#include <bits/stdc++.h>

#define SC static_cast

inline void redirectIo() {
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

struct Vec {
	int32_t x, y;

	Vec(int32_t x = 0, int32_t y = 0) : x(x), y(y) {}

	Vec operator+(const Vec &other) const { return Vec(x + other.x, y + other.y); }
	Vec operator-(const Vec &other) const { return Vec(x - other.x, y - other.y); }

	Vec operator*(int32_t mul) const { return Vec(mul * x, mul * y); }
	friend Vec operator*(int32_t lhs, const Vec &rhs) { return (rhs * lhs); }

	Vec &operator+=(const Vec &other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec &operator-=(const Vec &other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	friend std::istream &operator>>(std::istream &is, Vec &v) {
		return (is >> v.x >> v.y);
	}
};

inline void preprocess() {}

inline bool solve() {
	const std::array<Vec, 4> DIRS{
		Vec(1, 0), Vec(0, 1), Vec(-1, 0), Vec(0, -1)
	};

	size_t l, m, n;
	if (!(std::cin >> m >> n >> l)) return false;
	std::vector<std::vector<uint32_t>> grid(m, std::vector<uint32_t>(n));
	for (size_t i = 0; i < l; ++i) {
		int32_t x, y;
		std::cin >> x >> y;
		--x, --y;
		std::cin >> grid[x][y];
	}
	Vec src, dst;
	std::cin >> src >> dst;
	--src.x, --src.y;
	--dst.x, --dst.y;

	auto dists = std::vector<std::vector<uint32_t>>(m, std::vector<uint32_t>(n, -1));
	std::queue<Vec> q;

	dists[src.x][src.y] = 0;
	q.push(src);

	while (q.size()) {
		auto cur = q.front();
		q.pop();

		auto dist = dists[cur.x][cur.y] + 1;

		for (const auto &dir : DIRS) {
			auto nxt = cur + dir;
			if (nxt.x < 0 || nxt.x >= m || nxt.y < 0 || nxt.y >= n) continue;

			while (0 <= nxt.x && nxt.x < m && 0 <= nxt.y && nxt.y < n && grid[nxt.x][nxt.y]) {
				nxt = nxt + grid[nxt.x][nxt.y] * dir;
			}
			if (nxt.x < 0) {
				nxt.x = 0;
			} else if (nxt.x >= m) {
				nxt.x = m - 1;
			} else if (nxt.y < 0) {
				nxt.y = 0;
			} else if (nxt.y >= n) {
				nxt.y = n - 1;
			}

			if (dists[nxt.x][nxt.y] <= dist) continue;
			dists[nxt.x][nxt.y] = dist;
			q.push(nxt);
		}
	}

	auto ans = dists[dst.x][dst.y];
	if (~ans) {
		std::cout << ans << '\n';
	} else {
		std::cout << "impossible\n";
	}

	return true;
}

inline int mainLoop() {
	while (solve());
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	redirectIo();
	preprocess();
	return mainLoop();
}