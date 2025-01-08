#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
	int32_t n;
	scanf("%d", &n);
	if (n <= 1) {
		return -1;
	}
	if (n == 2) {
		puts("The max prime number is 2");
		return 0;
	}
	for (int32_t i = ((n & 1) ? n : (n - 1)); i >= 3; i -= 2) {
		bool is_prime = true;
		for (int32_t j = 3; j * j <= i; ++j) {
			if (i % j == 0) {
				is_prime = false;
				break;
			}
		}
		if (is_prime) {
			printf("The max prime number is %d.\n", i);
			return 0;
		}
	}
	return -1;
}