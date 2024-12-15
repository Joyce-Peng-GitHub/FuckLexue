#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	char plate[10];
	gets(plate);
	size_t len = strlen(plate);
	if (len == 6 &&
		isupper(plate[0]) && isupper(plate[1]) && isupper(plate[2]) &&
		isdigit(plate[3]) && isdigit(plate[4]) && isdigit(plate[5])) {
		puts("The plate is a valid older style plate.");
	} else if (len == 7 &&
			   isdigit(plate[0]) && isdigit(plate[1]) && isdigit(plate[2]) && isdigit(plate[3]) &&
			   isupper(plate[4]) && isupper(plate[5]) && isupper(plate[6])) {
		puts("The plate is a valid newer style plate.");
	} else {
		puts("The plate is not valid.");
	}
	return 0;
}