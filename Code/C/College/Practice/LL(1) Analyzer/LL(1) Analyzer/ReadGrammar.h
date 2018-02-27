#pragma once
#ifndef READGRAMMAR_H
#define READGRAMMAR_H

#include "LLmain.h"

typedef void*(*pFun)();
typedef pRuleNode(*pNewRuleNode)(digType, char*, pRuleNode);
typedef pSymbolNode(*pNewSymbolNode)(digType, char*, long*, long*, pSymbolNode);

// Determine whether it is a the separator
inline long isSperatedSymbol(char * c);

// Get the serial of the symbol
digType findSymbol(char * symbol);

// Get symbol by serial
char* findSerial(digType serial);

// Get linked list from a line
void* getLinkedList(char* in, void* end, pFun newFun, ...);

// Load the gramma from disk
void ReadGrammar(FILE* f);


#endif // !READGRAMMAR_H

