// hookdbg.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

LPVOID	g_pWriteFile = NULL;
CREATE_PROCESS_DEBUG_INFO g_cpdi;
BYTE	g_chINT3 = 0xcc, g_chOrgByte = 0;

void DebugLoop();
bool OnCreateProcessDebugEvent(LPDEBUG_EVENT);
bool OnExceptionDebugEvent(LPDEBUG_EVENT);


int main(int argc, char* argv[])
{
	DWORD	dwPID;
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

	// ������ѭ��
	DebugLoop();

    return 0;
}


// TODO: �����ڴ��ڹ��̺���(WndProc)
// �ӱ������ߴ������¼�������, Ȼ��ʹ�������߼�������
void DebugLoop() {
	DEBUG_EVENT  de;
	DWORD		 dwContinueStatus;

	// �ȴ��������߷����¼�
	// API: WaitForDebugEvent
	// BOOL APIENTRY WaitForDebugEvent(
	//		_Out_ LPDEBUG_EVENT lpDebugEvent,
	//		_In_ DWORD dwMilliseconds
	//	);
	// ��DEBUG_EVENT�ṹ��de���ձ����Խ��̵����е����¼�
	while (WaitForDebugEvent(&de, INFINITE))
	{
		dwContinueStatus = DBG_CONTINUE;
		// �����Խ������ɻ��߸����¼�
		if (CREATE_PROCESS_DEBUG_EVENT == de.dwDebugEventCode) {
			OnCreateProcessDebugEvent(&de);
		}
		// �쳣�¼�
		else if (EXCEPTION_DEBUG_EVENT == de.dwDebugEventCode) {
			if (OnExceptionDebugEvent(&de))
				continue;
		}
		// �����Խ�����ֹ�¼�
		else if (EXIT_PROCESS_DEBUG_EVENT == de.dwDebugEventCode) {
			// ��������ֹ
			break;
		}
		// �ٴ����б�������
		// API: ContinueDebugEvent
		// BOOL APIENTRY ContinueDebugEvent(
		// _In_ DWORD dwProcessId,
		// _In_ DWORD dwThreadId,
		// _In_ DWORD dwContinueStatus
		// );
		// TODO: ʹ�������߼�������, 
		// ��������¼���������, ��dwContinueStatusӦΪDBG_CONTINUE
		// ���޷�����, ϣ����Ӧ�ó����SEH�д���, ��dwContinueStatusӦΪDBG_EXCEPTION_NOT_HANDLED
		ContinueDebugEvent(de.dwProcessId, de.dwThreadId, dwContinueStatus);
	}
}

// TODO: ���Ȼ�ȡWriteFile() API����ʼ��ַ(�����ߺͱ������߾�����ͬ��RVA)
// Ȼ���ȡ�����Խ��̾��, �����öϵ�
bool OnCreateProcessDebugEvent(LPDEBUG_EVENT pde) {
	// ��ȡWriteFile() API��ַ
	g_pWriteFile = GetProcAddress(GetModuleHandleA("kernel32.dll"), "WriteFile");

	// ͨ��CREATE_PROCESS_DEBUG_INFO�ṹ���hProcess��Ա��ȡ�����Խ��̾��
	memcpy(&g_cpdi, &pde->u.CreateProcessInfo, sizeof(CREATE_PROCESS_DEBUG_INFO));

	// API "����" - WriteFile()
	// ���öϵ�, ����ԭʼ�ֽ�ֵ(������ӵ�б������ߵĵ���Ȩ��)
	ReadProcessMemory(g_cpdi.hProcess, g_pWriteFile, &g_chOrgByte, sizeof(BYTE), NULL);
	WriteProcessMemory(g_cpdi.hProcess, g_pWriteFile, &g_chINT3, sizeof(BYTE), NULL);

	return true;
}

bool OnExceptionDebugEvent(LPDEBUG_EVENT pde) {
	CONTEXT		ctx;
	PBYTE		lpBuffer = NULL;
	DWORD		dwNumOfBytesToWrite, dwAddrOfBuffer, i;
	PEXCEPTION_RECORD per = &pde->u.Exception.ExceptionRecord;

	// �Ƕϵ��쳣(INT 3)ʱ
	if (EXCEPTION_BREAKPOINT == per->ExceptionCode) {
		// �ϵ��ַΪWriteFile() API��ַʱ
		if (g_pWriteFile == per->ExceptionAddress) {
			// 1. Unhook
			// ��0xcc�ָ�
			WriteProcessMemory(g_cpdi.hProcess, g_pWriteFile, &g_chOrgByte, sizeof(BYTE), NULL);

			// 2. ��ȡ�߳�������
			ctx.ContextFlags = CONTEXT_CONTROL;
			GetThreadContext(g_cpdi.hThread, &ctx);

			// 3. ��ȡWriteFile()�ĵ�2, 3������
			// param 2 : ESP + 0x8
			// param 3 : ESP + 0xc
			ReadProcessMemory(g_cpdi.hProcess, (LPVOID)(ctx.Esp + 0x8), &dwAddrOfBuffer, sizeof(DWORD), NULL);
			ReadProcessMemory(g_cpdi.hProcess, (LPVOID)(ctx.Esp + 0xc), &dwNumOfBytesToWrite, sizeof(DWORD), NULL);

			// 4. ������ʱ������
			lpBuffer = (PBYTE)malloc(dwNumOfBytesToWrite + 1);
			memset(lpBuffer, 0, dwNumOfBytesToWrite + 1);

			// 5. ����WriteFile()����������ʱ������
			ReadProcessMemory(g_cpdi.hProcess, (LPVOID)dwAddrOfBuffer, lpBuffer, dwNumOfBytesToWrite, NULL);
			printf("\n### original string: %s\n", lpBuffer);

			// 6. ��Сд����
			for (i = 0; i < dwNumOfBytesToWrite; i++) {
				if (isalpha(lpBuffer[i]))
					lpBuffer[i] ^= 0x20;
			}
			printf("\n### converted string: %s\n", lpBuffer);

			// 7. ���任��Ļ��������Ƶ�WriteFile()������
			WriteProcessMemory(g_cpdi.hProcess, (LPVOID)dwAddrOfBuffer, lpBuffer, dwNumOfBytesToWrite, NULL);

			// 8. �ͷ���ʱ������
			free(lpBuffer);

			// 9. �������ĵ�EIP����ΪWriteFile()�׵�ַ
			// ����ִ����INT 3, ��ǰEIP���׵�ַ��1
			ctx.Eip = (DWORD)g_pWriteFile;
			SetThreadContext(g_cpdi.hThread, &ctx);

			// 10. ���б����Խ���
			ContinueDebugEvent(pde->dwProcessId, pde->dwThreadId, DBG_CONTINUE);
			Sleep(0);

			// 11. API"����"
			WriteProcessMemory(g_cpdi.hProcess, g_pWriteFile, &g_chINT3, sizeof(BYTE), NULL);

			return true;
		}
	}
	return false;
}