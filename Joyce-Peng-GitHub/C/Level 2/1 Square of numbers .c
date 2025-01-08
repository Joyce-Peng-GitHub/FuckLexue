#include <stdint.h>
#include <stdio.h>

int main(void) {
	uint64_t n;
	uint64_t m = 1;
	scanf("%zu", &n);
	for (uint64_t i = 1, j; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			printf("%3llu", (m++));
		}
		putchar('\n');
	}
	return 0;
}