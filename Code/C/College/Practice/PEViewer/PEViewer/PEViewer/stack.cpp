#include	"stdafx.h"
#include	"stack.h"

void stack::stackPush(DWORD arg) {
	node *pnode = new node(arg); //申请入栈元素的空间
	pnode->next = head->next;
	head->next = pnode;
	cnts++;
}

void stack::stackPop(DWORD &arg) {
	if (head->next != NULL) {
		node* temp = head->next;
		head->next = head->next->next;
		DWORD popVal = temp->value;
		delete temp;
		arg = popVal;
	}
}

DWORD stack::stackPop() {
	if (head->next != NULL) {
		node* temp = head->next;
		head->next = head->next->next;
		DWORD popVal = temp->value;
		delete temp;
		return popVal;
	}
}

DWORD stack::stackTop() {
	if (head->next != NULL) {
		return head->next->value;
	}
	return FALSE;
}

void stack::printStack() {
	if (head->next != NULL) {
		node* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
			cout << temp->value << endl;
		}
	}
}

int stack::counts() {
	return cnts;
}

bool stack::isEmpty() {
	if (cnts)
		return false;
	else
		return true;
}
