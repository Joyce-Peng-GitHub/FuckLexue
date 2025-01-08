#include <stdint.h>
#include <stdio.h>

uint64_t gcd(uint64_t a, uint64_t b) {
	uint64_t t;
	if (a < b) {
		t = b;
		b = a;
		a = t;
	}
	while (b) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}
uint64_t lcm(uint64_t a, uint64_t b) {
	return (a / gcd(a, b) * b);
}

int main() {
	int64_t a, b;
	while (scanf("%lld%lld", &a, &b) == 2 && (a || b)) {
		if (a > 0 && b > 1) {
			printf("The GCD of %lld and %lld is:%llu\n"
				   "The LCM of %lld and %lld is:%llu\n",
				   a, b, gcd(a, b), a, b, lcm(a, b));
		} else {
			puts("Error!");
		}
	}
	return 0;
}