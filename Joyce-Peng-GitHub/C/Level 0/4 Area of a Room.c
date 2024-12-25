#include <stdio.h>

int main(void) {
	long double l, w;
	scanf("%LF%LF", &l, &w);
	printf("Enter the length of the room in feet: \nEnter the width of the room in feet: \nThe area of the room is %.2Lf square feet.\n", l * w);
	return 0;
}