#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

	printf("Success!\n");

	fclose(fpi);
	fclose(fpo);

	return 0;
}
