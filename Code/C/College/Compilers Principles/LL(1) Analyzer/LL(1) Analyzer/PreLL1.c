#include "PreLL1.h"
#include "ReadGrammar.h"


extern pSymbolNode ll[3];
extern pRule gRules;
extern digType gNonTerSerial;
extern digType gTerSerial;

pRuleNode **AT; // analysis table

digType * setAppend(digType ** dst, digType * src, int includeZero) {
	long cdst = **dst, csrc = *src;
	digType * ret = (digType *)malloc(sizeof(long) * (cdst + csrc + 1));
	long cnt = 0, pdst = 1, psrc = 1;

	for (; pdst <= cdst && psrc <= csrc; cnt++) {
		if (!includeZero) {
			if (!*(*dst + pdst)) pdst++;
			if (!*(src + pdst)) psrc++;
		}
		if (*(*dst + pdst) < *(src + psrc)) {
			*(ret + cnt + 1) = *(*dst + pdst);
			pdst++;
		}
		else if (*(*dst + pdst) > *(src + psrc)) {
			*(ret + cnt + 1) = *(src + psrc);
			psrc++;
		}
		else {
			*(ret + cnt + 1) = *(*dst + pdst);
			pdst++; psrc++;
		}
	}
	while (pdst <= cdst) {
		*(ret + cnt + 1) = *(*dst + pdst);
		cnt++; pdst++;
	}
	while (psrc <= csrc) {
		*(ret + cnt + 1) = *(src + psrc);
		cnt++; psrc++;
	}

	*ret = cnt;
	free(*dst);
	*dst = NULL;

	return ret;
}

pSymbolNode findSymbolPoint(digType serial) {
	for (pSymbolNode p = ll[0]; p; p = p->next) {
		if (p->serial == serial)
			return p;
	}

	for (pSymbolNode p = ll[1]; p; p = p->next) {
		if (p->serial == serial)
			return p;
	}

	return 0;
}

char* Rule2String(pRuleNode p) {
	char* buf = (char*)malloc(BUFSIZ);
	size_t i = 0;

	for (pRuleNode pn = p; pn; pn = pn->next) {
		size_t len = strlen(pn->symbol);

		strcpy(buf + i, pn->symbol);
		i += len;
		*(buf + i++) = 0x20;
	}
	--i;
	*(buf + i) = 0;

	return buf;
}

digType setCount(void* pFun) {
	digType rtn = 0;
	if (pFun == getSymbolFirst) {
		for (pSymbolNode p = ll[0]; p; p = p->next)
			if (p->first)
				rtn += *(p->first);
	}
	else {
		for (pSymbolNode p = ll[0]; p; p = p->next)
			if (p->follow)
				rtn += *(p->follow);
	}
	return rtn;
}

