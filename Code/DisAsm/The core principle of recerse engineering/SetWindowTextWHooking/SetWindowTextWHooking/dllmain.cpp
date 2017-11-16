// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

FARPROC g_pOrgFun;
typedef bool(*PFSETWINDOWTEXTW)(HWND, LPWSTR);

bool __stdcall hook_iat(LPCSTR, PROC, PROC);
bool __stdcall MySetWindowTextW(HWND, LPWSTR);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		// 保存原始api地址, 为脱钩用
		g_pOrgFun = GetProcAddress(GetModuleHandle(L"user32.dll"), "SetWindowTextW");

		// hook
		hook_iat("user32.dll", g_pOrgFun, (PROC)MySetWindowTextW);
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		// unhook
		hook_iat("user32.dll", (PROC)MySetWindowTextW, g_pOrgFun);
		break;
	}
	return TRUE;
}

bool __stdcall MySetWindowTextW(HWND hWnd, LPWSTR lpString) {
	wchar_t* pNum = L"零一二三四五六七八九";
	wchar_t temp[2] = { 0, };
	int i = 0, nLen = 0, nIndex = 0;
	
	nLen = wcslen(lpString);
	for (i = 0; i < nLen; i++) {
		if (L'0' <= lpString[i] && lpString[i] <= L'9') {
			temp[0] = lpString[i];
			nIndex = _wtoi(temp);
			lpString[i] = pNum[nIndex];
		}
	}
	return ((PFSETWINDOWTEXTW)g_pOrgFun)(hWnd, lpString);
}

bool __stdcall hook_iat(LPCSTR szDllName, PROC src, PROC dest) {
	HMODULE hMod;
	LPCSTR szLibName;
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc;
	PIMAGE_THUNK_DATA pThunk;
	DWORD dwOldProtect, dwRVA;
	PBYTE pAddr;

	// hMod, pAddr = ImageBase of calc.exe
	//               VA to MZ signature(IMAGE_DOS_HEADER)
	hMod = GetModuleHandle(NULL);
	pAddr = (PBYTE)hMod;

	// pAddr = VA to PE signature (IMAGE_NT_HEADRERS)
	pAddr += *((DWORD*)&pAddr[0x3C]);

	// dwRVA = RVA to IMAGE_IMPORT_DESCRIPTOR
	dwRVA = *((DWORD*)&pAddr[0x80]);

	// pImportDesc = VA to IMAGE_IMPORT_DESCRIPTOR Table
	pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)hMod + dwRVA);

	for (; pImportDesc->Name; pImportDesc++) {
		// szLibName = VA to IMAGE_IMPORT_DESCRIPTOR.Name
		szLibName = (LPCSTR)((DWORD)hMod + pImportDesc->Name);

		if (!_stricmp(szLibName, szDllName)) {
			// pThunk = IMAGE_IMPORT_DESCRIPTOR.FirstThunk
			//	      = VA to IAT
			pThunk = (PIMAGE_THUNK_DATA)((DWORD)hMod + pImportDesc->FirstThunk);

			// pThunk->u1.Function = VA to API
			for (; pThunk->u1.Function; pThunk++) {
				if (pThunk->u1.Function == (DWORD)src) {
					// 更改内存属性为E/R/W
					VirtualProtect((LPVOID)&pThunk->u1.Function, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);

					// 修改IAT
					pThunk->u1.Function = (DWORD)dest;

					// 恢复内存属性
					VirtualProtect((LPVOID)&pThunk->u1.Function, 4, dwOldProtect, &dwOldProtect);
					
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}