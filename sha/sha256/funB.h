#ifndef _FUNB_H
#define _FUNB_H

/*
 * This library is for "Basic FUNctions"
 * that are required for the Project
 */

void showArr(WORD A[], int n) {
	int i;
	for(i = 0; i < n; i++) {
		printf("%08x ", A[i]);
	}
	printf("\n");
}
void clearArr(WORD A[], int n) {
	int i;
	for(i = 0; i < n; A[i++] = 0);
}

#define ROT_L(a,b) (((a) << (b)) | ((a) >> (32-(b)))) // Rotate Left
#define ROT_R(a,b) (((a) >> (b)) | ((a) << (32-(b)))) // Rotate Right

// #define SIG0(x) (ROT_R(x,7) ^ ROT_R(x,18) ^ ((x) >> 3))
// #define SIG1(x) (ROT_R(x,17) ^ ROT_R(x,19) ^ ((x) >> 10))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))	// Majority
#define EP0(x) (ROT_R(x,2) ^ ROT_R(x,13) ^ ROT_R(x,22))
#define EP1(x) (ROT_R(x,6) ^ ROT_R(x,11) ^ ROT_R(x,25))

#endif
