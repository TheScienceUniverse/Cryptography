#ifndef _SHIFT_CIPHER_H
#define _SHIFT_CIPHER_H

#include <ctype.h>

void pre_process(char *T, int *n) {
	int i, nx=0;
	char *X = (char*)malloc(*n);
	for(i=0; i<*n; i++) {
		if(isalpha(X[i])) {
			X[nx++] = T[i];
		}
	}
	realloc(X, nx);
	T = X, *n = nx;
}
void encrypt(char *P, int n, int k) {
	pre_process(P, &n);
	for(int i=0; i<n; i++) {
		P[i] = ((((P[i] - 'A') + k) % 26) + 'A');
	}
}
void decrypt(char *C, int n, int k) {
	for(int i=0; i<n; i++) {
		C[i] = ((((C[i] - 'A') + k) % 26) + 'A');
	}
}

#endif
