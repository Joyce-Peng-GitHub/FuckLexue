#include <stdint.h>
#include <stdio.h>

int main(void) {
	const char animals[][10] = {"Rat", "Ox", "Tiger", "Hare",
								"Dragon", "Snake", "Horse", "Sheep",
								"Monkey", "Rooster", "Dog", "Pig"};
	const int64_t base = 2008;
	int64_t year;
	scanf("%lld", &year);
	printf("%lld is the year of the %s.\n", year,
		   animals[((year - base) % 12 + 12) % 12]);
	return 0;
}