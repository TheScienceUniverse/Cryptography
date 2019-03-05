#ifndef _DATA_H
#define _DATA_H

// defining datatypes
#define BYTE unsigned char
#define UINT uint32_t
// #define UINT unsigned int

/*
BYTE _H[5][4] = {
{0x67, 0x45, 0x23, 0x01},
{0xef, 0xcd, 0xab, 0x89},
{0x98, 0xba, 0xdc, 0xfe},
{0x10, 0x32, 0x54, 0x76},
{0xc3, 0xd2, 0xe1, 0xf0}};
*/
UINT _H[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};

UINT _W[80];	// Words (extended)
//BYTE _W[320];	// Words (extended)

#endif
