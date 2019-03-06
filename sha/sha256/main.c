#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "data.h"
#include "funB.h"
#include "sha256.h"

int main(int argc, char *argv[]) {
	if(argc < 2) {
		perror("Missing Input File\n");
		exit(1);
	}
	// system(strcat(strcat("cp ", argv[1]), " ip.bin"));
	FILE *fpi = fopen(argv[1], "rb+");
	if(fpi == NULL) {
		perror("Input File Openning ERROR\n");
		exit(1);
	}

	FILE *fpo = fopen("op.txt", "wb+");
	if(fpo == NULL) {
		perror("Output File Openning ERROR\n");
		exit(1);
	}

	fseek(fpi, 1, SEEK_END);
	unsigned long f_ic = 0;		// File Index Counter
	long f_sz = ftell(fpi);	// File SiZe
	printf("File Size: %ld bytes.\n", f_sz);

	int i;	// Secondary Iterator
	int nR = f_sz % 64;	// Number of Ratio
	int nB = f_sz / 64;	// Number of Blocks
	int n;

	BYTE x = 0x80;
	if(nR < 56) {
		n = 55 - nR;
		nB += 1;
	} else {
		n = (63 - nR) + 56;
		nB += 2;
	}
	fwrite(&x, 1, 1, fpi);
	x = 0x00;
	for(i = 0; i < n; i++) {
		fwrite(&x, 1, 1, fpi);
	}
	fwrite(&f_sz, 8, 1, fpi);
	printf("n = %d, nB = %d\n", n, nB);
	rewind(fpi);	// get back the pointer to base

	WORD X[16];
	clearArr(X, 16);

	int j;
	size_t s;
	for(i = 0; i < nB; i++) {
		printf("Hashing Block: %d...", i + 1);
		for(j = 0; j < 16; j++) {
			s = fread(&X[j], 4, 1, fpi);
		}
		// printf("X: ");
		// showArr(X, 16);
		hash(X);
		// printf("H: ");
		// showArr(_H, 8);
		printf("\tDone!\n");
	}

	printf("H: ");
	showArr(_H, 8);

	for(i = 0; i < 8; i++) {
		s = fwrite(&_H[i], 4, 1, fpo);
	}

	fclose(fpi);
	fclose(fpo);
	// system("rm ip.bin");
	return 0;
}
