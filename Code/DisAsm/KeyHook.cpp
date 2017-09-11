// KeyHook.cpp
#include    "windows.h"

#define     DEF_PROCESS_NAME    "notepad.exe"

HINSTANCE   g_hInstance = NULL;
HHOOK       g_hHook = NULL;
HWND        g_hWnd = NULL;

BOOL APIENTRY DllMain(HMODULE   hModule,
    DWORD   ul_reason_for_call,
    LPVOID  lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_hInstance = hModule;
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

LRESULT CALLBACK KeyboardProc(int nCode,
    WPARAM wParam,
    LPARAM lParam
)
{
    char    szPath[MAX_PATH] = { 0, };
    char    *p = NULL;

    if (nCode == 0) {
        // bit 31: 0 = key press, 1 = key release
        if (!(lParam & 0x80000000)) { // key release
            GetModuleFileNameA(NULL, szPath, MAX_PATH);
            p = strrchr(szPath, '\\');

            // 比较进程名称, 如果是目标进程, 则消息不会传递
            if (!_stricmp(p + 1, DEF_PROCESS_NAME))
                return 1;
        }
    }

    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    __declspec(dllexport) void HookStart() {
        g_hHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_hInstance, 0);
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    __declspec(dllexport) void HookStop() {
        UnhookWindowsHookEx(g_hHook);
        g_hHook = NULL;
    }

#ifdef __cplusplus
}
#endif // __cplusplus
