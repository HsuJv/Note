#pragma once
#ifndef LA_H
#define LA_H

// headers
#include <Windows.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <io.h>

// macro
#define FILE_OUTPUT "out.txt"

#define TYPE_KEYWORD 1
#define TYPE_IDENTIFIER 2
#define TYPE_CONSTANT 3
#define TYPE_STRING_LITERAL 4
#define TYPE_PUNCTUATOR 5
#define TYPE_UNDEFINED 6

// functions
int __stdcall separatePreprocessingToken(unsigned char* s);

int __stdcall separateToken(unsigned char* s);

#endif // !LA_H
