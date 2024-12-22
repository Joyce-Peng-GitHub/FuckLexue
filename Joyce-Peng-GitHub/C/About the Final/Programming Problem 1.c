#include <stddef.h>
#include <stdio.h>

int main(void) {
	size_t n;
	scanf("%zu", &n);
	for (size_t i = 1; i != n; ++i) {
		for (size_t j = 0; j != i; ++j) {
			putchar('*');
		}
		putchar('\n');
	}
	for (size_t i = 0; i != n; ++i) {
		putchar('*');
		putchar('*');
	}
	putchar('\n');
	for (size_t i = n - 1; i; --i) {
		for (size_t j = 0; j != i; ++j) {
			putchar('*');
		}
		putchar('\n');
	}
	return 0;
}