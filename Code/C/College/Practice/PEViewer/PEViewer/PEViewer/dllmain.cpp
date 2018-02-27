// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include	"stdafx.h"
#include	"PE.h"
#include	"ConstValue.h"

typedef PE* pPE;

pPE		pe;
char	path[MAX_PATH];

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 ){
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		pe = new PE();
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		pe->~PE();
		break;
	}
	return TRUE;
}

