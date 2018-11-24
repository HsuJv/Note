#pragma once

extern "C"
struct Node
{
	long	value;
	Node* next;

	Node() : next(NULL) {}
	Node(long t) : value(t), next(NULL) {}
};

extern "C"
class Stack
{
private:
	long	cnts;
	Node *top;

public:
	Stack() { cnts = 0; top = new Node;}
	~Stack() {
		Node* p;
		for (Node* n = top->next; n;) {
			p = n;
			n = n->next;
			delete p;
		} 
		top = NULL;
	}
	void		StackPush(long arg);
	void		StackPop(long &arg);
	long			StackTop();

	long			counts();
	long*		Stack2Array();
	bool		isEmpty();
};