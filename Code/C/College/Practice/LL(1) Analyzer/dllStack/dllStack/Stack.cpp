#include "stdafx.h"
#include "Stack.h"

void Stack::StackPush(long arg) {
	Node *pNode = new Node(arg);
	pNode->next = top->next;
	top->next = pNode;
	cnts++;
}

void Stack::StackPop(long &arg) {
	if (top->next != NULL) {
		Node* temp = top->next;
		top->next = top->next->next;
		long popVal = temp->value;
		delete temp;
		arg = popVal;
		cnts--;
	}
}

long Stack::StackTop() {
	if (top->next != NULL) {
		return top->next->value;
	}
	return FALSE;
}

long* Stack::Stack2Array() {
	long* ret = (long *)malloc(sizeof(long) * cnts);
	long i = 0;

	for (Node* n = top->next; n; n = n->next) {
		*(ret + i++) = n->value;
	}
	return ret;
}

long Stack::counts() {
	return cnts;
}

bool Stack::isEmpty() {
	if (top->next)
		return FALSE;
	else
		return TRUE;
}
