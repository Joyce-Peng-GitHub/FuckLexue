#include <stdint.h>
#include <stdio.h>

int main(void) {
	int64_t n;
	scanf("%lld", &n);
	switch (n) {
	case 3:
		puts("That's a triangle.");
		break;
	case 4:
		puts("That's a quadrangle");
		break;
	case 5:
		puts("That's a pentagon.");
		break;
	case 6:
		puts("That's a hexagon.");
		break;
	case 7:
		puts("That's a heptagon.");
		break;
	case 8:
		puts("That's a octagon.");
		break;
	case 9:
		puts("That's an enneagon.");
		break;
	case 10:
		puts("That's a decagon.");
		break;
	default:
		puts("That number of sides is not supported by this program.");
		break;
	}
	return 0;
}