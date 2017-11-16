// InjectDll.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
// InjectDll.cpp
#include "windows.h"  
#include "stdio.h"  

BOOL InjectDll(DWORD dwPID, PCHAR szDllPath)
{
	HMODULE         hMod = NULL;
	HANDLE          hProcess = NULL;
	HANDLE          hThread = NULL;
	LPVOID          pRemoteBuf = 0;
	DWORD           dwSize = 0;
	LPTHREAD_START_ROUTINE pThreadProc;


	// #1. ʹ��dwPID��ȡĿ����̾��
	if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS,   // dwDesiredAccess  
		FALSE,                // bInheritHandle  
		dwPID)))             // dwProcessId  
	{
		printf("OpenProcess() fail : err_code = %d\n", GetLastError());
		return FALSE;
	}

	// #2. ��Ŀ������ڴ��з���szDllName��С���ڴ�
	dwSize = sizeof(char) * (strlen(szDllPath) + 1);
	if (!(pRemoteBuf = VirtualAllocEx(hProcess,             // hProcess  
		NULL,                 // lpAddress  
		dwSize,               // dwSize  
		MEM_COMMIT,           // flAllocationType  
		PAGE_READWRITE)))    // flProtect  
	{
		printf("VirtualAllocEx() fail : err_code = %d\n", GetLastError());
		return FALSE;
	}

	// #3. ��dll·��д�������ڴ�
	if (!WriteProcessMemory(hProcess,                       // hProcess  
		pRemoteBuf,                     // lpBaseAddress  
		(LPVOID)szDllPath,              // lpBuffer  
		dwSize,                         // nSize  
		NULL))                         // [out] lpNumberOfBytesWritten  
	{
		printf("WriteProcessMemory() fail : err_code = %d\n", GetLastError());
		return FALSE;
	}

	// #4. ��ȡLoadLibraryA() API�ĵ�ַ
	hMod = GetModuleHandleA("kernel32.dll");
	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(
		hMod, "LoadLibraryA");

	// #5. �ڽ����������߳�
	if (!(hThread = CreateRemoteThread(hProcess,            // hProcess  
		NULL,                // lpThreadAttributes  
		0,                   // dwStackSize  
		pThreadProc,         // dwStackSize  
		pRemoteBuf,          // lpParameter  
		0,                   // dwCreationFlags  
		NULL)))             // lpThreadId  
	{
		printf("CreateRemoteThread() fail : err_code = %d\n", GetLastError());
		return FALSE;
	}

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return TRUE;
}


int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("USAGE : %s pid dll_path\n", argv[0]);
		return 1;
	}

	// inject dll
	if (InjectDll((DWORD)atol(argv[1]), argv[2]))
		printf("InjectDll(\"%s\") success!\n", argv[2]);
	else
		printf("InjectDll(\"%s\") failed!\n", argv[2]);
	return 0;
}

// main()��������Ҫ�����Ǽ���������Ĳ���, 
// Ȼ�����InjectDll()����
// 
// InjectDll()����������ʵʩdllע��ĺ��ĺ���
// �书��������Ŀ��������е���LoadLibrary("*.dll") API
// 
// hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID)):
// ����OpenProcess() API, ��������dwPID��ȡĿ����̵ľ��
// (PROCESS_ALL_ACCESSȨ��), ֮��, �Ϳ���ʹ�û�ȡ�ľ��(hProcess)
// ���ƶ�Ӧ����
// 
// pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwSize, 
//                      MEM_COMMIT, PAGE_READWRITE)):
// ��Ҫ�Ѽ������ص�dll�ļ���·��(�ַ���)��֪Ŀ�����
// ��Ϊ�κ��ڴ�ռ䶼�޷�����д�����, ��������VirtualAllocEx() API
// ��Ŀ����̵��ڴ�ռ��з���һ�黺����
// 
// WriteProcessMemory(hProcess, pRemoteBuf, 
//                  (LPVOID)szDllPath, dwSize, NULL):
// ʹ��WriteProcessMemory() API��dll·���ַ���д��������õĻ�����
// (pRemoteBuf)��ַ, ����, Ҫע���dll�ļ���·���ͱ�д��Ŀ�����
// 
// hMod = GetModuleHandleA("kernel32.dll");
// pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(
//      hMod, "LoadLibraryA"):
// ����LoadLibrary() APIǰҪ�Ȼ�ȡ���ַ
// �öδ����ȡ����InjectDll.exe�����е�kernel32.dll��ַ
// ����ϵͳdll����������е�ImageBase, ���ᷢ���ض�λ����
// ���Խ���InjectDll.exe�е�kernel32.dll��ַ��Ŀ������еĵ�ַ��һ����
// 
// hThread = CreateRemoteThread(hProcess, NULL, 0, 
//          pThreadProc, pRemoteBuf, 0, NULL):
// �����Ŀ����̷�������, �������LoadLibraryA() API������ָ����dll�ļ�
// Ȼ��Windows��δ�ṩִ�����������API, ��������辶��CreateRemoteThread() API
// HANDLE WINAPI CreateRemoteThread(
// __in  HANDLE                 hProcess,  // Ŀ����̾��
// __in  LPSECURITY_ATRIBUTES   lpThreadAttributes,
// __in  SIZE_T                 dwStackSize,
// __in  LPTHREAD_START_ROUTINE lpStartSize,// �̺߳�����ַ
// __in  LPVOID                 lpParameter,// �̲߳�����ַ
// __in  DWORD                  dwCreationFlags,
// __out LPDWORD                lpThreadId
// );
// ��Ϊ�̺߳���ThreadProc()��LoadLibrary()��������һ��4�ֽڵĲ���, һ��4�ֽڵķ���
// �����ô���Զ���̵߳�APIʱ, ���̺߳�����ַ�滻ΪLoadLibrary()��ַ
// ���̲߳�����ַ�滻Ϊdll�ļ�·���ַ������ڵ�ַ
// �Ϳ�����ʹĿ����̼���ָ����dll�ļ�
