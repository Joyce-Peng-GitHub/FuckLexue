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

template <typename Side, size_t D>
class Hypercube {
public:
	using Sides = std::array<Side, D>;
	using size_type = size_t;
	using iterator = typename Sides::const_iterator;
	using const_iterator = typename Sides::const_iterator;
	using reverse_iterator = typename Sides::const_reverse_iterator;
	using const_reverse_iterator = typename Sides::const_reverse_iterator;

	static constexpr size_t DIM = D;

	Hypercube() = default;
	Hypercube(const Sides &sides) : m_sides(sides) {}
	void assign(const Sides &sides) { m_sides = sides; }

	const Sides &sides() const { return m_sides; }
	const Side &operator[](size_t n) const { return m_sides[n]; }
	const Side &at(size_t n) const { return m_sides.at(n); }

	iterator begin() const { return m_sides.cbegin(); }
	iterator end() const { return m_sides.cend(); }
	const_iterator cbegin() const { return begin(); }
	const_iterator cend() const { return end(); }
	reverse_iterator rbegin() const { return m_sides.rbegin(); }
	reverse_iterator rend() const { return m_sides.rend(); }
	const_reverse_iterator crbegin() const { return rbegin(); }
	const_reverse_iterator crend() const { return rend(); }

	friend bool operator==(const Hypercube &lhs, const Hypercube &rhs) {
		return (lhs.m_sides == rhs.m_sides);
	}
	friend std::istream &operator>>(std::istream &is, Hypercube &hypercube) {
		for (unsigned i = 0; i < DIM; ++i) {
			is >> hypercube.m_sides[i];
		}
		std::sort(hypercube.m_sides.begin(), hypercube.m_sides.end());
		return is;
	}

protected:
	Sides m_sides;
};

template <typename Side>
using Seg = Hypercube<Side, 1>;
template <typename Side>
using Rect = Hypercube<Side, 2>;
template <typename Side>
using Cube = Hypercube<Side, 3>;

template <typename Side>
std::array<std::pair<Rect<Side>, Side>, 3> surfacesOf(const Cube<Side> &cube) {
	return {
		std::make_pair(Rect<Side>({cube[0], cube[1]}), cube[2]),
		std::make_pair(Rect<Side>({cube[0], cube[2]}), cube[1]),
		std::make_pair(Rect<Side>({cube[1], cube[2]}), cube[0])};
}

namespace std {
	template <typename Side, size_t DIM>
	struct hash<Hypercube<Side, DIM>> {
		size_t operator()(const Hypercube<Side, DIM> &hc) const {
			size_t res = 0;
			for (const auto &s : hc) {
				res ^= m_hash(s);
			}
			return res;
		}

	protected:
		hash<Side> m_hash;
	};
}

inline void preprocess() {}

inline void solve() {
	size_t n;
	std::cin >> n;
	std::vector<Cube<uint32_t>> cubes(n);
	for (auto &cube : cubes) {
		std::cin >> cube;
	}
	std::unordered_map<Rect<uint32_t>, std::pair<size_t, uint32_t>> ump;
	size_t argmax_sing = std::max_element(
							 cubes.begin(), cubes.end(),
							 [](const Cube<uint32_t> &lhs,
								const Cube<uint32_t> &rhs) {
								 return (lhs[0] < rhs[0]);
							 }) -
						 cubes.begin();
	std::pair<size_t, size_t> argmax_pr{0, 1};
	uint32_t max_pr = 0;
	for (size_t i = 0; i < n; ++i) {
		auto sfcs = surfacesOf(cubes[i]);
		for (const auto &sfc : sfcs) {
			auto iter = ump.find(sfc.first);
			if (iter == ump.end()) {
				continue;
			}
			uint32_t cur = std::min(std::min(sfc.first[0], sfc.first[1]),
									iter->second.second + sfc.second);
			if (cur > max_pr) {
				argmax_pr.first = iter->second.first;
				argmax_pr.second = i;
				max_pr = cur;
			}
		}
		for (const auto &sfc : sfcs) {
			auto iter = ump.find(sfc.first);
			if (iter == ump.end()) {
				ump.insert(std::make_pair(sfc.first, std::make_pair(i, sfc.second)));
			} else if (iter->second.second < sfc.second) {
				iter->second.first = i;
				iter->second.second = sfc.second;
			}
		}
	}
	if (cubes[argmax_sing][0] > max_pr) {
		std::cout << "1\n"
				  << (argmax_sing + 1) << '\n';
		return;
	}
	std::cout << "2\n"
			  << (argmax_pr.first + 1) << ' ' << (argmax_pr.second + 1) << '\n';
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