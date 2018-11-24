// dllStack.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "Stack.h"

extern Stack* s;

extern "C" DLLSTACKAPI void WINAPI StackPush(long arg) {
	s->StackPush(arg);
}

extern "C" DLLSTACKAPI void WINAPI StackPop(long* arg) {
	s->StackPop(*arg);
}

extern "C" DLLSTACKAPI long WINAPI StackTop() {
	return s->StackTop();
}

extern "C" DLLSTACKAPI long* WINAPI Stack2Array() {
	return s->Stack2Array();
}

extern "C" DLLSTACKAPI long	WINAPI counts() {
	return s->counts();
}

extern "C" DLLSTACKAPI long WINAPI isEmpty() {
	return (long)s->isEmpty();
}
