#include <stdio.h>
#include <stdlib.h>

#define BYTE unsigned char

BYTE X[8], c;

void showArr(BYTE A[], int n) {
	int i;
	for(i = 0; i < n; printf("%02x ", A[i++]));
	printf("\n");
}

#include "des.h"

int main(int argc, char *argv[]) {
	int i;
	BYTE P[8] = {'H', 'E', 'L', 'L', 'O', '!', '\0', '\0'};
	BYTE K[8] = {'P', 'A', 'S', 'S', 'W', 'O', 'R', 'D'};
	printf("Hello in Data Encryption Algorithm\n");
printf("P: ");
	showArr(P, 8);
printf("K: ");
	showArr(K, 8);

	encrypt_des(P, K);
//	decrypt_des(C, K);
	showArr(P, 8);
	return 0;
}
