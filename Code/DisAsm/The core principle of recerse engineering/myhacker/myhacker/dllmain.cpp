// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
//myhack.cpp

#include    "windows.h"
#include    "tchar.h"
#include    "stdlib.h"
#include    "Urlmon.h"

#pragma     comment(lib, "Urlmon.lib")

#define     DEF_URL         (L"http://www.baidu.com")
#define     DEF_FILE_NAME   (L"baidu.html")

HMODULE     g_hMod = NULL;

DWORD __stdcall ThreadProc(LPVOID lParam) {
	TCHAR   szPath[_MAX_PATH] = { 0, };
	if (!GetModuleFileName(g_hMod, szPath, MAX_PATH))
		return FALSE;

	TCHAR   *p = _tcsrchr(szPath, '\\');
	if (!p)
		return FALSE;

	lstrcpy(p + 1, DEF_FILE_NAME);

	URLDownloadToFile(NULL, DEF_URL, szPath, 0, NULL);

	return 0;
}

BOOL __stdcall DllMain(HINSTANCE hinstDLL,
	DWORD     fdwReason,
	LPVOID    lpvReserved
) {
	HANDLE      hThread = NULL;

	g_hMod = (HMODULE)hinstDLL;

	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		OutputDebugString(L"myhack.dll Injection!!!");
		hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
		CloseHandle(hThread);
		break;
	}
	return TRUE;
}

// Dll������(DLL_PROCESS_ATTACH)ʱ, �����һ�������ַ���
// Ȼ�󴴽��̵߳��ú���(ThreadProc)
// ��ThreadProc()�����е���URLDownloadToFile() API������ָ����վ��html�ļ�
