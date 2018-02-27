#pragma once
extern "C" {
	PEVEIWER_API bool WINAPI ConOpenPE(char const *);
	PEVEIWER_API bool WINAPI ConShowDosHeader();
	PEVEIWER_API bool WINAPI ConShowNTHeader();
	PEVEIWER_API bool WINAPI ConShowSectionHeader();
}