void DLR() {
	pSymbolNode symbol_start = ll[0];
	pRule rule_start = gRules;
	ll[2] = ll[0];

	for (pSymbolNode i = symbol_start; i; i = i->next) {
		// Delete the indirect left recursion
		for (pSymbolNode j = symbol_start; j != i; j = j->next) {
			for (pRule ri = rule_start; ri; ri = ri->next) {
				// Rules that in the form of i ::= j...
				if (ri->addr->serial == i->serial) {
					if (ri->addr->next->serial == j->serial) {
						int changed = 0;

						// j is going to be substituted
						for (pRule rj = rule_start; rj; rj = rj->next) {
							// Rules that in the form of j ::= ...
							if (rj->addr->serial == j->serial) {
								char* buf;
								pRuleNode origanal = ri->addr->next;

								changed = 1;

								buf = Rule2String(rj->addr->next);
								ri->addr->next = (pRuleNode)getLinkedList(buf, origanal->next, newRuleNode);
								free(buf);
								buf = Rule2String(ri->addr);
								gRules = newRule((pRuleNode)getLinkedList(buf, 0, newRuleNode), gRules);
								free(buf);
								buf = NULL;

								for (pRuleNode prn = ri->addr->next; prn != origanal->next;) {
									pRuleNode temp = prn;
									prn = prn->next;
									free(temp);
								}

								ri->addr->next = origanal;
							}
						}

						// Delete the rule rj
						if (changed) {
							pRule preRi = gRules;

							while (preRi->next != ri && preRi != ri) preRi = preRi->next;
							for (pRuleNode pr = ri->addr; pr;) {
								pRuleNode prn = pr;
								pr = pr->next;
								free(prn->symbol);
								free(prn);
							}
							preRi->next = ri->next;
							free(ri);
							ri = preRi;
						}
					}
				}
			}
		}

		rule_start = gRules;

		// Delete the direct left recursion
		for (pRule r = rule_start; r; r = r->next) {
			// Rules that in the form of i ::= i...
			if (r->addr->serial == i->serial && r->addr->serial == r->addr->next->serial) {
				char newSymbol[BUFSIZ], *buf;
				size_t sLen, rLen;
				pRule preRi;
				int deleted = 0;

				// Fine all rules that indicate a direct left recursion rule of i
				for (pRule ri = r; ri; ri = ri->next) {
					if (ri->addr->serial == i->serial && ri->addr->serial == ri->addr->next->serial) {
						// Add symbol i'
						strcpy(newSymbol, i->symbol);
						sLen = strlen(i->symbol);
						newSymbol[sLen++] = '\'';
						newSymbol[sLen] = 0;
						if (strcmp(ll[0]->symbol, newSymbol)) {
							ll[0] = newSymbolNode(gNonTerSerial, newSymbol, 0, 0, ll[0]);
							gNonTerSerial += 2;
						}					

						// Add rule i ::= 0
						if (!deleted) {
							newSymbol[sLen] = 0x20;
							newSymbol[sLen + 1] = '0';
							newSymbol[sLen + 2] = 0;
							gRules = newRule((pRuleNode)getLinkedList(newSymbol, 0, newRuleNode), gRules);
						}

						// Add rule i' ::= ...i'
						buf = Rule2String(ri->addr->next->next);
						newSymbol[sLen++] = 0x20;
						memcpy(newSymbol + sLen, buf, strlen(buf));
						sLen += strlen(buf);
						free(buf);
						newSymbol[sLen++] = 0x20;
						rLen = sLen;
						sLen = 0;
						while (*(newSymbol + sLen) != 0x20) sLen++;
						newSymbol[sLen] = 0;
						strcpy(newSymbol + rLen, newSymbol);
						rLen += sLen;
						newSymbol[sLen] = 0x20;
						newSymbol[rLen] = 0;
						gRules = newRule((pRuleNode)getLinkedList(newSymbol, 0, newRuleNode), gRules);

						newSymbol[sLen] = 0;

						// Add rules i ::= a i' for all a in rules i ::= a starting without i
						for (pRule rr = rule_start; rr; rr = rr->next) {
							// If rules i ::= a i' for all a in rules i ::= a starting without i has been deleted
							if (deleted) break;

							// Rule in the form of i ::= a starting without i
							if (rr->addr->serial == i->serial && rr->addr->serial != rr->addr->next->serial) {
								char newR[BUFSIZ];

								buf = Rule2String(rr->addr);
								rLen = strlen(buf);
								strcpy(newR, buf);
								free(buf);
								newR[rLen++] = 0x20;
								strcpy(newR + rLen, newSymbol);
								gRules = newRule((pRuleNode)getLinkedList(newR, 0, newRuleNode), gRules);

								// Delete the rule rr
								preRi = gRules;
								while (preRi->next != rr) preRi = preRi->next;
								for (pRuleNode pr = rr->addr; pr;) {
									pRuleNode prn = pr;
									pr = pr->next;
									free(prn->symbol);
									free(prn);
								}
								preRi->next = rr->next;
								if (rr == ri) ri = preRi;
								free(rr);
								rr = preRi;
							}
						}

						deleted = 1;
					}
				}

				// Delete all rules that indicates a direct left recursion of i
				for (pRule ri = r; ri; ri = ri->next) {
					if (ri->addr->serial == i->serial) {
						preRi = gRules;
						while (preRi->next != ri) preRi = preRi->next;
						for (pRuleNode pr = ri->addr; pr;) {
							pRuleNode prn = pr;
							pr = pr->next;
							free(prn->symbol);
							free(prn);
						}
						preRi->next = ri->next;
						if (ri == r) r = preRi;
						free(ri);
						ri = preRi;
					}
				}

				rule_start = gRules;
			}
		}
	}
}

