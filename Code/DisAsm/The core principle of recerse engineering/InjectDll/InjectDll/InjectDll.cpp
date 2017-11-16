// InjectDll.cpp : 定义控制台应用程序的入口点。
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


	// #1. 使用dwPID获取目标进程句柄
	if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS,   // dwDesiredAccess  
		FALSE,                // bInheritHandle  
		dwPID)))             // dwProcessId  
	{
		printf("OpenProcess() fail : err_code = %d\n", GetLastError());
		return FALSE;
	}

	// #2. 在目标进程内存中分配szDllName大小的内存
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

	// #3. 将dll路径写入分配的内存
	if (!WriteProcessMemory(hProcess,                       // hProcess  
		pRemoteBuf,                     // lpBaseAddress  
		(LPVOID)szDllPath,              // lpBuffer  
		dwSize,                         // nSize  
		NULL))                         // [out] lpNumberOfBytesWritten  
	{
		printf("WriteProcessMemory() fail : err_code = %d\n", GetLastError());
		return FALSE;
	}

	// #4. 获取LoadLibraryA() API的地址
	hMod = GetModuleHandleA("kernel32.dll");
	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(
		hMod, "LoadLibraryA");

	// #5. 在进程中运行线程
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

// main()函数的主要功能是检测输入程序的参数, 
// 然后调用InjectDll()函数
// 
// InjectDll()函数是用来实施dll注入的核心函数
// 其功能是命令目标进程自行调用LoadLibrary("*.dll") API
// 
// hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID)):
// 调用OpenProcess() API, 借助参数dwPID获取目标进程的句柄
// (PROCESS_ALL_ACCESS权限), 之后, 就可以使用获取的句柄(hProcess)
// 控制对应进程
// 
// pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwSize, 
//                      MEM_COMMIT, PAGE_READWRITE)):
// 需要把即将加载的dll文件的路径(字符串)告知目标进程
// 因为任何内存空间都无法进行写入操作, 所以先用VirtualAllocEx() API
// 在目标进程的内存空间中分配一块缓冲区
// 
// WriteProcessMemory(hProcess, pRemoteBuf, 
//                  (LPVOID)szDllPath, dwSize, NULL):
// 使用WriteProcessMemory() API将dll路径字符串写入分配所得的缓冲区
// (pRemoteBuf)地址, 这样, 要注入的dll文件的路径就被写入目标进程
// 
// hMod = GetModuleHandleA("kernel32.dll");
// pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(
//      hMod, "LoadLibraryA"):
// 调用LoadLibrary() API前要先获取其地址
// 该段代码获取的是InjectDll.exe进程中的kernel32.dll地址
// 由于系统dll都有自身固有的ImageBase, 不会发生重定位问题
// 所以进程InjectDll.exe中的kernel32.dll地址和目标进程中的地址是一样的
// 
// hThread = CreateRemoteThread(hProcess, NULL, 0, 
//          pThreadProc, pRemoteBuf, 0, NULL):
// 最后向目标进程发送命令, 让其调用LoadLibraryA() API来加载指定的dll文件
// 然而Windows并未提供执行这样命令的API, 于是另辟蹊径用CreateRemoteThread() API
// HANDLE WINAPI CreateRemoteThread(
// __in  HANDLE                 hProcess,  // 目标进程句柄
// __in  LPSECURITY_ATRIBUTES   lpThreadAttributes,
// __in  SIZE_T                 dwStackSize,
// __in  LPTHREAD_START_ROUTINE lpStartSize,// 线程函数地址
// __in  LPVOID                 lpParameter,// 线程参数地址
// __in  DWORD                  dwCreationFlags,
// __out LPDWORD                lpThreadId
// );
// 因为线程函数ThreadProc()和LoadLibrary()函数都有一个4字节的参数, 一个4字节的返回
// 所以用创建远程线程的API时, 将线程函数地址替换为LoadLibrary()地址
// 将线程参数地址替换为dll文件路径字符串所在地址
// 就可以驱使目标进程加载指定的dll文件
