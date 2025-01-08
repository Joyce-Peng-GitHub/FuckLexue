#include <stdint.h>
#include <stdio.h>

const size_t days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(void) {
	size_t q;
	scanf("%zu", &q);
	while (q--) {
		size_t year, month, day;
		scanf("%zu%zu%zu", &year, &month, &day);
		size_t cnt = 0;
		for (size_t y = 1990; y != year; ++y) {
			cnt += 365 + (y % 4 == 0 && (y % 100 || y % 400 == 0));
		}
		for (size_t m = 1; m != month; ++m) {
			cnt += days[m];
		}
		if (month > 2 && year % 4 == 0 && (year % 100 || year % 400 == 0)) {
			++cnt;
		}
		cnt += day;
		printf((((cnt - 1) % 5 < 3)
					? "He was fishing on %zu.%zu.%zu\n"
					: "He was basking on %zu.%zu.%zu\n"),
			   year, month, day);
	}
	return 0;
}