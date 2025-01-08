#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool is_leap_year(size_t year) {
	return (year % 4 == 0 && (year % 100 || year % 400 == 0));
}
size_t days_since_1990_01_01(size_t year, size_t month, size_t day) {
	const size_t days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	size_t cnt = 0;
	for (size_t y = 1990; y != year; ++y) {
		cnt += 365 + is_leap_year(y);
	}
	for (size_t m = 1; m != month; ++m) {
		cnt += days[m];
	}
	if (month > 2 && is_leap_year(year)) {
		++cnt;
	}
	cnt += day;
	return cnt;
}
const char *check_error(int64_t year, int64_t month, int64_t day) {
	const size_t days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year < 1990) {
		return "Year";
	}
	if (month <= 0 || month > 12) {
		return "Month";
	}
	if (days <= 0 || (day > days[month] && (month != 2 || !is_leap_year(year) || day != 29))) {
		return "Day";
	}
	return NULL;
}

int main(void) {
	size_t q;
	scanf("%zu", &q);
	while (q--) {
		int64_t year, month, day;
		scanf("%zu%zu%zu", &year, &month, &day);
		const char *err = check_error(year, month, day);
		if (err) {
			printf("%s is wrong!\n", err);
		} else {
			printf((((days_since_1990_01_01(year, month, day) - 1) % 5 < 3)
						? "He was fishing on %zu.%zu.%zu\n"
						: "He was basking on %zu.%zu.%zu\n"),
				   year, month, day);
		}
	}
	return 0;
}