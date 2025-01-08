#include <math.h>
#include <stdio.h>

typedef struct {
	double x, y;
} point_t;

int main(void) {
	point_t first, cur;
	double res = 0.0;
	puts("Enter the first x-coordinate:\n"
		 "Enter the first y-coordinate:\n"
		 "Enter the next x-coordinate (blank to quit):");
	scanf("%lf%lf", &first.x, &first.y);
	point_t prev = first;
	while (scanf("%lf%lf", &cur.x, &cur.y) == 2) {
		puts("Enter the next y-coordinate:\nEnter the next x-coordinate (blank to quit):");
		res += sqrt(pow(cur.x - prev.x, 2) + pow(cur.y - prev.y, 2));
		prev = cur;
	}
	printf("The perimeter of that polygon is %.6lf\n", res + sqrt(pow(first.x - prev.x, 2) + pow(first.y - prev.y, 2)));
	return 0;
}