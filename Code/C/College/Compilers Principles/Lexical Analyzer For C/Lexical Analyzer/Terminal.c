#include "LA.h"
#include "Terminal.h"

char* g_keyword[44] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local" };

char g_simpleEscapeSeq[11] = { '\'', '\"', '\?', '\\', 'a', 'b', 'f', 'n', 'r', 't', 'v' };

char* g_punctuator[54] = { "<<", ">>", "<", ">", "<=", ">=", "==", "!=", "^", "|", "&&", "||", "?", ":", ";", "...", "=", "*=", "/=", "%=", "+=", "-=", "<<=", ">>=", "&=", "^=", "|=", ",", "#", "##", "<:", ":>", "<%", "%>", "%:", "%:%:" , "[", "]", "(", ")", "{", "}", ".", "->", "++", "--", "&", "*", "+", "-", "~", "!", "/", "%"};

struct _UniversalChar {
	int index;
	unsigned short int value;
	struct _UniversalChar *next;
}*g_pUC;

int isKeyword(char* s) {
	int len;
	for (int i = 0; i < 44; i++) {
		len = strlen(g_keyword[i]);
		if (!strncmp(g_keyword[i], s, len))
			return len;
	}
	return 0;
}

int isNondigit(unsigned char* i) {
	if (*i == '_') return 1;
	if (*i > 64 && *i < 90) return 1;
	if (*i > 96 && *i < 123) return 1;
	return 0;
}

int isDigit(unsigned char* i) {
	if (*i > 47 && *i < 58) return 1;
	return 0;
}

int isUniversalCharacter(unsigned char* i) {
	struct _UniversalChar *p;

	if (IsDBCSLeadByte(*i)) {
		if (!g_pUC) {
			g_pUC = (struct _UniversalChar *)malloc(sizeof(struct _UniversalChar));
			g_pUC->index = 1;
			g_pUC->value = *(short int *)i;
			g_pUC->next = 0;
			return 1;
		}
		for (p = g_pUC; p->next; p = p->next) {
			if (*(short int*)i == p->value)
				return p->index;
		}
		if (*(short int*)i == p->value)
			return p->index;
		p->next = (struct _UniversalChar *)malloc(sizeof(struct _UniversalChar));
		p->next->index = p->index + 1;
		p->next->value = *(short int *)i;
		p->next->next = 0;
		return p->next->index;
	}
	return 0;
}

int isUniversalCharacterName(unsigned char* i) {
	if (*i == 'D') {
		int j = 2;
		int k = 0;
		while (j) {
			if (*(i + k++) == 46) j--;
		}
		return k;
	}
	return 0;
}

int isHexadecimalPerfix(char* s) {
	if (_strnicmp("0x", s, 2)) {
		return 0;
	}
	return 2;
}

int isNonzeroDigit(unsigned char* i) {
	if (*i > 48 && *i < 58) return 1;
	return 0;
}

int isOctalDigit(unsigned char* i) {
	if (*i > 47 && *i < 56) return 1;
	return 0;
}

int isHexadecimalDigit(unsigned char* i) {
	if (*i > 47 && *i < 58) return 1;
	if (*i > 64 && *i < 71) return 1;
	if (*i > 96 && *i < 103) return 1;
	return 0;
}

int isIntegerSuffix(unsigned char* i) {
	if (*i == 85 || *i == 117) {
		if (*(i + 1) == 76 || *(i + 1) == 108) {
			if (*(i + 1) == *(i + 2))
				return 3; // ull
			else return 2; // ul
		}
		else return 1; //u
	}
	else if (*i == 76 || *i == 108) {
		if (*i == *(i + 1)) {
			if (*(i + 2) == 85 || *(i + 2) == 117)
				return 3; // llu
			else return 2; // ll
		}
		else return 1; // l
	}
	return 0;
}

int isSign(unsigned char *i) {
	if (*i == 45 || *i == 43) {
		return 1;
	}
	return 0;
}

int isFloatingSuffix(unsigned char* i) {
	if (*i == 70 || *i == 102 || *i == 76 || *i == 108) {
		return 1;
	}
	return 0;
}

int isEncodingPrefix(unsigned char* i, char c) {
	if (*i == 117) {
		if (*(i + 1) == 56 && c == '\"') {
			return 2; // u8
		}
		return 1; // u
	}
	if (*i == 85) {
		return 1; // U
	}
	if (*i == 76) {
		return 1; // L
	}
	return 0;
}

int isPunctuator(char* s) {
	int len;
	for (int i = 0; i < 54; i++) {
		len = strlen(g_punctuator[i]);
		if (!strncmp(g_punctuator[i], s, len))
			return len;
	}
	return 0;
}

int isSimpleEscapeSeq(unsigned char* c) {
	if (*c == '\\')
		for (int i = 0; i < 11; i++) {
			if (*(c + 1) == g_simpleEscapeSeq[i])
				return 2;
		}
	return 0;
}

int isWhiteSpaceCharacter(unsigned char* c) {
	if (*c == ' ' || *c == '\n' || *c == '\r' || *c == '\t')
		return 1;
	return 0;
}