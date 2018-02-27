// DllTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef bool(*pOpenPE)(const char *);
typedef bool(*pDOSHeader)();
typedef bool(*pNTHeader)();
typedef bool(*pSecHeader)();


int main()
{
	HINSTANCE h = LoadLibraryA("PEViewer.dll");
	if (h) {
		pOpenPE OpenPE = (pOpenPE)GetProcAddress(h, "ConOpenPE");
		if (OpenPE("222.exe")) {
			pDOSHeader DosHeader = (pDOSHeader)GetProcAddress(h, "ConShowDosHeader");
			DosHeader();
			pNTHeader NTHeader = (pNTHeader)GetProcAddress(h, "ConShowNTHeader");
			NTHeader();
			pSecHeader SecHeader = (pSecHeader)GetProcAddress(h, "ConShowSectionHeader");
			SecHeader();
		}
		FreeLibrary(h);
		
	}
	system("pause");
    return 0;
}

