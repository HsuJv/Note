// hookdbg.cpp
#include <stdio.h>
#include <Windows.h>

LPVOID  g_pWriteFile = NULL;
CREATE_PROCESS_DEBUG_INFO g_cpdi;
BYTE    g_chINT3 = 0xcc, g_chOrgByte = 0;

void DebugLoop();
bool OnCreateProcessDebugEvent(LPDEBUG_EVENT);
bool OnExceptionDebugEvent(LPDEBUG_EVENT);


int main(int argc, char* argv[])
{
    DWORD   dwPID;
    if (argc != 2) {
        printf("\nUsage: hookdbg.exe pid\n");
        return 1;
    }

    // Attach Process
    dwPID = atoi(argv[1]);
    if (!DebugActiveProcess(dwPID)) {
        printf("DebugActiveProcess(%d) failed!!\nError Code = %d\n", dwPID, GetLastError());
        return 1;
    }

    // 调试器循环
    DebugLoop();

    return 0;
}


// TODO: 类似于窗口过程函数(WndProc)
// 从被调试者处接收事件并处理, 然后使被调试者继续运行
void DebugLoop() {
    DEBUG_EVENT  de;
    DWORD        dwContinueStatus;

    // 等待被调试者发生事件
    // API: WaitForDebugEvent
    // BOOL APIENTRY WaitForDebugEvent(
    //      _Out_ LPDEBUG_EVENT lpDebugEvent,
    //      _In_ DWORD dwMilliseconds
    //  );
    // 由DEBUG_EVENT结构体de接收被调试进程的所有调试事件
    while (WaitForDebugEvent(&de, INFINITE))
    {
        dwContinueStatus = DBG_CONTINUE;
        // 被调试进程生成或者附加事件
        if (CREATE_PROCESS_DEBUG_EVENT == de.dwDebugEventCode) {
            OnCreateProcessDebugEvent(&de);
        }
        // 异常事件
        else if (EXCEPTION_DEBUG_EVENT == de.dwDebugEventCode) {
            if (OnExceptionDebugEvent(&de))
                continue;
        }
        // 被调试进程终止事件
        else if (EXIT_PROCESS_DEBUG_EVENT == de.dwDebugEventCode) {
            // 调试器终止
            break;
        }
        // 再次运行被调试者
        // API: ContinueDebugEvent
        // BOOL APIENTRY ContinueDebugEvent(
        // _In_ DWORD dwProcessId,
        // _In_ DWORD dwThreadId,
        // _In_ DWORD dwContinueStatus
        // );
        // TODO: 使被调试者继续运行, 
        // 如果调试事件处理正常, 则dwContinueStatus应为DBG_CONTINUE
        // 若无法处理, 希望在应用程序的SEH中处理, 则dwContinueStatus应为DBG_EXCEPTION_NOT_HANDLED
        ContinueDebugEvent(de.dwProcessId, de.dwThreadId, dwContinueStatus);
    }
}

// TODO: 首先获取WriteFile() API的起始地址(调试者和被调试者具有相同的RVA)
// 然后获取被调试进程句柄, 并设置断点
bool OnCreateProcessDebugEvent(LPDEBUG_EVENT pde) {
    // 获取WriteFile() API地址
    g_pWriteFile = GetProcAddress(GetModuleHandleA("kernel32.dll"), "WriteFile");

    // 通过CREATE_PROCESS_DEBUG_INFO结构体的hProcess成员获取被调试进程句柄
    memcpy(&g_cpdi, &pde->u.CreateProcessInfo, sizeof(CREATE_PROCESS_DEBUG_INFO));

    // API "钩子" - WriteFile()
    // 设置断点, 保存原始字节值(调试器拥有被调试者的调试权限)
    ReadProcessMemory(g_cpdi.hProcess, g_pWriteFile, &g_chOrgByte, sizeof(BYTE), NULL);
    WriteProcessMemory(g_cpdi.hProcess, g_pWriteFile, &g_chINT3, sizeof(BYTE), NULL);

    return true;
}

bool OnExceptionDebugEvent(LPDEBUG_EVENT pde) {
    CONTEXT     ctx;
    PBYTE       lpBuffer = NULL;
    DWORD       dwNumOfBytesToWrite, dwAddrOfBuffer, i;
    PEXCEPTION_RECORD per = &pde->u.Exception.ExceptionRecord;

    // 是断点异常(INT 3)时
    if (EXCEPTION_BREAKPOINT == per->ExceptionCode) {
        // 断点地址为WriteFile() API地址时
        if (g_pWriteFile == per->ExceptionAddress) {
            // 1. Unhook
            // 将0xcc恢复
            WriteProcessMemory(g_cpdi.hProcess, g_pWriteFile, &g_chOrgByte, sizeof(BYTE), NULL);

            // 2. 获取线程上下文
            ctx.ContextFlags = CONTEXT_CONTROL;
            GetThreadContext(g_cpdi.hThread, &ctx);

            // 3. 获取WriteFile()的第2, 3个参数
            // param 2 : ESP + 0x8
            // param 3 : ESP + 0xc
            ReadProcessMemory(g_cpdi.hProcess, (LPVOID)(ctx.Esp + 0x8), &dwAddrOfBuffer, sizeof(DWORD), NULL);
            ReadProcessMemory(g_cpdi.hProcess, (LPVOID)(ctx.Esp + 0xc), &dwNumOfBytesToWrite, sizeof(DWORD), NULL);

            // 4. 分配临时缓冲区
            lpBuffer = (PBYTE)malloc(dwNumOfBytesToWrite + 1);
            memset(lpBuffer, 0, dwNumOfBytesToWrite + 1);

            // 5. 复制WriteFile()缓冲区到临时缓冲区
            ReadProcessMemory(g_cpdi.hProcess, (LPVOID)dwAddrOfBuffer, lpBuffer, dwNumOfBytesToWrite, NULL);
            printf("\n### original string: %s\n", lpBuffer);

            // 6. 大小写互换
            for (i = 0; i < dwNumOfBytesToWrite; i++) {
                if (isalpha(lpBuffer[i]))
                    lpBuffer[i] ^= 0x20;
            }
            printf("\n### converted string: %s\n", lpBuffer);

            // 7. 将变换后的缓冲区复制到WriteFile()缓冲区
            WriteProcessMemory(g_cpdi.hProcess, (LPVOID)dwAddrOfBuffer, lpBuffer, dwNumOfBytesToWrite, NULL);

            // 8. 释放临时缓冲区
            free(lpBuffer);

            // 9. 将上下文的EIP更改为WriteFile()首地址
            // 由于执行完INT 3, 当前EIP比首地址大1
            ctx.Eip = (DWORD)g_pWriteFile;
            SetThreadContext(g_cpdi.hThread, &ctx);

            // 10. 运行被调试进程
            ContinueDebugEvent(pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE);
            Sleep(0);

            // 11. API"钩子"
            WriteProcessMemory(g_cpdi.hProcess, g_pWriteFile, &g_chINT3, sizeof(BYTE), NULL);

            return true;
        }
    }
    return false;
}