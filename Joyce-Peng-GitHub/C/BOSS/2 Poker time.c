#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void blackjack(void);
void tractor(void);

int main(void) {
	// freopen("2.in", "r", stdin);
	// freopen("2.out", "w", stdout);
	int ch;
	char ops[11];
	bool not_reached_endline;
	while (true) {
		puts("1. Blackjack\n2. Tractor\n0. Exit\nInput your choice:");
	_ENTRY:
		fgets(ops, 10, stdin);
		not_reached_endline = true;
		for (char *p = ops; *p; ++p) {
			if (*p == '\n' || *p == '\r') {
				not_reached_endline = false;
				*p = '\0';
				break;
			}
		}
		if (ops[1]) {
			while (not_reached_endline) { // In case that the input includes a super long string
				fgets(ops, 10, stdin);
				for (char *p = ops; *p; ++p) {
					if (*p == '\n' || *p == '\r') {
						not_reached_endline = false;
						*p = '\0';
						break;
					}
				}
			}
			puts("Wrong Input. Input Again.");
			goto _ENTRY;
		}
		switch (ops[0]) {
		case '1':
			blackjack();
			break;
		case '2':
			tractor();
			break;
		case '0':
			goto _RETURN;
		default:
			puts("Wrong Input. Input Again.");
			goto _ENTRY;
		}
		puts("Do you want to play again? (Y/N)");
		fgets(ops, 10, stdin);
		ch = ops[0];
		not_reached_endline = true;
		for (char *p = ops; *p; ++p) {
			if (*p == '\n' || *p == '\r') {
				not_reached_endline = false;
				*p = '\0';
				break;
			}
		}
		while (not_reached_endline) {
			if (!fgets(ops, 10, stdin)) {
				return 0;
			}
			fgets(ops, 10, stdin);
			for (char *p = ops; *p; ++p) {
				if (*p == '\n' || *p == '\r') {
					not_reached_endline = false;
					*p = '\0';
					break;
				}
			}
		}
		if (ch == 'N') {
			goto _RETURN;
		}
	}
_RETURN:
	return 0;
}

