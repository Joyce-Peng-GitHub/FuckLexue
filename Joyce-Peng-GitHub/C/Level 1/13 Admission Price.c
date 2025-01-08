#include <stdint.h>
#include <stdio.h>

int main(void) {
	uint32_t age, tot = 0;
	puts("Enter the age of the guest (blank to finish):");
	while (scanf("%u", &age) == 1) {
		puts("Enter the age of the guest (blank to finish):");
		if (3 <= age && age <= 12) {
			tot += 14;
		} else if (age >= 65) {
			tot += 18;
		} else if (age > 2) {
			tot += 23;
		}
	}
	printf("The total for that group is $%u.00\n", tot);
	return 0;
}