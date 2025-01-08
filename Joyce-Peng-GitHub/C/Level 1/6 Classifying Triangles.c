#include <stdio.h>

int main(void) {
	long double a, b, c;
	scanf("%Lf%Lf%Lf", &a, &b, &c);
	if (a == b || b == c) {
		if (a == b && b == c) {
			puts("That's a equilateral triangle.");
		} else {
			puts("That's a isosceles triangle.");
		}
	} else {
		puts("That's a scalene triangle.");
	}
	return 0;
}