void getSymbolFirst(pSymbolNode p) {
	// Terminals
	if (p->serial % 2 == 0)
	{
		p->first = (digType*)malloc(sizeof(long) * 2);
		*(p->first) = 1;
		*(p->first + 1) = p->serial;
	}
	// Nonterminals
	else
	{
		for (pRule r = gRules; r; r = r->next) {
			// Rules about P
			if (r->addr->serial == p->serial) {
				// Rules like P ::= p alpha or 0
				if (r->addr->next->serial % 2 == 0) {
					pSymbolNode pa = findSymbolPoint(r->addr->next->serial);

					// P ::= p alpha
					if (r->addr->next->serial) {
						if (p->first) {
							p->first = setAppend(&p->first, pa->first, 1);
						}
						else {
							p->first = (digType*)malloc(sizeof(long) * 2);
							*(p->first) = 1;
							*(p->first + 1) = pa->serial;
						}
					}
					// A ::= 0
					else
					{
						if (p->first) {
							digType temp[2] = { 1, 0 };
							p->first = setAppend(&p->first, temp, 1);
						}
						else {
							p->first = (digType*)malloc(sizeof(long) * 2);
							*(p->first) = 1;
							*(p->first + 1) = 0;
						}
					}
				}
				// Rules like A ::= B1 B2 ... Bk
				else {
					for (pRuleNode pr = r->addr->next; pr; pr = pr->next) {
						pSymbolNode pb = findSymbolPoint(pr->serial);

						if (pb->first) {
							if (p->first)
								p->first = setAppend(&p->first, pb->first, 0);
							else {
								digType len = *(pb->first);

								if (*(pb->first + 1) == 0) len--;
								p->first = (digType *)malloc(sizeof(long) * (len + 1));
								if (*(pb->first + 1) == 0)
									memcpy((void*)(p->first + 1), (void*)(pb->first + 2), len * sizeof(long));
								else
									memcpy((void*)(p->first + 1), (void*)(pb->first + 1), len * sizeof(long));
								*(p->first) = len;
							}
							if (pr->next == 0 && *(pb->first + 1) == 0) {
								if (p->first) {
									digType temp[2] = { 1, 0 };
									p->first = setAppend(&p->first, temp, 1);
								}
								else {
									p->first = (digType*)malloc(sizeof(long) * 2);
									*(p->first) = 1;
									*(p->first + 1) = 0;
								}
							}
							if (*(pb->first + 1) != 0) break;
						}
						else break;
					}
				}
			}
		}
	}
}

digType* getSequenceFirst(pRuleNode p) {
	digType* first = (digType*)malloc(sizeof(long));
	int includeEpsilon = 1;

	*first = 0;

	for (pRuleNode i = p; i; i = i->next) {
		pSymbolNode ps = findSymbolPoint(i->serial);
		first = setAppend(&first, ps->first, 0);
		if (*(ps->first + 1)) {
			includeEpsilon = 0;
			break;
		}
	}
	if (includeEpsilon) {
		digType temp[2] = { 1, 0 };
		first = setAppend(&first, temp, 1);
	}

	return first;
}

void getFollow(pSymbolNode p) {

	// p is the start of grammar
	if (p == ll[2]) {
		if (p->follow) {
			digType temp[2] = { 1, -1 };
			p->follow = setAppend(&p->follow, temp, 1);
		}
		else {
			p->follow = (digType*)malloc(sizeof(long) * 2);
			*(p->follow) = 1;
			*(p->follow + 1) = -1;
		}
	}

	for (pRule r = gRules; r; r = r->next) {
		// Rules in the form of A ::= alpha P beta
		for (pRuleNode pr = r->addr->next; pr; pr = pr->next) {
			if (pr->serial == p->serial) {
				pSymbolNode beta;
				pSymbolNode a = findSymbolPoint(r->addr->serial);
				digType* firstOfBeta;

				// beta = epsilon
				if (!pr->next) {
					if (a->follow)
						if (p->follow)
							p->follow = setAppend(&p->follow, a->follow, 1);
						else {
							digType len = *(a->follow) + 1;

							p->follow = (digType *)malloc(sizeof(long) * len);
							memcpy(p->follow, a->follow, len * sizeof(long));
						}
						continue;
				}

				beta = findSymbolPoint(pr->next->serial);
				firstOfBeta = getSequenceFirst(pr->next);

				// First(beta) without epsilon will be appended to Follow(B);
				if (p->follow) {
					p->follow = setAppend(&p->follow, firstOfBeta, 0);
				}
				else {
					digType len = *(firstOfBeta);

					if (*(firstOfBeta + 1) == 0) len--;
					p->follow = (digType *)malloc(sizeof(long) * (len + 1));
					if (*(firstOfBeta + 1) == 0)
						memcpy((void*)(p->follow + 1), (void*)(firstOfBeta + 2), len * sizeof(long));
					else
						memcpy((void*)(p->follow + 1), (void*)(firstOfBeta + 1), len * sizeof(long));
					*(p->follow) = len;
				}

				// if beta can be generalized to epsilon
				if (!*(firstOfBeta + 1)) {
					if (a->follow)
						if (p->follow)
							p->follow = setAppend(&p->follow, a->follow, 1);
						else {
							digType len = *(a->follow) + 1;

							p->follow = (digType *)malloc(sizeof(long) * len);
							memcpy(p->follow, a->follow, len * sizeof(long));
						}
				}

				free(firstOfBeta);
			}
		}
	}
}

