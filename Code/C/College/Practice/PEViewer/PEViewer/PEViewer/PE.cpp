#include	"stdafx.h"
#include	"PE.h"
#include	"ConstValue.h"

PE::PE() {
	isInit = 0;
}

bool PE::IsInit() {
	if (isInit) return true;
	return false;
}

bool PE::OpenPE(char const *path) {
	f = NULL;
	fopen_s(&f, path, "rb");
	if (!f) {
		cout << "Can't open the file, ";
		cout << "check the path again. " << endl;
		Sleep(SleepTime);
		return false;
	}
	isInit = 1;
	return true;
}


PE::~PE() {
	if (f != NULL)
		fclose(f);
}

DWORD PE::RVA2RAW(DWORD rva) {
	IMAGE_SECTION_HEADER    ISH;
	DWORD                   ret = -1;

	s.stackPush(ftell(f));
	fseek(f, e_lrash, 0);
	for (int i = 0; i < NumberOfSections; i++) {
		fread(&ISH, sizeof(IMAGE_SECTION_HEADER), 1, f);
		if (rva >= ISH.VirtualAddress && rva <= ISH.VirtualAddress + ISH.Misc.VirtualSize) {
			ret = rva - ISH.VirtualAddress + ISH.PointerToRawData;
			if (ret > ISH.PointerToRawData + ISH.SizeOfRawData)
				ret = -1;
			break;
		}
	}
	fseek(f, s.stackPop(), 0);
	return ret;
}

DWORD PE::PrintStrByRaw(DWORD offset) {
	char           ch;
	DWORD          cnts = 0;    // the number of characteristics to be printed

	s.stackPush(ftell(f));
	fseek(f, offset, 0);
	do {
		fread(&ch, 1, 1, f);
		if (ch == '\0') {
			break;
		}
		cout << ch;
		cnts++;
	} while (1);
	fseek(f, s.stackPop(), 0);
	return cnts;
}

bool PE::Is32PE() {
	DWORD   PESignature = 0x00004550;   // "PE"00
	DWORD   dw;
	WORD    w;

	fseek(f, 0x3c, 0);
	fread(&e_lfanew, sizeof(dw), 1, f);
	fseek(f, e_lfanew, 0);
	fread(&dw, sizeof(dw), 1, f);
	if (dw != PESignature)
		return false;
	fread(&w, sizeof(w), 1, f);
	if (w != 0x014C)
		return false;
	e_lraidd = ftell(f) + 0x72;                 // get the offset of IDD
	fread(&NumberOfSections, sizeof(w), 1, f);  // get the number of sections 
	fseek(f, 3 * sizeof(dw), 1);
	fread(&e_lrash, sizeof(w), 1, f);
	e_lrash = e_lrash + (2 + ftell(f));         // get the offset of section header
	return true;
}

void PE::ShowDosHeader() {
	IMAGE_DOS_HEADER    IDH;

	fseek(f, 0, 0);
	fread(&IDH, sizeof(IDH), 1, f);
	printf("\t\t\t%s\n", "DOS Header");
	printf("%04x\t\t\t\t\t%s\n", IDH.e_magic, "Magic number");
	printf("%08x\t\t\t\t%s\n", IDH.e_lfanew, "File address of new exe header");
}

void PE::ShowNTHeader(int flg) {
	fseek(f, e_lfanew, 0);
	char	time[26];
	IMAGE_NT_HEADERS32    PNH;

	fread(&PNH, sizeof(IMAGE_NT_HEADERS32), 1, f);
	ctime_s(time, 26, (time_t *)&PNH.FileHeader.TimeDateStamp);
	time[25] = '\0';
	if (!flg) {
		printf("\t\t\t%s\n", "NT Header");
		printf("%08x\t\t\t\t%s\n", PNH.Signature, "PE Signature");
	}
	if (flg == 1 || !flg) {
		if (!flg) cout << endl << endl;
		printf("\t\t\t%s\n", "File Header");
		printf("%04x\t\t\t\t\t%s\n", PNH.FileHeader.Machine, "Machine Code(0x014c for 32-bits machine, and 0x0200 for 64)");
		printf("%04x\t\t\t\t\t%s\n", PNH.FileHeader.NumberOfSections, "Section Number");
		printf("%08x\t\t\t\t%s%s", PNH.FileHeader.TimeDateStamp, "This file was created at: ", time);
	}
	if (flg == 2 || !flg) {
		if (!flg) cout << endl << endl;
		printf("\t\t\t%s\n", "Optional Header");
		printf("%08x\t\t\t\t%s\n", PNH.OptionalHeader.AddressOfEntryPoint, "The RVA of entry point");
		printf("%08x\t\t\t\t%s\n", PNH.OptionalHeader.ImageBase, "The ImageBase of this file");
		printf("%08x\t\t\t\t%s\n", PNH.OptionalHeader.SectionAlignment, "The alignment of this file's sections in memory");
		printf("%08x\t\t\t\t%s\n", PNH.OptionalHeader.FileAlignment, "The alignment of this file's sections on disk");
		printf("%04x\t\t\t\t\t%s\n", PNH.OptionalHeader.Subsystem, "1 for driver files, 2 for windows app and 3 for console app");
	}
}

