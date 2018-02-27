#pragma once
#include	"stack.h"

extern	"C"
class PE
{
    
private:
    FILE    *f;
    DWORD   e_lfanew;
    WORD    NumberOfSections;
    WORD    e_lrash; // raw address of the section header
    WORD    e_lraidd; // raw address of the image_data_directory(idd)
    stack   s; // stack for this class
	int		isInit; // to confirm whether the method "OpenPE" is called
    
    DWORD   RVA2RAW(DWORD rva);
    DWORD   PrintStrByRaw(DWORD offset);

public:
    PE();
    bool OpenPE(char const *path);
    ~PE();
	bool IsInit();
    bool Is32PE();
    void ShowDosHeader();
    void ShowNTHeader(int flg);
    void ShowSectionHeader();
    void ShowINT();
    void ShowEAT();
};