void CLAT() {
	digType nCnt = gNonTerSerial / 2;
	digType tCnt = gTerSerial / 2;

	// initialize the analysis table
	AT = (pRuleNode **)malloc(nCnt * sizeof(pRuleNode*));
	for (digType i = 0; i < nCnt; i++) {
		*(AT + i) = (pRuleNode*)malloc(tCnt * sizeof(pRuleNode));
		memset(*(AT + i), 0, tCnt * sizeof(pRuleNode));
	}


	// construct
	for (pRule p = gRules; p; p = p->next) {
		digType* first;
		pSymbolNode A = findSymbolPoint(p->addr->serial);
		digType i = 1;

		// A ::= epsilon
		if (!p->addr->next->serial) {
			first = (digType*)malloc(2 * sizeof(long));
			*(first) = 1;
			*(first + 1) = 0;
		}
		else
			first = getSequenceFirst(p->addr->next);

		// epsilon in first(alpha)
		if (!*(first + i)) {
			for (digType j = 1; j <= *(A->follow); j++) {
				// for each terminal in Follow(A)
				// set AT[A, j] = r
				if (*(A->follow + j) == -1)
					AT[A->serial / 2][0] = p->addr->next;
				else
					AT[A->serial / 2][*(A->follow + j) / 2] = p->addr->next;
			}
			i++;
		}

		// for each terminal in first(alpha)
		// set AT[A, i] = r
		for (; i <= *first; i++) {
			AT[A->serial / 2][*(first + i) / 2] = p->addr->next;
		}

		free(first);
	}
}

void PreLL1() {
	digType cflag = 0;

	// Detect and eliminate left recursion
	DLR();

#ifdef _DEBUG
	printf("After deleting the left recursion: \n");

	for (pRule p = gRules; p; p = p->next) {
		for (pRuleNode pr = p->addr; pr; pr = pr->next) {
			printf("%s ", pr->symbol);
		}
		printf("\n");
	}
	printf("\n\n\n");
#endif // _DEBUG

	// Terminals First set
	for (pSymbolNode p = ll[1]; p; p = p->next) {
		getSymbolFirst(p);
	}

	// Nonterminals First set
	while (1)
	{
		for (pSymbolNode p = ll[0]; p; p = p->next) {
			getSymbolFirst(p);
		}

		if (cflag == setCount(getSymbolFirst)) break;
		else cflag = setCount(getSymbolFirst);
	}

#ifdef _DEBUG
	printf("The First sets: \n");

	for (pSymbolNode p = ll[0]; p; p = p->next) {
		printf("%s: ", p->symbol);
		if (p->first)
			for (unsigned int i = 1; i <= *(p->first); i++) {
				char *s = findSerial(*(p->first + i));
				printf("%s ", s);
				free(s);
			}
		printf("\n");
	}
	printf("\n\n\n");
#endif // _DEBUG

	cflag = 0;

	//  Follow set
	while (1)
	{
		for (pSymbolNode p = ll[0]; p; p = p->next) {
			getFollow(p);
		}

		if (cflag == setCount(getFollow)) break;
		else cflag = setCount(getFollow);
	}
#ifdef _DEBUG
	printf("The Follow sets: \n");

	for (pSymbolNode p = ll[0]; p; p = p->next) {
		printf("%s: ", p->symbol);
		if (p->follow)
			for (unsigned int i = 1; i <= *(p->follow); i++) {
				char *s = findSerial(*(p->follow + i));
				printf("%s ", s);
				printf("(%d) ", *(p->follow + i));
				free(s);
			}
		printf("\n");
	}
	printf("\n\n\n");
#endif // _DEBUG

	// Construct LL(1) analysis table
	CLAT();

#ifdef _DEBUG
	printf("The Analysis table: \n\t");

	for (digType i = 0; i < gTerSerial / 2; i++) {
		if (!i)
			printf("# ");
		else {
			char* s = findSerial(i * 2);
			printf("%s ", s);
			free(s);
		}
	}
	printf("\n");

	for (digType row = 0; row < gNonTerSerial / 2; row++) {
		char* s = findSerial(row * 2 + 1);
		printf("%s\t", s);
		free(s);
		for (digType col = 0; col < gTerSerial / 2; col++) {
			if (!AT[row][col]) {
				printf(". ");
				continue;
			}

			s = findSerial(AT[row][col]->serial);
			if (s)
				printf("%s ", s);
			else
				printf("0 ");
			free(s);
		}
		printf("\n");
	}
	printf("\n\n\n");
#endif // _DEBUG
}