#ifndef _DES_H
#define _DES_H

#include "data.h"

void byte_to_bits(int n) {
	int i;
	for(i = 0; i < n; i++) {
		_eB[n-1-i] = (_cB >> i) & 0x01;
	}
}
void bits_to_byte(int n) {
	_cB = 0;
	int i;
	for(i = 0; i < n; i++) {
		_cB = (_cB << 1) | _eB[i];
	}
}

void iniPermute() {
	int i;
	BYTE X[64];
	for(i = 0; i < 64; i++)
		X[i] = _X[i];
	for(i = 0; i < 64; i++)
		_X[i] = X[IP[i]];
}

void finPermute() {
	int i;
	BYTE X[64];
	for(i = 0; i < 64; i++)
		X[i] = _X[i];
	for(i = 0; i < 64; i++)
		_X[i] = X[FP[i]];
}
// Generate Key
void genKey(int r) {
	int i, x;
	x = ((r == 0) || (r == 1) || (r == 8) || (r == 15)) ? 1 : 2;
// Copy to temporary location
	for(i = 0; i < 28; i++) {
		_Y[i] = _K[(28 - i - x) % 28];
		_Y[28 + i] = _K[28 + ((28 - i - x) % 28)]
	}
	for(i = 0; i < 48; i++) {
		_k[i] = _Y[KB[i]];
	}
}

void coreDES(int r, BYTE R[]) {
	int i;
	BYTE rs, cs, x;
// right part expansion
	for(i = 0; i < 48; i++) {
		_Y[i] = R[EB[i]];
	}
// substitution
	for(i = 0; i < 8; i++) {
		rs = (_Y[6*i] << 1) | _Y[6*i + 5];
		cs = 0;
		for (x = 1; x < 5; x++) {
			cs = (cs << 1) | _Y[6*i + x];
		}
		x = SB[i][rs][cs];
// copy(R[4*i : 4*i+4], B2b(4,x))
	}
	genKey(r);
// Adding Key
	for(i = 0; i < 48; i++) {
		R[i] ^= _k[i];
	}
}

// Feistal Round
void fr(int r) {
	int i;
	BYTE L[32], R[32];
// Filling up L and R
	for(i = 0; i < 32; i++) {
		L[i] = _X[i], R[i] = _X[32+i];
	}
// Sending R to coreDES
	coreDES(r, R);
// Adding R to L
	for(i = 0; i < 32; i++) {
		L[i] ^= R[i];
	}
// Putting Back in Swapped Position
	for(i = 0; i < 32; i++) {
		_X[i] = R[i];
		_X[32+i] = L[i];
	}
// _X updated
}

void encrypt_des(BYTE P[], BYTE K[]) {
	int i, j;
printf("Received Request with P and K as text (8*8)\n");
printf("Expanding Bytes' to Bits' Blocks => 8*8 --> 1 * 64\n");
	for(i = 0; i < 8; i++) {
		_cB = K[i];
		byte_to_bits(8);
		for(j = 0; j < 8; j++) {
			_X[8*i + j] = _eB[j];
		}
	}
printf("Expanded K: \n");
showArr(_X, 64);
	j = 0;
	for(i = 0; i < 64; i++) {
		if(i%8 != 0)
			_K[j++] = _X[i];
	}
printf("Shortened K: \n");
showArr(_K, 56);
printf("Expanding Bytes' to Bits' Blocks => 8*8 --> 1 * 64\n");
	for(i = 0; i < 8; i++) {
		_cB = P[i];
		byte_to_bits(8);
		for(j = 0; j < 8; j++) {
			_X[8*i + j] = _eB[j];
		}
	}
printf("Expanded P: \n");
	showArr(_X, 64);
printf("Expanded K: \n");

	iniPermute();

printf("Performing 16 feistal rounds\n");
	for(i = 0; i < 16; i++) {
		fr(i); // FeistalRound
	}
printf("Performing Final Permutation\n");
	finPermute();
printf("Shrinking Bits' to Bytes' Blocks => 1 * 64 --> 8 * 8\n");
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			_eB[j] = _X[8*i + j];
		}
		bits_to_byte(8);
		P[i] = _cB;
	}
printf("Encryption Done\n");
}

#endif
