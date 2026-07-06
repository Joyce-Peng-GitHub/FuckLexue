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

constexpr size_t N = 1000;
constexpr std::array<std::array<unsigned, 4>, 3> EQUIV_CLASSES{
	{{0, 3, 6, 9},
	 {1, 4, 7, -1u},
	 {2, 5, 8, -1u}}
};
constexpr std::array<unsigned, 2> LSDS{{0, 5}};

inline void preprocess() {}

std::vector<unsigned> solve_lsd(const std::array<size_t, 10> &ori_cnts, unsigned lsd) {
	if (!ori_cnts[lsd]) return {};

	auto cnts = ori_cnts;
	--cnts[lsd];

	{
		unsigned sum = lsd;
		for (unsigned d = 0; d < 10; ++d) sum += cnts[d] * d;

		auto rem = sum % 3;
		if (rem) {
			size_t to_remove_num = 1;
			for (auto d : EQUIV_CLASSES[rem]) {
				if (d == -1u) break;

				if (cnts[d]) {
					--cnts[d];
					--to_remove_num;
					break;
				}
			}

			if (to_remove_num) {
				to_remove_num = 2;
				for (auto d : EQUIV_CLASSES[1 + !(rem - 1)]) {
					if (d == -1u) break;

					while (cnts[d] && to_remove_num) {
						--cnts[d];
						--to_remove_num;
					}
				}

				if (to_remove_num) return {};
			}
		}
	}

	std::vector<unsigned> res;
	for (unsigned d = 10; d--;) {
		res.insert(res.end(), cnts[d], d);
	}
	res.push_back(lsd);

	assert(res.size());
	if (res.front() == 0) {
		res.erase(res.begin() + 1, res.end());
	}

	return res;
}

inline bool solve() {

	std::string str;
	str.reserve(N);
	if (!std::getline(std::cin, str)) return false;

	std::array<size_t, 10> cnts{};
	for (char ch : str) {
		++cnts[ch ^ '0'];
	}

	std::array<std::vector<unsigned>, LSDS.size()> cands;
	for (size_t i = 0; i < LSDS.size(); ++i) {
		cands[i] = solve_lsd(cnts, LSDS[i]);
	}

	const auto &res = std::max(
		cands[0], cands[1],
		[](const std::vector<unsigned> &lhs, const std::vector<unsigned> &rhs) {
			return ((lhs.size() == rhs.size()) ? (lhs < rhs) : (lhs.size() < rhs.size()));
		}
	);

	if (res.empty()) {
		std::cout << "impossible\n";
		return true;
	}
	for (const auto &d : res) std::cout << SC<char>('0' ^ d);
	std::cout << '\n';

	return true;
}

inline int mainLoop() {
	while (solve());
	return 0;
}

int main() {
	redirectIo();
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	preprocess();
	return mainLoop();
}