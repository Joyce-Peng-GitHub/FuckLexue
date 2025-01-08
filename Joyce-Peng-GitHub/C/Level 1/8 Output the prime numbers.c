#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
#define N 100000
	uint32_t n, primes[N] = {2};
	size_t m = 1;
	bool not_prime[N + 1] = {true, true};
	scanf("%u", &n);
	for (uint32_t i = 3; i <= n; ++i) {
		if (!not_prime[i]) {
			primes[m++] = i;
			for (uint32_t j = 2; j * i <= n; ++j) {
				not_prime[j * i] = true;
			}
		}
	}
	for (size_t i = 0; i != m; ++i) {
		printf("%d", primes[i]);
		putchar((i % 5 != 4) ? '\t' : '\n');
	}
	return 0;
}