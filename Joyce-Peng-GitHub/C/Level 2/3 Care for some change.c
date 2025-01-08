#include <stdint.h>
#include <stdio.h>

int main(void) {
	size_t n;
	scanf("%zu", &n);
	if (n % 8) {
		puts("No change.");
	} else {
		printf("%zu,%zu,%zu\n", n / 4 * 25, n / 2 * 15, n / 8 * 45);
	}
	return 0;
}