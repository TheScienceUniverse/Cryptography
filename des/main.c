#include <stdio.h>
#include <stdlib.h>

#include "data.h"

BYTE X[8], c;

void showArr(BYTE A[], int n) {
	int i;
	for(i = 0; i < n; printf("%02x", A[i++]));
	printf("\n");
}
void showArrBit(BYTE A[], int n) {
	int i;
	for(i = 0; i < n; printf("%x", A[i++]));
	printf("\n");
}
void clearArr(BYTE A[], int n) {
	int i;
	for(i = 0; i < n; A[i++] = 0);
}

#include "des.h"

int main(int argc, char *argv[]) {
	if(argc < 2) {
		perror("Missing Input File\n");
		exit(1);
	}
	FILE *fpi = fopen(argv[1], "r");
	if(fpi == NULL) {
		perror("Input File Openning ERROR\n");
		exit(1);
	}
	FILE *fpo = fopen("op.txt", "w+");
	if(fpo == NULL) {
		perror("Output File Openning ERROR\n");
		exit(1);
	}


	BYTE X[8], x;

	fseek(fpi, 1, SEEK_END);
	long f_ic = 0;		// File Index Counter
	long f_sz = ftell(fpi);	// File SiZe
	rewind(fpi);
	printf("File Size: %ld bytes.\n", f_sz);

	BYTE K[8] = {'P', 'A', 'S', 'S', 'W', 'O', 'R', 'D'};
	size_t s;

	int i, c = 0;
	do {
		clearArr(X, 8);
		for(i = 0; i < 8; i++) {
			s = fread(&x, 1, 1, fpi);
			if(s == 1) {
				++f_ic;
				X[i] = x;
			} else {
				break;
			}
		}
		printf("Index = %ld\n", f_ic);
		printf("P: ");
		showArr(X, 8);
		e_des(X, K);
		// Tricking
		/*for(i = 0; i < 8; i++) {
			X[i] = 'A' + (X[i] % 26);
		}*/
		printf("C: ");
		showArr(X, 8);
		fwrite(X, 8, 1, fpo);
		if(s == 0)
			break;

	} while(f_ic < f_sz);


//	size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
//	size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);


/*
	BYTE P[8] = {'H', 'E', 'L', 'L', 'O', '!', 0, 0};
	BYTE K[8] = {'P', 'A', 'S', 'S', 'W', 'O', 'R', 'D'};
	printf("Hello from Data Encryption Algorithm\n");
printf("P[8]: ");
	showArr(P, 8);
printf("K[8]: ");
	showArr(K, 8);

	e_des(P, K);
//	d_des(C, K);
printf("C[8]: ");
	showArr(P, 8);
*/
	fclose(fpi);
	fclose(fpo);
	return 0;
}
