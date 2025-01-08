#include <stdint.h>
#include <stdio.h>

int main(void) {
	int32_t min = INT32_MAX, max = INT32_MIN, sum = 0;
	for (size_t i = 0; i != 10; ++i) {
		int32_t score;
		scanf("%d", &score);
		sum += score;
		if (score < min) {
			min = score;
		}
		if (score > max) {
			max = score;
		}
	}
	printf("Canceled Max Score:%d\nCanceled Min Score:%d\nAverage Score:%d\n",
		   max, min, (sum - max - min) / 8);
	return 0;
}