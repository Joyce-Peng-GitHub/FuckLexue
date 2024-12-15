#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

void printbase(uint64_t x, uint32_t base) {
	static const char digits[] = "0123456789ABCDEF";
	if (x) {
		if (x >= base) {
			printbase(x / base, base);
		}
		putchar(digits[x % base]);
	} else {
		putchar('0');
	}
}

int main(void) {
	uint64_t x;
	uint32_t base;
	scanf("%" SCNu64 "%" SCNu32, &x, &base);
	printf("%" PRIu64 " in %" PRIu32 " based system is ", x, base);
	printbase(x, base);
	putchar('\n');
	return 0;
}