#pragma once
#ifndef STACK_H
#define STACK_H

typedef void(*pStackPush)(long);
typedef void(*pStackPop)(long*);
typedef long(*pStackTop)();
typedef long* (*pStack2Array)();
typedef long(*pcounts)();
typedef long(*pisEmpty)();

// Import founction name
pStackPush StackPush;
pStackPop StackPop;
pStackTop StackTop;
pStack2Array Stack2Array;
pcounts StackCounts;
pisEmpty StackIsEmpty;

// Initialize the stack, load the relational dll
void stackInit();

// Disposal the stack, deload the dll
void stackDisposal();
#endif // !STACK_H
