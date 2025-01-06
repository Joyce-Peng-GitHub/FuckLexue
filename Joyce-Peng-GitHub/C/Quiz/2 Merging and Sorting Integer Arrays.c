#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
	return (*(int *)a - *(int *)b);
}

int main(void) {
	size_t n1, n2;
	scanf("%zu", &n1);
	int *arr = (int *)malloc(n1 * sizeof(int));
	for (size_t i = 0; i != n1; i++) {
		scanf("%d", arr + i);
	}
	scanf("%zu", &n2);
	arr = realloc(arr, (n1 + n2) * sizeof(int));
	for (size_t i = 0; i != n2; i++) {
		scanf("%d", arr + n1 + i);
	}
	qsort(arr, n1 + n2, sizeof(int), compare);
	printf("Enter the size of the first array: \n"
		   "Enter the elements of the first array: \n"
		   "Enter the size of the second array: \n"
		   "Enter the elements of the second array: \n"
		   "Merged array in ascending order with unique elements:");
	for (size_t i = 0, j, n = n1 + n2; i != n; i = j) {
		printf(" %d", arr[i]);
		for (j = i + 1; j != n && arr[i] == arr[j]; ++j)
			;
	}
	putchar('\n');
	free(arr);
	arr = NULL;
	return 0;
}