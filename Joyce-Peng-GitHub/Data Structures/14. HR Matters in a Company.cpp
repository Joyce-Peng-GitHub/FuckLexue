#include <bits/stdc++.h>

inline void redirectIO() {
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

template <typename Iter>
using RequireFwdIter = typename std::enable_if<
	std::is_base_of<
		std::forward_iterator_tag,
		typename std::iterator_traits<Iter>::iterator_category>::value>::type;

struct Employee {
	std::list<size_t> subs;
	std::string name;
	std::list<size_t> *frm;
	std::list<size_t>::iterator pos;

	Employee(std::string name, std::list<size_t> *frm, std::list<size_t>::iterator pos)
		: name(std::move(name)), frm(frm), pos(std::move(pos)) {}
};

std::vector<std::unique_ptr<Employee>> employees;
std::unordered_map<std::string, size_t> name_to_id;
std::list<size_t> super;

void print(size_t id, size_t dep) {
	for (size_t i = 0; i < dep; ++i) std::cout << '+';
	std::cout << employees[id]->name << '\n';
	++dep;
	for (auto sub : employees[id]->subs) print(sub, dep);
}
inline void print() {
	print(super.front(), 0);
	for (unsigned i = 0; i < 60; ++i) std::cout << '-';
	std::cout << '\n';
}

inline void hire(const std::string &lead, std::string sub) {
	size_t lead_id = name_to_id[lead], sub_id = employees.size();
	employees[lead_id]->subs.push_back(sub_id);
	employees.push_back(std::unique_ptr<Employee>(
		new Employee(std::move(sub),
					 &employees[lead_id]->subs,
					 std::prev(employees[lead_id]->subs.end()))));
	name_to_id[employees.back()->name] = sub_id;
}

void replace(size_t id) {
	if (employees[id]->subs.empty()) {
		employees[id]->frm->erase(employees[id]->pos);
		return;
	}
	size_t heit = employees[id]->subs.front();
	replace(heit);
	employees[heit]->subs = std::move(employees[id]->subs);
	employees[heit]->frm = employees[id]->frm;
	employees[heit]->pos = employees[id]->pos;
	assert(employees[heit]->frm);
	*employees[heit]->pos = heit;
}

inline void preprocess() {
	std::string ceo;
	std::getline(std::cin, ceo);
	super.push_back(0);
	employees.push_back(std::unique_ptr<Employee>(new Employee(std::move(ceo),
															   &super,
															   super.begin())));
}

template <typename Iter, typename = RequireFwdIter<Iter>>
inline std::vector<size_t> prefFuncOf(Iter begin, Iter end) {
	auto pi = std::vector<size_t>(std::distance(begin, end));
	end = std::next(begin);
	for (size_t i = 1, j; i < pi.size(); ++i, ++end) {
		for (j = pi[i - 1]; j && *end != *std::next(begin, j); j = pi[j - 1]);
		pi[i] = j + (*end == *std::next(begin, j));
	}
	return pi;
}

template <typename Iter>
inline std::vector<size_t>
kmp(Iter text_begin, Iter text_end,
	Iter pattern_begin, Iter pattern_end,
	const typename std::iterator_traits<Iter>::value_type &sep = -1) {
	size_t text_sz = std::distance(text_begin, text_end),
		   pattern_sz = std::distance(pattern_begin, pattern_end);
	auto seq = std::vector<typename std::iterator_traits<Iter>::value_type>(
		text_sz + 1 + pattern_sz);
	std::copy(pattern_begin, pattern_end, seq.begin());
	std::copy(text_begin, text_end, seq.end() - text_sz);
	seq[pattern_sz] = sep;
	auto pi = prefFuncOf(seq.begin(), seq.end());
	std::vector<size_t> res;
	for (size_t i = (pattern_sz << 1); i != pi.size(); ++i) {
		if (pi[i] == pattern_sz) {
			res.emplace_back(i - (pattern_sz << 1));
		}
	}
	return res;
}

inline void solve(const std::string &line) {
	assert(line != "end");

	if (line == "print") {
		print();
		return;
	}

	if (std::strncmp(line.c_str(), "fire ", 5) == 0) {
		replace(name_to_id[line.substr(5)]);
		return;
	}

	const char HIRES[] = " hires ";
	auto kmp_res = kmp(line.c_str(), line.c_str() + line.size(),
					   HIRES, HIRES + sizeof(HIRES) - 1);
	assert(kmp_res.size() == 1);
	hire(line.substr(0, kmp_res[0]), line.substr(kmp_res[0] + sizeof(HIRES) - 1));
}

inline int mainLoop() {
	std::string line;
	while (std::getline(std::cin, line) && line != "end") solve(line);
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