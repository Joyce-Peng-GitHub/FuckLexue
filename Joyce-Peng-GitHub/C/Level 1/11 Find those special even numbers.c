#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
	int32_t lower = -1, upper = -1;
	size_t cnt;
	while (scanf("%d%d", &lower, &upper)) {
		if (!lower && !upper) {
			break;
		}
		if (lower < 1000 || upper < lower || upper > 9999) {
			puts("Error");
			continue;
		}
		cnt = 0;
		for (int32_t x = ((lower & 1) ? (lower + 1) : lower); x <= upper; x += 2) {
			bool digits[10] = {false};
			digits[x % 10] = true;
			if (digits[(x / 10) % 10]) {
				continue;
			}
			digits[(x / 10) % 10] = true;
			if (digits[(x / 100) % 10]) {
				continue;
			}
			digits[(x / 100) % 10] = true;
			if (digits[x / 1000]) {
				continue;
			}
			printf("%d  ", x);
			++cnt;
		}
		printf("\ncounter=%zu\n", cnt);
	}
	return 0;
}