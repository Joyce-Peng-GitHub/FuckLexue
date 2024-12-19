#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char card[4];
} poker_t;
int suit_to_order(char suit) {
	switch (suit) {
	case 'C':
		return 0;
	case 'D':
		return 1;
	case 'S':
		return 2;
	case 'H':
		return 3;
	default:
		return -1;
	}
}
int value_to_order(const char value[]) {
	if (isdigit(value[0])) {
		return ((value[0] == '1' && value[1] == '0') ? 10 : (value[0] ^ '0'));
	}
	switch (value[0]) {
	case 'J':
		return 11;
	case 'Q':
		return 12;
	case 'K':
		return 13;
	case 'A':
		return 14;
	default:
		return -1;
	}
}
int comp(const void *p, const void *q) {
	const poker_t *r = (const poker_t *)p, *s = (const poker_t *)q;
	return ((r->card[0] == s->card[0])
				? (value_to_order(s->card + 1) - value_to_order(r->card + 1))
				: (suit_to_order(s->card[0]) - suit_to_order(r->card[0])));
}

int main(void) {
	poker_t players[2][3];
	scanf("%s %s %s\n%s %s %s\n",
		  players[0][0].card, players[0][1].card, players[0][2].card,
		  players[1][0].card, players[1][1].card, players[1][2].card);
	for (int i = 0, j, k; i != 2; ++i) {
		for (j = 0; j != 3; ++j) {
			if (suit_to_order(players[i][j].card[0]) == -1 || value_to_order(players[i][j].card + 1) == -1) {
				puts("Input Error!");
				return 0;
			}
			for (k = 0; k != j; ++k) {
				if (!strcmp(players[i][j].card, players[i][k].card)) {
					puts("Input Error!");
					return 0;
				}
			}
		}
	}
	qsort(players[0], 3, sizeof(poker_t), comp);
	qsort(players[1], 3, sizeof(poker_t), comp);
	char winner = 'X';
	for (size_t i = 0; i != 3; ++i) {
		if (comp(players[0] + i, players[1] + i)) {
			winner = ((comp(players[0] + i, players[1] + i) < 0) ? 'A' : 'B');
			break;
		}
	}
	printf("Winner is %c!\nA: %s %s %s\nB: %s %s %s\n", winner,
		   players[0][0].card, players[0][1].card, players[0][2].card,
		   players[1][0].card, players[1][1].card, players[1][2].card);
	return 0;
}