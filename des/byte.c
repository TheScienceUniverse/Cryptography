#include <stdio.h>
unsigned char X[] = {
16, 7, 20, 21, 29, 12, 28, 17,
1, 15, 23, 26, 5, 18, 31, 10,
2, 8, 24, 14, 32, 27, 3, 9,
19, 13, 30, 6, 22, 11, 4, 25 };
int main() {
	int i;
	for(i = 0; i < 32; i++)
		printf("0x%02x, ", X[i] - 1);
	printf("\n");
	return 0;
}
