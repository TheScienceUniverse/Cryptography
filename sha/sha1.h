#ifndef _SHA1_H
#define _SHA1_H

void hash(UINT *X, int ml) {
	// Break into 16 words of 32 bits
	int i;
	for(i = 0; i < 16; i++) {
		_W[i] = X[i];
	}
	for(i = 16; i < 80; i++) {
		_W[i] = left_rotate((_W[i-3] ^ _W[i-8] ^ _W[i-14] ^ _W[i-16]), 1);
	}

	// Initializing hash values
	// Initial Value (5 * 32 bits = 160 bits)
	UINT a = _H[0];
	UINT b = _H[1];
	UINT c = _H[2];
	UINT d = _H[3];
	UINT e = _H[4];

	UINT f, k, t;	// Feistal function, subKey, temporary

	// Main loop:
	for(i = 0; i < 80; i++) {

		if ((i >= 0) && (i < 20)) {
			f = (b & c) | (!b & d);
			k = 0x5A827999;
		} else if ((i >= 20) && (i < 40)) {
			f = b ^ c ^ d;
			k = 0x6ED9EBA1;
		} else if ((i >= 40) && (i < 60)) {
			f = (b & c) | (b & d) | (c & d);
			k = 0x8F1BBCDC;
		} else if ((i >= 60) && (i < 80)) {
			f = b ^ c ^ d;
			k = 0xCA62C1D6;
		}

		t = left_rotate(a, 5) + f + e + k + _W[i];
		e = d;
		d = c;
		c = left_rotate(b, 30);
		b = a;
		a = t;
	}

	_H[0] += a;
	_H[1] += b;
	_H[2] += c;
	_H[3] += d;
	_H[4] += e;

	printf("_H[5]: ");
	showArr(_H, 5);

	// printf("_W[80]: ");
	// showArr(_W, 80);
}

#endif
