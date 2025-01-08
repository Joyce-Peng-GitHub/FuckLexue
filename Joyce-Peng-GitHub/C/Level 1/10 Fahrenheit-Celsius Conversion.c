#include <stdint.h>
#include <stdio.h>

int main(void) {
	int32_t op;
	double t;
	while (scanf("%d%lf", &op, &t) != EOF) {
		if (op == 1) {
			printf("The Centigrade is %.2lf\n", (t - 32) * 5 / 9);
		} else if (op == 2) {
			printf("The Fahrenheit is %.2lf\n", t * 9 / 5 + 32);
		} else {
			puts("Wrong input!");
		}
	}
	return 0;
}