typedef struct {
	char suit;
	uint8_t value;
} Card;
int convertCard(Card *p, const char *s, size_t n) {
	if (n < 2 || (*s != 'H' && *s != 'S' && *s != 'D' && *s != 'C')) {
		return -1;
	}
	char suit = *s;
	if (!isgraph(*(++s))) {
		return -1;
	}
	if (n > 2 && isgraph(*(s + 1))) {
		if (*s == '1' && *(s + 1) == '0' && (n == 3 || !isgraph(*(s + 2)))) {
			p->value = 10;
		} else {
			return -1;
		}
	} else if (*s == 'J') {
		p->value = 11;
	} else if (*s == 'Q') {
		p->value = 12;
	} else if (*s == 'K') {
		p->value = 13;
	} else if (*s == 'A') {
		p->value = 14;
	} else if ('2' <= *s && *s <= '9') {
		p->value = (*s ^ '0');
	} else {
		return -1;
	}
	p->suit = suit;
	return 0;
}
size_t convertCards(Card cards[], size_t max_cards_num, const char *s) {
	size_t cnt = 0;
	for (const char *p = s + 1;; s = (++p)) {
		while (isgraph(*p)) {
			++p;
		}
		if (cnt == max_cards_num) {
			return -1;
		}
		if (convertCard(cards + cnt, s, p - s)) {
			return -1;
		}
		for (size_t i = 0; i != cnt; ++i) {
			if (cards[i].suit == cards[cnt].suit && cards[i].value == cards[cnt].value) {
				return -1;
			}
		}
		++cnt;
		if (!*p) {
			return cnt;
		}
	}
}
typedef struct {
	int32_t score;
	bool has_blackjack;
} BlackjackScore;
BlackjackScore blackjackCalcScore(const Card cards[], size_t n) {
#define BLACKJACK_SCORE_LIMIT 21
	int32_t res = 0;
	size_t cnt_a = 0;
	size_t cnt_ten = 0;
	for (size_t i = 0; i != n; ++i) {
		if (cards[i].value == 14) {
			++cnt_a;
			++res;
		} else if (cards[i].value < 10) {
			res += cards[i].value;
		} else {
			++cnt_ten;
			res += 10;
		}
		if (res > BLACKJACK_SCORE_LIMIT) {
			return (BlackjackScore){-1, false};
		}
	}
	if (res > BLACKJACK_SCORE_LIMIT) {
		return (BlackjackScore){-1, false};
	}
	size_t cnt_ace = MIN((size_t)(BLACKJACK_SCORE_LIMIT - res) / 10, cnt_a);
	return (BlackjackScore){res + cnt_ace * 10, (cnt_ace && cnt_ten)};
#undef BLACKJACK_SCORE_LIMIT
}
void blackjack(void) {
#define BLACKJACK_SCORE_LIMIT 21
	puts("You're playing Blackjack.\nPlease input cards for each player:");
	char dealer[51], player[51];
	fgets(dealer, 50, stdin);
	fgets(player, 50, stdin);
	{
		char *p = dealer;
		while (*p && *p != '\n' && *p != '\r') {
			++p;
		}
		*p = '\0';
		p = player;
		while (*p && *p != '\n' && *p != '\r') {
			++p;
		}
		*p = '\0';
	}
	Card dealer_cards[10], player_cards[10];
	size_t cnt_dealer_cards = convertCards(dealer_cards, 10, dealer),
		   cnt_player_cards = convertCards(player_cards, 10, player);
	if (cnt_dealer_cards == (size_t)-1 || cnt_player_cards == (size_t)-1) {
		puts("Input Error!");
		return;
	}
	for (size_t i = 0, j; i != cnt_dealer_cards; ++i) {
		for (j = 0; j != cnt_player_cards; ++j) {
			if (dealer_cards[i].suit == player_cards[j].suit &&
				dealer_cards[i].value == player_cards[j].value) {
				puts("Input Error!");
				return;
			}
		}
	}
	BlackjackScore
		dealer_score = blackjackCalcScore(dealer_cards, cnt_dealer_cards),
		player_score = blackjackCalcScore(player_cards, cnt_player_cards);
	if (dealer_score.has_blackjack && player_score.has_blackjack) {
		puts("Draw!");
		return;
	}
	if (player_score.has_blackjack) {
		puts("B wins with a Blackjack!");
		return;
	}
	if (dealer_score.has_blackjack) {
		puts("A wins with a Blackjack!");
		return;
	}
	if (dealer_score.score == player_score.score) {
		puts("Draw!");
		return;
	}
	if (dealer_score.score > player_score.score) {
		printf("A wins by %" PRId32 " points!\n", dealer_score.score - player_score.score);
	} else {
		printf("B wins by %" PRId32 " points!\n", player_score.score - dealer_score.score);
	}
#undef BLACKJACK_SCORE_LIMIT
}
typedef enum {
	SINGLE,
	PAIR,
	FLUSH,
	BOMB,
	STRAIGHT_FLUSH
} TractorType;
typedef enum {
	CLUB,
	DIAMOND,
	SPADE,
	HEART
} SuitOrder;
SuitOrder suitToOrder(char suit) {
	switch (suit) {
	case 'C':
		return CLUB;
	case 'D':
		return DIAMOND;
	case 'S':
		return SPADE;
	case 'H':
		return HEART;
	default:
		return -1;
	}
}
int compCards(const Card *p, const Card *q) {
	return ((p->value == q->value)
				? (suitToOrder(p->suit) - suitToOrder(q->suit))
				: (p->value - q->value));
}
int comp(const void *p, const void *q) { return compCards((const Card *)p, (const Card *)q); }
TractorType cardsToTractorType(const Card cards[]) {
	if (cards[0].suit == cards[1].suit &&
		cards[1].suit == cards[2].suit &&
		cards[0].value + 1 == cards[1].value &&
		cards[1].value + 1 == cards[2].value) {
		return STRAIGHT_FLUSH;
	}
	if (cards[0].value == cards[1].value && cards[1].value == cards[2].value) {
		return BOMB;
	}
	if (cards[0].value + 1 == cards[1].value &&
		cards[1].value + 1 == cards[2].value) {
		return FLUSH;
	}
	if (cards[0].value == cards[1].value ||
		cards[0].value == cards[2].value ||
		cards[1].value == cards[2].value) {
		return PAIR;
	}
	return SINGLE;
}
const char *valueToString(uint8_t value) {
	switch (value) {
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	case 10:
		return "10";
	case 11:
		return "J";
	case 12:
		return "Q";
	case 13:
		return "K";
	case 14:
		return "A";
	default:
		return NULL;
	}
}
void tractor(void) {
	puts("You're playing Tractor.\nPlease input cards for each player:");
	char dealer[16], player[16];
	fgets(dealer, 15, stdin);
	fgets(player, 15, stdin);
	{
		char *p = dealer;
		while (*p && *p != '\n' && *p != '\r') {
			++p;
		}
		*p = '\0';
		p = player;
		while (*p && *p != '\n' && *p != '\r') {
			++p;
		}
		*p = '\0';
	}
	Card dealer_cards[3], player_cards[3];
	size_t cnt_dealer_cards = convertCards(dealer_cards, 3, dealer),
		   cnt_player_cards = convertCards(player_cards, 3, player);
	if (cnt_dealer_cards == (size_t)-1 || cnt_player_cards == (size_t)-1 ||
		cnt_dealer_cards < 3 || cnt_player_cards < 3) {
		puts("Input Error!");
		return;
	}
	for (size_t i = 0, j; i != cnt_dealer_cards; ++i) {
		for (j = 0; j != cnt_player_cards; ++j) {
			if (dealer_cards[i].suit == player_cards[j].suit &&
				dealer_cards[i].value == player_cards[j].value) {
				puts("Input Error!");
				return;
			}
		}
	}
	qsort(dealer_cards, 3, sizeof(Card), comp);
	qsort(player_cards, 3, sizeof(Card), comp);
	TractorType dealer_type = cardsToTractorType(dealer_cards),
				player_type = cardsToTractorType(player_cards);
	if (dealer_type > player_type) {
		puts("Winner is A!");
	} else if (dealer_type < player_type) {
		puts("Winner is B!");
	} else {
		for (size_t i = 2; ~i; --i) {
			int cmp = compCards(dealer_cards + i, player_cards + i);
			if (cmp) {
				if (cmp < 0) {
					puts("Winner is B!");
				} else {
					puts("Winner is A!");
				}
				break;
			}
		}
	}
	putchar('A');
	putchar(':');
	for (size_t i = 2; ~i; --i) {
		printf(" %c%s", dealer_cards[i].suit, valueToString(dealer_cards[i].value));
	}
	putchar('\n');
	putchar('B');
	putchar(':');
	for (size_t i = 2; ~i; --i) {
		printf(" %c%s", player_cards[i].suit, valueToString(player_cards[i].value));
	}
	putchar('\n');
}