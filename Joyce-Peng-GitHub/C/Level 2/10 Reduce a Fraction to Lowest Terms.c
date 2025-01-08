#include <stdint.h>
#include <stdio.h>

uint64_t gcd(uint64_t a, uint64_t b) {
	uint64_t t = a;
	if (a < b) {
		a = b;
		b = t;
	}
	while (b) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

int main(void) {
	uint64_t a, b;
	scanf("%llu,%llu", &a, &b);
	if (!b) {
		puts("Denominator cannot be zero.");
	} else {
		printf("%llu/%llu can be reduced to %llu/%llu.\n",
			   a, b, a / gcd(a, b), b / gcd(a, b));
	}
	return 0;
}