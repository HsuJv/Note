#include "LA.h"
#include "Token.h"
#include "PreprocessingToken.h"
#include "Terminal.h"

int isConstant(unsigned char* s) {
	int iLen;

	if (iLen = isFloatingConstant(s))
		return iLen;
	if (iLen = isIntegerConstant(s))
		return iLen;
	if (iLen = isCharacterConstant(s))
		return iLen;
	return 0;
}

int isIntegerConstant(unsigned char* s) {
	int i = 0, iLen = 0;
	if (isNonzeroDigit(s)) {
		while (isDigit(s + i)) i++;
	}
	else if (isHexadecimalPerfix(s)) {
		i += 2;
		while (isHexadecimalDigit(s + i)) i++;
	}
	else if (*s == '0'){
		i += 1;
		while (isOctalDigit(s + i)) i++;
	}
	if (i && (iLen = isIntegerSuffix(s + i)))
		i += iLen;
	return i;
}

int isFloatingConstant(unsigned char* s) {
	int i = 0, iLen;

	if (isHexadecimalDigit(s)) {
		i += 2;
		while (isHexadecimalDigit(s + i)) i++;
		if (*(s + i) == '.') i++;
		while (isHexadecimalDigit(s + i)) i++;
		if (*(s + i) == 'p' || *(s + i) == 'P') {
			i++;
			if (isSign(s + i)) i++;
			while (isDigit(s + i)) i++;
		}
		else return 0;
	}
	else if (isDigit(s)) {
		int isFractional = 0;

		i += 1;
		while (isDigit(s + i)) i++;
		if (*(s + i) == '.') {
			i++;
			isFractional = 1;
		}
		while (isDigit(s + i)) i++;
		if (*(s + i) == 'e' || *(s + i) == 'E') {
			i++;
			if (isSign(s + i)) i++;
			while (isDigit(s + i)) i++;
		}
		else if (!isFractional) return 0;
	}
	if (i && (iLen = isFloatingSuffix(s + i)))
		i += iLen;
	return i;
}
