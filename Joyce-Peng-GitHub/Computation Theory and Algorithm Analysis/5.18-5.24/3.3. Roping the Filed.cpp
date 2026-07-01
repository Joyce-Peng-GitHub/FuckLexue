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

struct Vec {
	int64_t x, y;

	Vec(int64_t x = 0, int64_t y = 0) : x(x), y(y) {}

	Vec operator+(const Vec &other) const { return Vec(x + other.x, y + other.y); }
	Vec operator-(const Vec &other) const { return Vec(x - other.x, y - other.y); }
	Vec operator-() const { return Vec(-x, -y); }
	bool operator==(const Vec &other) const { return (x == other.x && y == other.y); }

	int64_t normSq() const { return (x * x + y * y); }
	static int64_t distSq(const Vec &a, const Vec &b) { return (a - b).normSq(); }

	static int64_t dot(const Vec &a, const Vec &b) { return (a.x * b.x + a.y * b.y); }
	static int64_t cross(const Vec &a, const Vec &b) { return (a.x * b.y - a.y * b.x); }
};

inline __int128_t sq(int64_t x) { return (SC<__int128_t>(x) * x); }

inline void preprocess() {}

inline void solve() {
	size_t m, n;
	int64_t rad;
	std::cin >> n >> m >> rad;
	if (n <= 3) {
		std::cout << "0\n";
		return;
	}
	std::vector<Vec> points(n), circs(m);
	for (auto &p : points) std::cin >> p.x >> p.y;
	for (auto &c : circs) std::cin >> c.x >> c.y;

	{
		size_t i_base =
			std::min_element(points.begin(), points.end(),
							 [](const Vec &lhs, const Vec &rhs) {
								 return ((lhs.y == rhs.y)
											 ? (lhs.x < rhs.x)
											 : (lhs.y < rhs.y));
							 }) -
			points.begin();
		std::swap(points[0], points[i_base]);
	}
	std::sort(points.begin() + 1, points.end(),
			  [&](const Vec &lhs, const Vec &rhs) {
				  auto cross = Vec::cross(lhs - points[0], rhs - points[0]);
				  if (cross == 0) {
					  return (Vec::distSq(lhs, points[0]) < Vec::distSq(rhs, points[0]));
				  }
				  return (cross > 0);
			  });

	std::vector<std::vector<bool>> valid(n, std::vector<bool>(n, true));
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = i + 2; j < n; ++j) {
			if (i == 0 && j + 1 == n) {
				valid[i][j] = false;
				valid[j][i] = false;
				continue;
			}

			auto u = points[j] - points[i];
			for (const auto &circ : circs) {
				auto v = circ - points[i];

				int64_t dot = Vec::dot(u, v);
				bool flag;
				if (dot <= 0) {
					flag = ((circ - points[i]).normSq() <= sq(rad));
				} else if (dot >= u.normSq()) {
					flag = ((circ - points[j]).normSq() <= sq(rad));
				} else {
					flag = (SC<__int128_t>(u.normSq()) * v.normSq() - sq(Vec::dot(u, v)) <= SC<__int128_t>(u.normSq()) * sq(rad));
				}

				if (flag) {
					valid[i][j] = false;
					valid[j][i] = false;
					break;
				}
			}
		}
	}

	std::vector<std::vector<uint64_t>> dp(n, std::vector<uint64_t>(n + 1, 0));
	for (size_t len = 3; len <= n; ++len) {
		for (size_t i = 0; i + len <= n; ++i) {
			for (size_t j = i + 1; j + 2 <= i + len; ++j) {
				dp[i][i + len] = std::max(dp[i][i + len], dp[i][j + 1] + dp[j][i + len]);
			}

			if (valid[i][i + len - 1] && !(i == 0 && len == n)) {
				++dp[i][i + len];
			}
		}
	}

	std::cout << dp[0][n] << '\n';
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