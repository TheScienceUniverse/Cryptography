#ifndef _SHIFT_CIPHER_H
#define _SHIFT_CIPHER_H

#include <ctype.h>

void pre_process(BYTE *T, UL *n) {
	int i, nx=0;
	BYTE *X = (BYTE*)malloc(*n);
	for(i=0; i<*n; i++) {
		if(isalpha(T[i]) > 0) {
			X[nx++] = toupper(T[i]);
		}
	}
	*n = nx;
	for(i=0; i<*n; i++) {
		T[i] = X[i];
	}
}
void encrypt(BYTE *P, UL *n, int k) {
	pre_process(P, n);
	for(int i=0; i<*n; i++) {
		P[i] = ((((P[i] - 'A') + k) % 26) + 'A');
	}
}
void decrypt(BYTE *C, UL *n, int k) {
	for(int i=0; i<*n; i++) {
		C[i] = ((((C[i] - 'A') + 26 - k) % 26) + 'A');
	}
}

#endif
