// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "Stack.h"

typedef Stack* pStack;

pStack s;

BOOL APIENTRY DllMain( HMODULE hModule,
                       long  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		s = new Stack();
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		s->~Stack();
		break;
	}
	return TRUE;
}

