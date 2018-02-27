#pragma once

extern "C"
struct node
{
	DWORD			value;
	node*	next;

	node() : next(NULL) {}
	node(DWORD t) : value(t), next(NULL) {}
};

extern "C"
class stack
{
	int		cnts;
	node *head;
public:

	stack() { cnts = 0; head = new node; }
	void		stackPush(DWORD arg);
	void		stackPop(DWORD &arg);
	DWORD		stackPop();
	DWORD		stackTop();

	void		printStack();
	int			counts();
	bool		isEmpty();
};