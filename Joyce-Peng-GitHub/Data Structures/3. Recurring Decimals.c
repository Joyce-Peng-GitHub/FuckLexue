#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeImpl {
	int data;
	struct NodeImpl *next;
} Node;

void output(Node *, int);
void change(int, int, Node *);

void output(Node *head, int lim) {
	int cnt = 0;

	printf("0.");
	while (head->next != NULL && cnt < lim) {
		printf("%d", head->next->data);
		head = head->next;
		cnt++;
	}
	printf("\n");
}

void destroy(Node *head) {
	Node **freed = NULL;
	size_t sz = 0, cap = 0;
	while (head) {
		bool found = false;
		for (size_t i = 0; i < sz; i++) {
			if (head == freed[i]) {
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
		Node *next = head->next;
		free(head);
		if (sz == cap) {
			cap = cap ? (cap << 1) : 1;
			freed = (Node **)realloc(freed, cap * sizeof(Node *));
			assert(freed);
		}
		freed[sz++] = head;
		head = next;
	}
	free(freed);
}

int main() {
	int n, m, k;
	Node *head;

	scanf("%d%d%d", &n, &m, &k);
	head = (Node *)malloc(sizeof(Node));
	head->next = NULL;
	change(n, m, head);
	output(head, k);
	destroy(head);
	return 0;
}

Node *find(int n, int m, int target, Node *head) {
	assert(0 < n && n < m && head);
	while (n && head) {
		if (n == target) {
			return head->next;
		}
		head = head->next;
		n = ((n << 1) + (n << 3)) % m; // 10 * n % m
	}
	return NULL;
}

void change(int n, int m, Node *head) {
	assert(0 < n && n < m && head);
	Node *cur = head;
	int n0 = n;
	while (n) {
		Node *found = find(n0, m, n, head);
		if (found) {
			cur->next = found;
			return;
		}
		div_t qr = div((n << 1) + (n << 3), m); // 10 * n / m, 10 * n % m
		Node *new_node = (Node *)malloc(sizeof(Node));
		assert(new_node);
		new_node->data = qr.quot;
		new_node->next = NULL;
		cur->next = new_node;
		cur = new_node;
		n = qr.rem;
	}
}