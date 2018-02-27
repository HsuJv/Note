#pragma once
#ifndef TERMINAL_H
#define TERMINAL_H

int isKeyword(char* s);

int isNondigit(unsigned char* i);

int isDigit(unsigned char* i);

int isUniversalCharacter(unsigned char* i);

int isUniversalCharacterName(unsigned char* i);

int isHexadecimalPerfix(char* s);

int isNonzeroDigit(unsigned char* i);

int isOctalDigit(unsigned char* i);

int isHexadecimalDigit(unsigned char* i);

int isIntegerSuffix(unsigned char*);

int isSign(unsigned char *i);

int isFloatingSuffix(unsigned char* i);

int isEncodingPrefix(unsigned char* i, char c);

int isPunctuator(char* s);

int isSimpleEscapeSeq(unsigned char* c);

int isWhiteSpaceCharacter(unsigned char* c);

#endif // !TERMINAL_H
