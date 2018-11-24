#include "LLmain.h"
#include "Stack.h"


#ifdef _DEBUG
#define dllName 
#endif

void stackInit() {
	HINSTANCE h = LoadLibraryA("dllStack.dll");
	if (h) {
		StackPush = (pStackPush)GetProcAddress(h, "StackPush");
		StackPop = (pStackPop)GetProcAddress(h, "StackPop");
		StackTop = (pStackTop)GetProcAddress(h, "StackTop");
		Stack2Array = (pStack2Array)GetProcAddress(h, "Stack2Array");
		StackCounts = (pcounts)GetProcAddress(h, "counts");
		StackIsEmpty = (pisEmpty)GetProcAddress(h, "isEmpty");
	}
}

void stackDisposal() {
	HINSTANCE h = GetModuleHandleA("dllStack.dll");
	if (h)
		FreeLibrary(h);
}