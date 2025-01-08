#include <stdio.h>

int precedence(char ch) {
	switch (ch) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return -1;
	}
}

int main(void) {
	char s[100000];
	gets(s);
	char ch = s[0];
	int ret = precedence(ch);
	if (~ret) {
		printf("The precedence of '%c' is: %d\n", ch, ret);
	} else {
		printf("Error: '%s' is not a valid operator.\n", s);
	}
	return 0;
}