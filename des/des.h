#ifndef _DES_H
#define _DES_H

void encrypt_des(BYTE *, BYTE *);
void fr(int);
void coreDES(int, BYTE *);
void genKey(int);
void iniPermute(void), finPermute(void);

void e_des(BYTE P[], BYTE K[]) {
	int i, j;

	printf("Received P and K (8*8)\n");

//	printf("Expanding Key-Text => 8*8 --> 1 * 64\n");
	for(i = 0; i < 8; i++) {
		_cB = K[i];
		byte_to_bits(8);
		for(j = 0; j < 8; j++) {
			_X[8*i + j] = _eB[j];
		}
	}
//	printf("Expanded K[64]: ");
//	showArrBit(_X, 64);

	j = 0;
	for(i = 0; i < 64; i++) {
		if(i%8 != 0)
			_K[j++] = _X[i];
	}
//	printf("Shortened K[56]: ");
//	showArrBit(_K, 56);

//	printf("Expanding Plain-Text => 8*8 --> 1 * 64\n");
	for(i = 0; i < 8; i++) {
		_cB = P[i];
		byte_to_bits(8);
		for(j = 0; j < 8; j++) {
			_X[8*i + j] = _eB[j];
		}
	}
//	printf("Expanded P[64]: ");
//	showArrBit(_X, 64);


//	printf("Performing Initial Permutation\n");
	iniPermute();

//	printf("Performing 16 feistal rounds\n");
	for(i = 0; i < 16; i++) {
		fr(i); // FeistalRound
	}

//	printf("Performing Final Permutation\n");
	finPermute();

//	printf("Shrinking Cipher-Text => 1 * 64 --> 8 * 8\n");
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			_eB[j] = _X[8*i + j];
		}
		bits_to_byte(8);
		P[i] = _cB;
	}
	printf("Encryption Done\n");
}

// Feistal Round
void fr(int r) {
	int i;
	BYTE L[32], R[32];
	//printf("Round-%d\n", r+1);
	// Filling up L and R
	for(i = 0; i < 32; i++) {
		L[i] = _X[i], R[i] = _X[32+i];
	}
	// Saving by Swapping at _X
	for(i = 0; i < 32; i++) {
		_X[i] = R[i];
	}
	// Sending R to coreDES
	coreDES(r, R);
	// Adding R to L
	for(i = 0; i < 32; i++) {
		L[i] ^= R[i];
	}
	// Putting Back in Swapped Position
	for(i = 0; i < 32; i++) {
		_X[32+i] = L[i];
	}
}

// Core DES
void coreDES(int r, BYTE R[]) {
	int i, j;
	BYTE rs, cs, x;
	// right part expansion
	for(i = 0; i < 48; i++) {
		_Y[i] = R[EB[i]];
	}
	// generating round_key
	genKey(r);
	// Adding Key
	for(i = 0; i < 48; i++) {
		_Y[i] ^= _k[i];
	}
	// substitution
	for(i = 0; i < 8; i++) {
		rs = (_Y[6*i] << 1) | _Y[6*i + 5];
		cs = 0;
		for (x = 1; x < 5; x++) {
			cs = (cs << 1) | _Y[6*i + x];
		}
		x = SB[i][rs][cs];
		// nibble to bits
		_cB = x;
		byte_to_bits(4);
		for(j = 0; j < 4; j++) {
			R[4*i + j] = _eB[j];
		}
	}
	// permutating straight
	for(i = 0; i < 32; i++) {
		_Y[i] = R[SP[i]];	// moving to temporary location
	}
	for(i = 0; i < 32; i++) {
		R[i] = _Y[i];		// copying to original location
	}	
}

// Generate Key
void genKey(int r) {
	BYTE Y[56];
	int i, x;
	x = ((r == 0) || (r == 1) || (r == 8) || (r == 15)) ? 1 : 2;
	// copying to temporary location
	for(i = 0; i < 28; i++) {
		Y[i] = _K[(28 - i - x) % 28];
		Y[28 + i] = _K[28 + ((28 - i - x) % 28)];
	}
	// updating main key
	for(i = 0; i < 56; i++){
		_K[i] = Y[i];
	}
	// updating working key
	for(i = 0; i < 48; i++) {
		_k[i] = Y[KB[i]];
	}
//	printf("K_%02d[48]: ", r);
//	showArrBit(_k, 48);
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

#endif
