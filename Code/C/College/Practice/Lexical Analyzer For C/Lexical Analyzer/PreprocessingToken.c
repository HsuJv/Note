#include "LA.h"
#include "PreprocessingToken.h"
#include "Terminal.h"

// trigraph
char* g_trigraph[9] = { "\?\?=", "\?\?/", "\?\?'", "\?\?(", "\?\?)", "\?\?<", "\?\?>", "\?\?!", "\?\?-" };
char* g_trigraphMap[9] = { "#", "\\", "^", "[", "]", "{", "}", "|", "~" };


int isTrigraph(unsigned char* s) {
	int i;

	if (*(s + 1) == 0 || *(s + 2) == 0) return 0;
	for (i = 0; i < 9; i++) {
		if (!strncmp(s, g_trigraph[i], 3))
			return i + 1;
	}
	return 0;
}

int isEscapeNewLine(unsigned char *s) {
	if (*(s + 1) == 0) return 0; // filter the last newline ahead of EOF
	if (*s == 92 && (*(s + 1) == '\r' || *(s + 1) == '\n')) return 1;
	return 0;
}

int isHeaderName(unsigned char* s) {
	int i = 1;

	if (*s == '\'') {
		while (*(s + i) != '\'' && *(s + i) != 0 && !isWhiteSpaceCharacter(s + i)) i++;
		if (*(s + i) = '\'') return i + 1;
	}
	else if (*s == '<')
	{
		while (*(s + i) != '>' && *(s + i) != 0 && !isWhiteSpaceCharacter(s + i)) i++;
		if (*(s + i) = '>') return i + 1;
	}
	return 0;
}

int isIdentifier(unsigned char* s) {
	int i = 0, pi;
	int iLen;

	if (iLen = isIdentifierNonDigit(s)) i += iLen;
	else return 0;
	do {
		pi = i;
		if (iLen = isIdentifierNonDigit(s + i)) i += iLen;
		while (iLen = isDigit(s + i)) i += iLen;
	} while (pi != i);
	return i;
}

int isPpNumber(unsigned char* s) {
	int i = 0, iLen, pi;

	if (*s == '.') i++;
	if (isDigit(s + i)) i++;
	else return 0;
	do {
		pi = i;
		while (iLen = isDigit(s + i)) i += iLen;
		if (iLen = isIdentifierNonDigit(s + i)) i += iLen;
		if (*(s + i - 1) == 'e' || *(s + i - 1) == 'E' || *(s + i - 1) == 'p' || *(s + i - 1) == 'P')
			if (isSign(s + i)) i++;
		while (*(s + i) == '.') i++;
	} while (pi != i);
	return i;
}

int isCharacterConstant(unsigned char* s) {
	int i = 0, iLen;

	if (iLen = isEncodingPrefix(s, '\'')) i += iLen;
	if (*(s + i) == '\'') {
		i++;
		if (iLen = isXCharSeq(s + i, '\'')) {
			i += iLen;
			return i;
		}
		return 0;
	}
	return 0;
}

int isStringLiteral(unsigned char* s) {
	int i = 0, iLen;

	if (iLen = isEncodingPrefix(s, '\'')) i += iLen;
	if (*(s + i) == '\"') {
		i++;
		if (iLen = isXCharSeq(s + i, '\"')) {
			i += iLen;
			return i;
		}
		return 0;
	}
	return 0;
}

int isIdentifierNonDigit(unsigned char* s) {
	int i = 0, pi;
	int iLen = 0;

	if (*s != 0) {
		do {
			pi = i;
			while (iLen = isNondigit(s + i)) i += iLen;
			while (iLen = isUniversalCharacterName(s + i)) i += iLen;
		} while (pi != i);
		return i;
	}
	return 0;
}

int isXCharSeq(unsigned char* s, char c) {
	int i = 0, pi;

	if (*s != 0) {
		do {
			pi = i;
			while (*(s + i) != '\\' && *(s + i) != c && *(s + i) != '\n' && *(s + i) != '\r') i++;
			if (isSimpleEscapeSeq(s + i)) i += 2;
			else if (*(s + i) == '\\' && isOctalDigit(s + i + 1)) {
				if (isOctalDigit(s + i + 2) && isOctalDigit(s + i + 3)) i += 4;
				else if (isOctalDigit(s + i + 2)) i += 3;
				else i += 2;
			}
			else if (*(s + i) == '\\' && *(s + i + 1) == 'x' && isHexadecimalDigit(s + i + 2)) {
				i += 3;
				while (isHexadecimalDigit(s + i)) i++;
			}
		} while (pi != i);
		if (*(s + i) == c) return i + 1;
	}
	return 0;
}

int isComment(unsigned char* s) {
	int i = 0;
	if (*s == '/' && *(s + 1) == '/')
		while (*(s + i) != '\n') i++;
	else if (*s == '/' && *(s + 1) == '*')
		while (*(s + i) != '/' && *(s + i - 1) != '*') i++;
	return i;
}