void PE::ShowSectionHeader() {
	fseek(f, e_lrash, 0);
	IMAGE_SECTION_HEADER    ISH;

	for (int i = 0; i < NumberOfSections; i++) {
		DWORD   dw;

		if (i) cout << endl << endl;
		printf("\t\t\t%s%d\n", "Section ", i + 1);
		fread(&ISH, sizeof(IMAGE_SECTION_HEADER), 1, f);
		printf("%08x\t\t\t\t%s\n", ISH.Misc.VirtualSize, "The size of this section in memory");
		printf("%08x\t\t\t\t%s\n", ISH.VirtualAddress, "The RVA of this section in memory");
		printf("%08x\t\t\t\t%s\n", ISH.SizeOfRawData, "The size of this section on disk");
		printf("%08x\t\t\t\t%s\n", ISH.PointerToRawData, "The RVA of this section on disk");
		printf("%08x\t\t\t\t%s\n", ISH.Characteristics, "Section characteristics");
		dw = ISH.Characteristics;
		if (dw >= 0x80000000) {
			printf("\t\t\t\t\t\t%s\n", "Writeable;");
			dw -= 0x80000000;
		}
		if (dw >= 0x40000000) {
			printf("\t\t\t\t\t\t%s\n", "Readable;");
			dw -= 0x40000000;
		}
		if (dw >= 0x20000000) {
			printf("\t\t\t\t\t\t%s\n", "Executable;");
			dw -= 0x20000000;
		}
		if (dw >= 0x80) {
			printf("\t\t\t\t\t\t%s\n", "Uninitialized Data");
			dw -= 0x80;
		}
		if (dw >= 0x40) {
			printf("\t\t\t\t\t\t%s\n", "Initialized Data");
			dw -= 0x40;
		}
		if (dw >= 0x20) {
			printf("\t\t\t\t\t\t%s\n", "Contains Code");
		}
	}
}

void PE::ShowINT() {
	IMAGE_DATA_DIRECTORY    IDD;
	DWORD   e_lraiid;   // raw address of the image import descriptor

	fseek(f, e_lraidd + sizeof(IMAGE_DATA_DIRECTORY), 0);
	fread(&IDD, sizeof(IMAGE_DATA_DIRECTORY), 1, f);
	e_lraiid = RVA2RAW(IDD.VirtualAddress);
	if (e_lraidd + 1) {
		fseek(f, e_lraiid, 0);
	}
	else {
		cout << "Something's wrong." << endl;
		cout << "Can not get the offset of Import Directory Table." << endl;
		cout << "Or there's no function exported." << endl;
		return;
	}
	do {
		IMAGE_IMPORT_DESCRIPTOR     IID;

		fread(&IID, sizeof(IMAGE_IMPORT_DESCRIPTOR), 1, f);
		if (IID.ForwarderChain == 0 && IID.Name == 0 && IID.FirstThunk == 0) break;
		PrintStrByRaw(RVA2RAW(IID.Name));   // print the dll names
		cout << ": ";
		s.stackPush(ftell(f));
		fseek(f, RVA2RAW(IID.OriginalFirstThunk), 0);
		do {
			// WORD    hint;
			DWORD   e_lrvaiibn;     // the rva of struct image_import_by_name 

			fread(&e_lrvaiibn, sizeof(DWORD), 1, f);
			if (!e_lrvaiibn) {
				cout << endl;
				break;      // the end of a import name table
			}
			s.stackPush(ftell(f));
			fseek(f, RVA2RAW(e_lrvaiibn) + 2, 0);
			printf("\n\t\t\t\t\t\t");
			PrintStrByRaw(ftell(f));
			fseek(f, s.stackPop(), 0);
		} while (1);     // print the function name that imported
		fseek(f, s.stackPop(), 0);
	} while (1);
}

void PE::ShowEAT() {
	IMAGE_DATA_DIRECTORY    IDD;
	IMAGE_EXPORT_DIRECTORY  IED;
	DWORD   e_lraied;   // raw address of the image export descriptor

	fseek(f, e_lraidd, 0);
	fread(&IDD, sizeof(IMAGE_DATA_DIRECTORY), 1, f);
	e_lraied = RVA2RAW(IDD.VirtualAddress);
	if (e_lraied + 1) {
		fseek(f, e_lraied, 0);
	}
	else {
		cout << "Something's wrong." << endl;
		cout << "Can not get the offset of Image Export Table." << endl;
		return;
	}
	fseek(f, e_lraied, 0);
	fread(&IED, sizeof(IMAGE_EXPORT_DIRECTORY), 1, f);
	printf("%s\t\t\t\t%s\n", "Ordinal ", "Function Name");
	for (unsigned int i = 0; i < IED.NumberOfNames; i++) {
		WORD    ordinal; // the ordial of function that exported with name
		DWORD   an; // address of function name that exported with name

		fseek(f, RVA2RAW(IED.AddressOfNameOrdinals) + i * 2, 0);
		fread(&ordinal, 2, 1, f);
		printf("%04x\t\t\t\t\t", ordinal);
		fseek(f, RVA2RAW(IED.AddressOfNames) + i * 4, 0);
		fread(&an, 4, 1, f);
		PrintStrByRaw(RVA2RAW(an));
		cout << endl;
	}
}
