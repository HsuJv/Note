#include "LLmain.h"
#include "Stack.h"
#include "ReadGrammar.h"
#include "PreLL1.h"

extern pRuleNode **AT;

// Linked List
// ll[0] point to the linked list of nonterminals
// ll[1] point to the linked list of terminals
// ll[2] point to the start symbol
pSymbolNode ll[3]; 
pRule gRules;
digType gNonTerSerial = 1;
digType gTerSerial = 2;

int main(int argc, char* argv[]) {
	FILE *fGramma;

	// Arguments assert
	if (argc != 2) {
		printf("Usage: LL.exe 'grammarFile'");
#ifdef _DEBUG
		for (long i = 0; i < argc; i++)
			printf("%s\n", argv[i]);
#endif
		_getch();
		return 1;
	}
	
	// File exists
	if (_access(argv[1], 0)) {
		printf("Grammar file not exits.\nPlease check again.");
		_getch();
		return 1;
	}

	// initialize
	systemInit();

	// Open the grammar file
	fGramma = fopen(argv[1], "r");

	// Read data
	ReadGrammar(fGramma);

	// Close the file 
	fclose(fGramma);

	// Preprocess
	PreLL1();

	// LL(1) Analysis
	LLmain();

	// Free memory
	systemExit();

	_getch();
	return 0;
}

pSymbolNode newSymbolNode(digType serial, char* symbol, digType* first, digType* follow, pSymbolNode next) {
	pSymbolNode pn = (pSymbolNode)malloc(sizeof(SymbolNode));
	pn->serial = serial;
	pn->symbol = (char *)malloc(strlen(symbol) + 1);
	strcpy(pn->symbol, symbol);
	if (!strcmp(symbol, "0")) {
		pn->serial = 0;
	}
	pn->first = first;
	pn->follow = follow;
	pn->next = next;
	
	return pn;
}

pRuleNode newRuleNode(digType serial, char *symbol, pRuleNode next) {
	pRuleNode pn = (pRuleNode)malloc(sizeof(RuleNode));
	pn->serial = serial;
	pn->symbol = (char *)malloc(strlen(symbol) + 1);
	strcpy(pn->symbol, symbol);
	pn->next = next;

	return pn;
}

pRule newRule(pRuleNode addr, pRule next) {
	pRule pn = (pRule)malloc(sizeof(Rule));
	pn->addr = addr;
	pn->next = next;

	return pn;
}

inline void systemInit() {
	// Initialize the stack
	stackInit();
}

void systemExit() {
	for (pRule p = gRules; p;) {
		pRule pr;

		for (pRuleNode pr = p->addr; pr;) {
			pRuleNode prn = pr;
			pr = pr->next;
			free(prn->symbol);
			free(prn);
		}
		pr = p;
		p = p->next;
		free(pr);
	}
	gRules = NULL;

	for (pSymbolNode n = ll[0]; n;) {
		pSymbolNode p = n;
		n = n->next;
		free(p->first);
		free(p->follow);
		free(p->symbol);
		free(p);
	}
	ll[0] = NULL;

	for (pSymbolNode n = ll[1]; n;) {
		pSymbolNode p = n;
		n = n->next;
		free(p->first);
		free(p->follow);
		free(p->symbol);
		free(p);
	}
	ll[1] = NULL;

	ll[2] = NULL;

	for (digType i = 0; i < gNonTerSerial / 2; i++) {
		free(*(AT + i));
		*(AT + i) = 0;
	}
	free(AT);

	stackDisposal();
}

void LLmain() {
	int scanner = 0;
	char seq[BUFSIZ];

	printf("%s:", "Input the sequence to be analysed");
	scanf("%s", seq);
	StackPush(ll[2]->serial);

	printf("Analysis stack: %s", ll[2]->symbol);
	printf("\nScan stack: %s\n", seq);

	while (*(seq + scanner)) {
		digType len = 0;
		pSymbolNode pTer = NULL;
		long temp, *as;
		
		for (pSymbolNode p = ll[1]; p; p = p->next) {
			if (strncmp(p->symbol, seq + scanner, strlen(p->symbol)))
				continue;
			else {
				if (strlen(p->symbol) > len) {
					len = (digType)strlen(p->symbol);
					pTer = p;
				}
			}
		}

		if (!pTer) {
			printf("\nError: No matching terminal.\n");
			return;
		}
		else {
			if (pTer->serial != StackTop()) {
				pRuleNode toBePushed = AT[StackTop() / 2][pTer->serial / 2];
				if (toBePushed) {
					StackPop(&temp);
					RuleInStack(toBePushed);
				}
				else {
					printf("\nError.\n");
					return;
				}
			}
			else
			{
				StackPop(&temp);
				scanner += len;
			}
		}
		printf("Analysis stack: ");
		as = Stack2Array();
		for (long i = StackCounts() - 1; i > -1; i--) {
			char *s;
			s = findSerial(as[i]);
			printf("%s ", s);
			free(s);
		}
		free(as);
		printf("\nScan stack: %s\n", seq + scanner);
	}

	// The input stream is end
	while (AT[StackTop() / 2][0]) {
		long temp, *as;
		pRuleNode toBePushed = AT[StackTop() / 2][0];
		
		StackPop(&temp);
		RuleInStack(toBePushed);

		printf("Analysis stack: ");
		as = Stack2Array();
		for (long i = StackCounts() - 1; i > -1; i--) {
			char *s;
			s = findSerial(as[i]);
			printf("%s ", s);
			free(s);
		}
		free(as);
		printf("\nScan stack: %s\n", seq + scanner);
	}
	if (StackIsEmpty()) {
		printf("\nAccepted.\n");
	}
	else
	{
		printf("\nError.");
	}
}

void RuleInStack(pRuleNode p) {
	pRuleNode pre = NULL, cur = p, nxt = NULL;

	while (cur) {
		nxt = cur->next;
		cur->next = pre;
		pre = cur;
		cur = nxt;
	}
	cur = pre;
	pre = NULL;
	while (cur) {
		if (cur->serial)
			StackPush(cur->serial);
		nxt = cur->next;
		cur->next = pre;
		pre = cur;
		cur = nxt;
	}
}