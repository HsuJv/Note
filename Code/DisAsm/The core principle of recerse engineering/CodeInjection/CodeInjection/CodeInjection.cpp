// CodeInjection.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// Thread Parameter
typedef struct _THREAD_PARAM {
	FARPROC pFunc[2];		// LoadLibraryA(), GetProcAddress()
	char	szBuf[4][128];  // "user32.dll", "MessageBoxA"
							// "www.reversecore.com", "ReverseCore"
} THREAD_PARAM, *PTHREAD_PARAM;

// LoadLibraryA()
typedef HMODULE (WINAPI *PFLOADLIBRARY)(LPCSTR lpLibFileName);

// GetProcAddress()
typedef FARPROC (WINAPI *PFGETPROCADDRESS)(HMODULE hModule, LPCSTR lpProcName);
	
// MessageBoxA()
typedef int (WINAPI *PFMESSAGEBOXA)(HWND hwnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

// Thread Procedure
DWORD WINAPI ThreadProc(LPVOID lParam) {
	PTHREAD_PARAM	pParam = (PTHREAD_PARAM)lParam;
	HMODULE			hMod = NULL;
	FARPROC			pFunc = NULL;
	// LoadLibrary("user32.dll")
	// pParam->pFunc[0] -> kernel32!LoadLibraryA()
	// pParam->szBuf[0] -> "user32.dll"
	hMod = ((PFLOADLIBRARY)pParam->pFunc[0])(pParam->szBuf[0]);

	// GetProcAddress("MessageBoxA")
	// pParam->pFunc[1] -> kernel32!GetProcAddress()
	// pParam->szBuf[1] -> "MessageBoxA"
	pFunc = (FARPROC)((PFGETPROCADDRESS)pParam->pFunc[1])(hMod, pParam->szBuf[1]);

	// MessageBoxA(NULL, "www.reversecore.com", "ReverseCore", MB_OK)
	// pParam->pFunc[2] -> "www.reversecore.com"
	// pParam->szBuf[3] -> "ReverseCore"
	((PFMESSAGEBOXA)pFunc)(NULL, pParam->szBuf[2], pParam->szBuf[3], MB_OK);

	return 0;
}

BOOL InjectCode(DWORD dwPID) {
	HMODULE			hMod = NULL;
	THREAD_PARAM	param = { 0, };
	HANDLE			hProcess = NULL;
	HANDLE			hThread = NULL;
	LPVOID			pRemoteBuf[2] = { 0, };
	DWORD			dwSize = 0;

	hMod = GetModuleHandleA("kernel32.dll");

	// set THREAD_PARAM
	param.pFunc[0] = GetProcAddress(hMod, "LoadLibraryA");
	param.pFunc[1] = GetProcAddress(hMod, "GetProcAddress");
	strcpy_s(param.szBuf[0], "user32.dll");
	strcpy_s(param.szBuf[1], "MessageBoxA");
	strcpy_s(param.szBuf[2], "www.reversecore.com");
	strcpy_s(param.szBuf[3], "ReverseCore");

	// Open Process
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);

	// Allocation for THREAD_PARAM
	dwSize = sizeof(THREAD_PARAM);
	pRemoteBuf[0] = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(hProcess, pRemoteBuf[0], (LPVOID)&param, dwSize, NULL);

	// Allocation for ThreadProc()
	dwSize = (DWORD)InjectCode - (DWORD)ThreadProc;
	pRemoteBuf[1] = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(hProcess, pRemoteBuf[1], (LPVOID)ThreadProc, dwSize, NULL);


	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pRemoteBuf[1],
		pRemoteBuf[0], 0, NULL);
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return TRUE;
}

BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege) {
	TOKEN_PRIVILEGES tp;
	HANDLE hToken;
	LUID luid;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken))
	{
		printf("OpenProcessToken error: %u\n", GetLastError());
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL,           // lookup privilege on local system
		lpszPrivilege,  // privilege to lookup 
		&luid))        // receives LUID of privilege
	{
		printf("LookupPrivilegeValue error: %u\n", GetLastError());
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	// Enable the privilege or disable all privileges.
	if (!AdjustTokenPrivileges(hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL))
	{
		printf("AdjustTokenPrivileges error: %u\n", GetLastError());
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		printf("The token does not have the specified privilege. \n");
		return FALSE;
	}

	return TRUE;
}

int main(int argc, char* argv[])
{
	DWORD			dwPID = 0;
	if (argc != 2) {
		printf("\n USAGE : %s pid\n", argv[0]);
		return 1;
	}

	// change privilege
	if (!SetPrivilege(SE_DEBUG_NAME, TRUE))
		return 1;

	// code injection
	dwPID = (DWORD)atol(argv[1]);
	InjectCode(dwPID);
    return 0;
}

