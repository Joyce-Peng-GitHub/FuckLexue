#include <stdio.h>

int main(void) {
	long double cost;
	scanf("%Lf", &cost);
	printf("Enter the cost of the meal: \nThe tax is %.2Lf and the tip is %.2Lf, making the total %.2Lf.\n", cost * 0.05, 0.18 * cost, (0.05 + 1.18) * cost);
	return 0;
}