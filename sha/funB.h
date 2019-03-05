#ifndef _FUNB_H
#define _FUNB_H

/*
 * This library is for "Basic FUNctions"
 * that are required for the Project
 */

void showArr(UINT A[], int n) {
	int i;
	for(i = 0; i < n; i++) {
		printf("%08x ", A[i]);
	}
	printf("\n");
}
void clearArr(UINT A[], int n) {
	int i;
	for(i = 0; i < n; A[i++] = 0);
}

UINT left_rotate(UINT x, int n) {
	x = (x << n) | (x >> (32 - n));
	return x;
}

#endif
