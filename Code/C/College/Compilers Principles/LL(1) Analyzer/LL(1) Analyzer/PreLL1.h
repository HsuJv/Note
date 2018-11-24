#pragma once
#ifndef PRELL1_H
#define PRELL1_H

#include "LLmain.h"

// Appand new elements in a set
digType * setAppend(digType ** dst, digType * src, int includeZero);

// Find a point to the symbol by its serial
pSymbolNode findSymbolPoint(digType serial);

// Retrive a rule to its string mode, 
char* Rule2String(pRuleNode p);

// Calculate how large the set is
digType setCount(void * pFun);

// Detect and eliminate left recursion
void DLR();

// Work out the First set of a single symbol
void getSymbolFirst(pSymbolNode p);

// Work out the Follow sets
void getFollow(pSymbolNode p);

// Construct LL(1) analysis table
void CLAT();

// Main
void PreLL1();

#endif // !PRELL1_H
