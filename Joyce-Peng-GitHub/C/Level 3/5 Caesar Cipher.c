#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	int op, offset;
	char lower[] = "abcdefghijklmnopqrstuvwxyz",
		 upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (scanf("%d %d ", &op, &offset); op; scanf("%d %d ", &op, &offset)) {
		if (op < 0 || op > 2) {
			puts("Wrong Input. Input Again.");
			for (int ch = getchar(); ~ch && ch != '\n'; ch = getchar())
				;
			continue;
		}
		offset %= 26;
		if (op == 2) {
			offset = -offset;
		}
		for (int ch = getchar(); ~ch && ch != '\n'; ch = getchar()) {
			if (isupper(ch)) {
				putchar(upper[(ch - 'A' + offset + 26) % 26]);
			} else if (islower(ch)) {
				putchar(lower[(ch - 'a' + offset + 26) % 26]);
			} else {
				putchar(ch);
			}
		}
		putchar('\n');
	}
	return 0;
}