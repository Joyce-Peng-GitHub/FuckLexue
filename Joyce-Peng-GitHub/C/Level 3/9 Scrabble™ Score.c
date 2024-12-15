#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
	uint64_t points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	uint64_t sum = 0;
	for (char ch = getchar(); ~ch; ch = getchar()) {
		if (islower(ch)) {
			sum += points[ch - 'a'];
		} else if (isupper(ch)) {
			sum += points[ch - 'A'];
		}
	}
	printf("%llu\n", sum);
	return 0;
}