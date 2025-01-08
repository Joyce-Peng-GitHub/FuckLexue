#include <stdint.h>
#include <stdio.h>

int main(void) {
	int32_t n;
	if (scanf("%d", &n) == 1 && n >= 0) {
		for (size_t i = 0; i != n; ++i) {
			for (size_t j = 0; j != i; ++j) {
				putchar(' ');
			}
			for (size_t j = 0; j != n; ++j) {
				putchar('*');
			}
			putchar('\n');
		}
	} else {
		puts("Error!");
	}
	return 0;
}