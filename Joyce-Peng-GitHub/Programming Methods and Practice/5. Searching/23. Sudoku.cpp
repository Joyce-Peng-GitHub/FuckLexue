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

constexpr unsigned INN = 4, OUT = 4;
using Block = std::array<std::array<uint8_t, INN>, INN>;
using Row = std::array<Block, OUT>;
using Sudoku = std::array<Row, OUT>;
using RowSolution = std::array<uint8_t, OUT>;
using Solution = std::array<RowSolution, OUT>;

inline void preprocess() {}

/**
 * @return @param block rotated counter-clockwise @param times times
 */
inline Block rotate(const Block &block, int times = 1) {
	times &= 4 - 1;
	if (times == 0) {
		return block;
	}
	Block res;
	if (times == 1) {
		for (unsigned i = 0; i < INN; ++i) {
			for (unsigned j = 0; j < INN; ++j) {
				res[INN - j - 1][i] = block[i][j];
			}
		}
	} else if (times == 2) {
		for (unsigned i = 0; i < INN; ++i) {
			for (unsigned j = 0; j < INN; ++j) {
				res[INN - i - 1][INN - j - 1] = block[i][j];
			}
		}
	} else { // times == 3
		for (unsigned i = 0; i < INN; ++i) {
			for (unsigned j = 0; j < INN; ++j) {
				res[j][INN - i - 1] = block[i][j];
			}
		}
	}
	return res;
}

inline bool checkRow(const Row &row) {
	for (unsigned i = 0; i < INN; ++i) {
		std::bitset<INN * OUT> used;
		for (const auto &block : row) {
			for (unsigned j = 0; j < INN; ++j) {
				if (used[block[i][j]]) {
					return false;
				}
				used.set(block[i][j]);
			}
		}
	}
	return true;
}

std::vector<RowSolution> solveRow(Row row) {
	std::vector<RowSolution> slns;
	RowSolution sln;
	std::function<void(unsigned)> dfs = [&](unsigned idx) {
		if (idx == OUT) {
			if (checkRow(row)) {
				slns.emplace_back(sln);
			}
			return;
		}
		for (sln[idx] = 0; sln[idx] < 4; ++sln[idx]) {
			dfs(idx + 1);
			row[idx] = rotate(row[idx]);
		}
	};
	dfs(0);
	return slns;
}

std::array<std::vector<RowSolution>, OUT> solveRows(const Sudoku &sudoku) {
	std::array<std::vector<RowSolution>, OUT> slns;
	for (unsigned i = 0; i < OUT; ++i) {
		slns[i] = solveRow(sudoku[i]);
	}
	return slns;
}

inline bool checkColumn(const Sudoku &sudoku, unsigned col) {
	for (unsigned i = 0; i < INN; ++i) {
		std::bitset<INN * OUT> used;
		for (unsigned j = 0; j < OUT; ++j) {
			for (unsigned k = 0; k < INN; ++k) {
				if (used[sudoku[j][col][k][i]]) {
					return false;
				}
				used.set(sudoku[j][col][k][i]);
			}
		}
	}
	return true;
}
inline bool checkColumns(const Sudoku &sudoku) {
	for (unsigned i = 0; i < OUT; ++i) {
		if (!checkColumn(sudoku, i)) {
			return false;
		}
	}
	return true;
}

inline void solve() {
	Sudoku ori, cur;
	for (unsigned i = 0; i < INN * OUT; ++i) {
		std::string row;
		std::cin >> row;
		for (unsigned j = 0; j < row.size(); ++j) {
			ori[i / INN][j / INN][i % INN][j % INN] = (std::isdigit(row[j])
														   ? (row[j] - '0')
														   : (row[j] - 'A' + 10));
		}
	}
	auto row_slns = solveRows(ori);
	unsigned best_sum = UINT_MAX, cur_sum = 0;
	Solution best_sln, cur_sln;
	std::function<void(unsigned)> dfs = [&](unsigned idx) {
		if (idx == OUT) {
			if (checkColumns(cur)) {
				best_sum = cur_sum;
				best_sln = cur_sln;
			}
			return;
		}
		for (const auto &sln : row_slns[idx]) {
			cur_sln[idx] = sln;
			for (unsigned j = 0; j < OUT; ++j) {
				cur[idx][j] = rotate(ori[idx][j], sln[j]);
			}
			cur_sum += std::accumulate(sln.begin(), sln.end(), 0u);
			if (cur_sum < best_sum) {
				dfs(idx + 1);
			}
			cur_sum -= std::accumulate(sln.begin(), sln.end(), 0u);
		}
	};
	dfs(0);
	std::cout << best_sum << '\n';
	for (unsigned i = 0; i < OUT; ++i) {
		for (unsigned j = 0; j < OUT; ++j) {
			for (uint8_t k = 0; k < best_sln[i][j]; ++k) {
				std::cout << (i + 1) << ' ' << (j + 1) << '\n';
			}
		}
	}
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