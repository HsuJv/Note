#include "HMIS.h"
#include "Vigenere.h"

#define KEYLEN 16
BYTE key[16] = { 0xc9, 0x33, 0x40, 0x4d, 0xc8, 0x48, 0x4a, 0x4f, 0x3f, 0x2b, 0x79, 0xcf, 0xd0, 0xbc, 0x24, 0x74 };

void getVigenereEncrypt(PBYTE data, unsigned int len) {
	for (unsigned int i = 0; i < len; i++) {
		if (!*(data + i)) continue;
		*(data + i) = *(data + i) ^ (key[i % KEYLEN]);
	}
}
