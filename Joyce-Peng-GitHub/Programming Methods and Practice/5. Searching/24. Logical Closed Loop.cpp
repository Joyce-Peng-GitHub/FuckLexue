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

constexpr size_t N = 3e5, M = 3e5;
size_t m, n, tot;
std::array<size_t, M> edges, nexts;
std::array<size_t, N> heads;
std::array<size_t, N> indeg, zero_indeg_verts;

inline void preprocess() {
	std::cin >> n >> m;
	std::fill(heads.begin(), heads.begin() + n, size_t(-1));
	for (size_t i = 0; i < m; ++i) {
		size_t u;
		std::cin >> u;
		std::cin >> edges[i];
		--edges[i];
		nexts[i] = heads[--u];
		heads[u] = i;
	}
}

/**
 * @return whether there is a cycle formed by the first @param lim edges
 */
bool toposort(size_t lim) {
	std::fill(indeg.begin(), indeg.begin() + n, 0);
	for (size_t frm = 0; frm < n; ++frm) {
		for (size_t i = heads[frm]; ~i; i = nexts[i]) {
			if (i >= lim) {
				continue;
			}
			++indeg[edges[i]];
		}
	}
	tot = 0;
	for (size_t i = 0; i < n; ++i) {
		if (!indeg[i]) {
			zero_indeg_verts[tot++] = i;
		}
	}
	size_t cnt = 0;
	while (tot) {
		size_t frm = zero_indeg_verts[--tot];
		++cnt;
		for (size_t i = heads[frm]; ~i; i = nexts[i]) {
			if (i >= lim) {
				continue;
			}
			if (!(--indeg[edges[i]])) {
				zero_indeg_verts[tot++] = edges[i];
			}
		}
	}
	return (cnt != n);
}

/**
 * @brief behaves as if it generates func[beg, end) and
 * 	performs std::lower_bound on it
 */
template <typename T, typename Ret, typename Func,
		  typename Cmp = std::less<Ret>>
inline T lowerBound(T beg, T end, const Ret &val, Func func = Func(), Cmp cmp = Cmp()) {
	while (beg < end) {
		T mid = beg + (end - beg) / 2;
		if (cmp(func(mid), val)) {
			beg = mid + 1;
		} else {
			end = mid;
		}
	}
	return beg;
}

inline void solve() {
	size_t mn = lowerBound(size_t(1), m + 1, true, toposort);
	if (mn == m + 1) {
		std::cout << "-1\n";
	} else {
		std::cout << mn << std::endl;
	}
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