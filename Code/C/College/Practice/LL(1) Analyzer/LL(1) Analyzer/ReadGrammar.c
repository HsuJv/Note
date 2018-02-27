#include "ReadGrammar.h"
#include "Stack.h"

extern pSymbolNode ll[3];
extern pRule gRules;
extern digType gNonTerSerial;
extern digType gTerSerial;

inline long isSperatedSymbol(char * c) {
	if (*c == 0x20 || *c == 9)
		return  1;
	if (*c == 0xd || *c == 0xa || *c == 0)
		return 2;
	return 0;
}

digType findSymbol(char * symbol) {
	for (pSymbolNode p = ll[0]; p; p = p->next) {
		if (!strcmp(symbol, p->symbol))
			return p->serial;
	}

	for (pSymbolNode p = ll[1]; p; p = p->next) {
		if (!strcmp(symbol, p->symbol))
			return p->serial;
	}

	return 0;
}

char* findSerial(digType serial) {
	pSymbolNode p;
	char* rtn;

	if (serial % 2) p = ll[0];
	else p = ll[1];
	
	for (; p; p = p->next) {
		if (p->serial == serial) {
			rtn = (char*)malloc(strlen(p->symbol) + 1);
			strcpy(rtn, p->symbol);
			return rtn;
		}
	}
	return 0;
}

void* getLinkedList (char* in, void* end, pFun newFun, ...) {
	long i = 0, j;
	char symbol[BUFSIZ];
	void *p = end;
	digType* cnt = 0;

	if (newFun == newSymbolNode) {
		va_list arg_ptr;

		va_start(arg_ptr, newFun);
		cnt = va_arg(arg_ptr, digType *);
		va_end(arg_ptr);
	}

	while (isSperatedSymbol(in + i) != 2) i++;
	for (j = --i; j > -1; i = j) {
		while (!isSperatedSymbol(in + j) && j > -1) j--;

		memcpy(symbol, in + j + 1, i - j);
		symbol[i - j] = 0;

		if (newFun == newRuleNode) {
			(pRuleNode)p = ((pNewRuleNode)newFun) (findSymbol(symbol), symbol, (pRuleNode)p);

		}
		else if (newFun == newSymbolNode) {
			(pSymbolNode)p = ((pNewSymbolNode)newFun) (*cnt, symbol, 0, 0, (pSymbolNode)p);
			*cnt += 2;
		}

		while (isSperatedSymbol(in + j) && j > -1) j--;
	}

	return p;
}

void ReadGrammar(FILE* f) {
	char buf[BUFSIZ] = { 0 };
	long i = 0;
	long lf; // long file offset of the rules

	// Nonterminals
	fgets(buf, BUFSIZ, f);
	ll[0] = getLinkedList(buf, 0, newSymbolNode, &gNonTerSerial);

	// Terminals
	fgets(buf, BUFSIZ, f);
	ll[1] = getLinkedList(buf, 0, newSymbolNode, &gTerSerial);

	// Read Rules
	lf = ftell(f);
	while (fgets(buf, BUFSIZ, f)) {
		if (isSperatedSymbol(buf) != 2) {
			// Store the file point line by line
			StackPush(lf);
		}
		lf = ftell(f);
	}

	// Store Rules in Reverse
	while (!StackIsEmpty()) {
		// Recover the file point
		StackPop(&lf);
		fseek(f, lf, 0);

		// Rules
		fgets(buf, BUFSIZ, f);
		gRules = newRule((pRuleNode)getLinkedList(buf, 0, newRuleNode), gRules);
	}

	// Test
#ifdef _DEBUG
	for (pRule p = gRules; p; p = p->next) {
		for (pRuleNode pr = p->addr; pr; pr = pr->next) {
			printf("%s ", pr->symbol);
		}
		printf("\n");
	}
	printf("\n\n\n");
#endif // _DEBUG
}