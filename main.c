#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BYTE unsigned char
#define UL unsigned long
#define N 100

#include "shift_cipher.h"

void dspl(BYTE *X, UL nx) {
	for(int i=0; i<nx; printf("%c", (char)X[i++]));
	printf("\n");
}

int main(int argc, char *argv[]) {
	FILE *fpi, *fpo;
	int i;
	if(argc < 3) {
		perror("Insufficient Data\nUse \"<PROGRAM_NAME> <INPUT_FILE_NAME> <OUTPUT_FILE_NAME> <ENTER>\"");
		exit(1);
	}
	if((fpi=(fopen(argv[1], "r"))) == NULL) {
		perror("Input file Openning ERROR!...\n");
		exit(1);
	}
	if((fpo=(fopen(argv[2], "w+"))) == NULL) {
		perror("Output file Openning ERROR!...\n");
		exit(1);
	}
	
	BYTE *X = (BYTE *)malloc(N);
	UL nx;
	BYTE c=0;
	ssize_t x;

	fseek(fpi, 0, SEEK_END);
	nx = ftell(fpi);
	fseek(fpi, 0, SEEK_SET);

	for(i=0; i<nx; i++) {
		x = fread(&c, 1, 1, fpi);
		X[i] = c;
	}

//x = fread(&c, 1, 1, fpi);
//x = fwrite(&c, 1, 1, fpo);

//	dspl(X, nx);

	encrypt(X, &nx, 3);
//	dspl(X, nx);
	x = fwrite(X, nx, 1, fpo);

//	decrypt(X, &nx, 3);
//	dspl(X, nx);
//	x = fwrite(X, nx, 1, fpi);

	fclose(fpi);
	fclose(fpo);

	printf("Success!\n");
	return 0;
}
