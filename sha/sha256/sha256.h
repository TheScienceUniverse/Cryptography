#ifndef _SHA256_H
#define _SHA256_H

/*
 * This library is for "main SHA-256 functions"
 * that are required for the Project
 */

void hash(WORD *X) {
	// Break into 16 words of 32 bits
	int i;
	for(i = 0; i < 16; i++) {
		_W[i] = X[i];
	}
	WORD s0, s1;
	for(i = 16; i < 64; i++) {
		s0 = ROT_R(_W[i-15], 7) ^ ROT_R(_W[i-15], 18) ^ (_W[i-15] >> 3);
		s1 = ROT_R(_W[i-2], 17) ^ ROT_R(_W[i-2], 19) ^ (_W[i-2] >> 10);
		_W[i] = _W[i-16] + s0 + _W[i-7] + s1;
	}

	// Initializing hash values
	// Initial Value (5 * 32 bits = 160 bits)
	WORD a = _H[0];
	WORD b = _H[1];
	WORD c = _H[2];
	WORD d = _H[3];
	WORD e = _H[4];
	WORD f = _H[5];
	WORD g = _H[6];
	WORD h = _H[7];

//	WORD f, k, t;	// Feistal function, subKey, temporary

	WORD t1, t2;

	// Main loop for Compression Function:
	for(i = 0; i < 64; i++) {
		t1 = h + EP1(e) + CH(e, f, g) + _K[i] + _W[i];
		t2 = EP0(a) + MAJ(a, b, c);

		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	_H[0] += a;
	_H[1] += b;
	_H[2] += c;
	_H[3] += d;
	_H[4] += e;
	_H[5] += f;
	_H[6] += g;
	_H[7] += h;

	// printf("_H[5]: ");
	// showArr(_H, 5);
}

#endif
