#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
#define N 6
	const uint32_t ten_to_power[N + 1] = {1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6};
	size_t n;
	scanf("%zu", &n);
	bool exist = false;
	for (uint32_t x = ten_to_power[n - 1]; x != ten_to_power[n]; ++x) {
		uint32_t pow_sum = 0;
		for (uint32_t t = x; t; t /= 10) {
			if ((pow_sum += pow(t % 10, n)) > x) {
				break;
			}
		}
		if (pow_sum == x) {
			printf("%u\n", x);
			exist = true;
		}
	}
	if (!exist) {
		puts("No output.");
	}
	return 0;
}