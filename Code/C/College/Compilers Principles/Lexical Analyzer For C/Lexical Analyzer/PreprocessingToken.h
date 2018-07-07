#pragma once
#ifndef PREPROCESSINGTOKEN_H
#define PREPROCESSINGTOKEN_H

int isTrigraph(unsigned char* s);

int isEscapeNewLine(unsigned char* s);

int isHeaderName(unsigned char* s);

int isIdentifier(unsigned char* s);

int isPpNumber(unsigned char* s);

int isCharacterConstant(unsigned char* s);

int isStringLiteral(unsigned char* s);

int isIdentifierNonDigit(unsigned char* s);

int isXCharSeq(unsigned char* s, char c);

int isComment(unsigned char* s);
#endif // !PREPROCESSINGTOKEN_H
