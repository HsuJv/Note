// PEViewer.cpp : 定义 DLL 应用程序的导出函数。
//

#include	"stdafx.h"
#include	"PE.h"
#include	"PEViewer.h"

extern PE* pe;
extern char path[260];

// todo: to open a PE32 file
// arg: the path of the file to open (relative or absolute)
// ret: if success to open, return TRUE else FALSE
extern "C" 	PEVEIWER_API bool WINAPI ConOpenPE(char const *path){
#ifdef _DEBUG
	if (!pe->OpenPE("Q:\\Users\\Hsu\\Documents\\GitHub\\PEViewer\\test\\notepad.exe12"))
#else
	if (!pe->OpenPE(path))
#endif // _DEBUG
	{
		return false;
	}
	if (!pe->Is32PE())
		return false;
	return true;
}

// todo: show some info of the file DOS header that opened 
// arg: none
// ret: if success, retrun TRUE else FALSE
extern "C" PEVEIWER_API bool WINAPI ConShowDosHeader() {
	if (!pe->IsInit()) return false;
	pe->ShowDosHeader();
	return true;
}

// todo: show some info of the file NT header that opened 
// arg: none
// ret: if success, retrun TRUE else FALSE
extern "C" PEVEIWER_API bool WINAPI ConShowNTHeader() {
	if (!pe->IsInit()) return false;
	pe->ShowNTHeader(0);
	return true;
}

// todo: show some info of the file Section header that opened 
// arg: none
// ret: if success, retrun TRUE else FALSE
extern "C" PEVEIWER_API bool WINAPI ConShowSectionHeader() {
	if (!pe->IsInit()) return false;
	pe->ShowSectionHeader();
	return true;
}