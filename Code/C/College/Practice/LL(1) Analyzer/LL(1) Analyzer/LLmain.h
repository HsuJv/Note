#pragma once
#ifndef LLMAIN_H
#define LLMAIN_H

#pragma warning(disable:4996)

// headers
#include <Windows.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <io.h>

// marco

// typedef
typedef unsigned long digType;

typedef struct _SymbolNode {
	digType serial;
	char* symbol;
	digType *first, *follow;
	struct _SymbolNode *next;
} SymbolNode, *pSymbolNode;

typedef struct _RuleNode{
	digType serial;
	char* symbol;
	struct _RuleNode *next;
} RuleNode, *pRuleNode;

typedef struct _Rule {
	pRuleNode addr;
	struct _Rule *next;
}Rule, *pRule;

// method
pSymbolNode newSymbolNode(digType serial, char* symbol, digType* first, digType* follow, pSymbolNode next);
pRuleNode newRuleNode(digType serial,char* symbol, pRuleNode next);
pRule newRule(pRuleNode addr, pRule next);
inline void systemInit();
void systemExit();
void LLmain();

// Push a rule in stack in reverse
void RuleInStack(pRuleNode p);
#endif // !LLMAIN_H
