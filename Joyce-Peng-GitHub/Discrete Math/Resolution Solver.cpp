#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using Literal = int;
using Clause = std::set<Literal>;
using ClauseSet = std::set<Clause>;

class ResolutionSolver {
public:
	void run(const std::string &expr) {
		ClauseSet kb = parseCnf(expr);

		bool is_satisfiable = solve(kb);
		if (is_satisfiable) {
			std::cout << "YES\n";
		} else {
			std::cout << "NO\n";
		}
	}

private:
	ClauseSet parseCnf(std::string expr) {
		ClauseSet clauses;

		expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end()); // remove spaces

		if (expr.empty()) {
			return clauses;
		}

		std::stringstream ss(expr);
		std::string seg;

		// divide by '&' to get clauses
		while (std::getline(ss, seg, '&')) {
			Clause cur_clause;

			seg.erase(std::remove(seg.begin(), seg.end(), '('), seg.end());
			seg.erase(std::remove(seg.begin(), seg.end(), ')'), seg.end());

			std::stringstream ss_clause(seg);
			std::string literal_str;

			// divide by '|' to get literals
			while (std::getline(ss_clause, literal_str, '|')) {
				if (literal_str.empty()) continue;

				bool is_neg = false;
				int start_idx = 0;

				if (literal_str[0] == '!') {
					is_neg = true;
					start_idx = 1;
				}

				char var_ch = literal_str[start_idx];
				int val = var_ch - 'A' + 1; // A=1, B=2, ...
				if (is_neg) {
					val = -val;
				}

				cur_clause.insert(val);
			}

			if (!cur_clause.empty()) {
				clauses.insert(cur_clause);
			}
		}
		return clauses;
	}

	bool isTautology(const Clause &c) {
		for (auto l : c) {
			if (c.count(-l)) {
				return true;
			}
		}
		return false;
	}

	bool resolveClauses(const Clause &c1, const Clause &c2, std::vector<Clause> &out_resolvents) {
		bool found = false;

		for (auto l1 : c1) {
			if (c2.count(-l1)) {
				// generate resolvent: (C1 - {l1}) U (C2 - {-l1})
				Clause new_clause;

				// add literals from C1 except l1
				for (auto x : c1) {
					if (x != l1) {
						new_clause.insert(x);
					}
				}
				// add literals from C2 except -l1
				for (auto x : c2) {
					if (x != -l1) {
						new_clause.insert(x);
					}
				}

				if (!isTautology(new_clause)) {
					out_resolvents.push_back(new_clause);
					found = true;
				}
			}
		}
		return found;
	}

	bool solve(ClauseSet kb) {
		while (true) {
			std::vector<Clause> new_clauses;
			std::vector<Clause> clauses(kb.begin(), kb.end());
			size_t sz = clauses.size();
			bool new_info_added = false;

			for (size_t i = 0; i < sz; ++i) {
				for (size_t j = i + 1; j < sz; ++j) {
					std::vector<Clause> resolvents;
					resolveClauses(clauses[i], clauses[j], resolvents);

					for (const auto &res : resolvents) {
						if (res.empty()) {
							return false; // NO
						}

						if (!kb.count(res)) {
							new_clauses.push_back(res);
							kb.insert(res);
							new_info_added = true;
						}
					}
				}
			}

			if (!new_info_added) {
				return true; // YES
			}
		}
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string line;
	if (std::getline(std::cin, line)) {
		ResolutionSolver solver;
		solver.run(line);
	}

	return 0;
}