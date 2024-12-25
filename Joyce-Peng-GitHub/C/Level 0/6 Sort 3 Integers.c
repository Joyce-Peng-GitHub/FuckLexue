#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
	int64_t a, b, c;
	scanf("%" SCNd64 "%" SCNd64 "%" SCNd64, &a, &b, &c);
	int64_t min = ((a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c)),
			max = ((a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c)),
			mid = a - min + b - max + c;
	printf("Enter the first number: \nEnter the second number: \nEnter the third number: \nThe numbers in sorted order are: %" PRId64 " %" PRId64 " %" PRId64 ".\n", min, mid, max);
	return 0;
}