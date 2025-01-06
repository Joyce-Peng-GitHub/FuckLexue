#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
	int32_t first, last;
	scanf("%d%d", &first, &last);
	bool has_result = false;
	printf("Perfect numbers in the range %d to %d are: ", first, last);
	for (int32_t i = first; i <= last; ++i) {
		int32_t sum = 0;
		for (int32_t j = 1; j != i; ++j) {
			if (i % j == 0) {
				sum += j;
			}
		}
		if (sum == i) {
			if (has_result) {
				printf(", ");
			} else {
				has_result = true;
			}
			printf("%d", i);
		}
	}
	if (!has_result) {
		fputs("No result", stdout);
	}
	putchar('.');
	putchar('\n');
	return 0;
}