#include "LA.h"
#include "Terminal.h"
#include "PreprocessingToken.h"
#include "Token.h"

extern char* g_trigraphMap[9];
extern struct _UniversalChar {
	int index;
	unsigned short int value;
	struct _UniversalChar *next;
}*g_pUC;

HANDLE g_semaphore;
char *g_outStream, *g_inStream;

int main(int argc, char **argv) {
	FILE *fInput, *fOutput;
	char *out = FILE_OUTPUT;
	size_t fLen;
	HANDLE la, pp;
	int col = 0;
	char *fin;
	int i = 0, o = 0, u = 0;

	if (argc != 2) {
		printf("Usage: LA.exe target_file");
		return 1;
	}

	if (_access(argv[1], 2)) {
		printf("%s not exists or permession denied", argv[1]);
		return 1;
	}

	// Read the source in the memory
	fopen_s(&fInput, argv[1], "rb");
	fseek(fInput, 0, SEEK_END);
	fLen = ftell(fInput) + 1;
	fseek(fInput, 0, SEEK_SET);
	fin = (char *)malloc(fLen);
	fread_s(fin, fLen, 1, fLen - 1, fInput);
	fin[fLen - 1] = 0;
	fclose(fInput);

	// handle the escape new line and trigraph;
	g_inStream = (char *)malloc(fLen);
	while (*(fin + i)){
		int triMap;
		if (triMap = isTrigraph(fin + i)) {
			*(g_inStream + o++) = g_trigraphMap[triMap - 1][0];
			i += 3;
			continue;
		}
		if (isEscapeNewLine(fin + i)) {
			while (*(fin + i++) != '\n');
			continue;
		}
		if (u = isUniversalCharacter(fin + i)) {
			char temp[10] = "D.";
			int len;

			_itoa_s(u, temp + 2, 10, 10);
			i += 2;
			len = strlen(temp);
			memcpy(g_inStream + o, temp, len);
			o += len;
			*(g_inStream + o++) = '.';
			continue;
		}
		*(g_inStream + o++) = *(fin + i++);
	}
	*(g_inStream + o) = 0;
	free(fin);

	// init the scanner and allocate memory for the data to write
	g_outStream = (char *)malloc(fLen * 2);

	// init the semaphore 
	g_semaphore = CreateSemaphore(NULL, 0, BUFSIZ, NULL);

	// Thread created
	la = (HANDLE)_beginthreadex(NULL, 0, separateToken, g_outStream, 0, NULL);
	pp = (HANDLE)_beginthreadex(NULL, 0, separatePreprocessingToken, g_inStream, 0, NULL);
	WaitForSingleObject(la, INFINITE);

	// drop the thread and semaphore
	CloseHandle(g_semaphore);
	CloseHandle(la);
	CloseHandle(pp);

	// write the result to disk
	fopen_s(&fOutput, out, "wb");
	fwrite(g_outStream, 1, strlen(g_outStream), fOutput);
	fclose(fOutput);

	for (struct _UniversalChar *p = g_pUC; p; p = p->next) {
		free(p);
	}
	g_pUC = NULL;
	free(g_inStream);
	free(g_outStream);
	system("pause");
	return 0;
}

int __stdcall separatePreprocessingToken(unsigned char* s) {
	int ppLen;
	int i = 0, o = 0;
	
	while (1)
	{
		if (ppLen = isComment(s + i)) {
 			i += ppLen;
			continue;
		}

		if (*(s + i) == '\r' || *(s + i) == '\n') {
			*(g_outStream + o++) = '\r';
			*(g_outStream + o++) = '\n';

			while (*(s + i++) != '\n');
			ReleaseSemaphore(g_semaphore, 1, NULL);
			continue;
		}
		
		if (*(s + i) == 0) {
			*(g_outStream + o) = 0;
			ReleaseSemaphore(g_semaphore, 1, NULL);
			break;
		}
		
		if (ppLen = isHeaderName(s + i)) {
			memcpy_s(g_outStream + o, ppLen, g_inStream + i, ppLen);
			o += ppLen;
			*(g_outStream + o++) = 0x20;

			i += ppLen;
			continue;
		}
			
		if (ppLen = isIdentifier(s + i)) {
			memcpy_s(g_outStream + o, ppLen, g_inStream + i, ppLen);
			o += ppLen;
			*(g_outStream + o++) = 0x20;

			i += ppLen;
			continue;
		}

		if (ppLen = isPpNumber(s + i)) {
			memcpy_s(g_outStream + o, ppLen, g_inStream + i, ppLen);
			o += ppLen;
			*(g_outStream + o++) = 0x20;

			i += ppLen;
			continue;
		}

		if (ppLen = isCharacterConstant(s + i)) {
			memcpy_s(g_outStream + o, ppLen, g_inStream + i, ppLen);
			o += ppLen;
			*(g_outStream + o++) = 0x20;

			i += ppLen;
			continue;
		}

		if (ppLen = isStringLiteral(s + i)) {
			memcpy_s(g_outStream + o, ppLen, g_inStream + i, ppLen);
			o += ppLen;
			*(g_outStream + o++) = 0x20;

			i += ppLen;
			continue;
		}

		if (ppLen = isPunctuator(s + i)) {
			memcpy_s(g_outStream + o, ppLen, g_inStream + i, ppLen);
			o += ppLen;
			*(g_outStream + o++) = 0x20;

			i += ppLen;
			continue;
		}
		memcpy_s(g_outStream + o, 1, g_inStream + i, 1);
		o += 1;
		*(g_outStream + o++) = 0x20;

		i += 1;
	}
	return 0;
}

int __stdcall separateToken(unsigned char* s) {
	int i = 0;

	while (1)
	{
		int col;

		WaitForSingleObject(g_semaphore, INFINITE);

		for (col = 0; *(short int *)(s + i + col) != '\r\n' && *(s + i + col); col++) {
			int colLen, isQuote , isDoubleQuote;
			char *token = (char *)malloc(BUFSIZ);

			colLen = isQuote = isDoubleQuote = 0;
			while (1){
				if (*(s + i + col + colLen) == 0x20) {
					if (!isQuote && !isDoubleQuote) break;
				}
				else if (*(s + i + col + colLen) == 39 && !isQuote) isQuote = 1;
				else if (*(s + i + col + colLen) == 39 && isQuote) isQuote = 0;
				else if (*(s + i + col + colLen) == 34 && !isDoubleQuote) isDoubleQuote = 1;
				else if (*(s + i + col + colLen) == 34 && isDoubleQuote) isDoubleQuote = 0;
				colLen++;
			}
			memcpy_s(token, colLen, s + i + col, colLen);
			if (isKeyword(token))
			{
				printf_s("(%d, ", TYPE_KEYWORD);
				for (int j = 0; j < colLen; j++)
					putchar(*(s + i + col + j));
				printf_s(")\n");
				col += colLen;
				continue;
			}
			if (isIdentifier(token)) 
			{
				printf_s("(%d, ", TYPE_IDENTIFIER);
				for (int j = 0; j < colLen; j++)
					putchar(*(s + i + col + j));
				printf_s(")\n");
				col += colLen;
				continue;
			}
			if (isConstant(token))
			{
				printf_s("(%d, ", TYPE_CONSTANT);
				for (int j = 0; j < colLen; j++)
					putchar(*(s + i + col + j));
				printf_s(")\n");
				col += colLen;
				continue;
			}
			if (isStringLiteral(token))
			{
				printf_s("(%d, ", TYPE_STRING_LITERAL);
				for (int j = 0; j < colLen; j++)
					putchar(*(s + i + col + j));
				printf_s(")\n");
				col += colLen;
				continue;
			}
			if (isPunctuator(token))
			{
				printf_s("(%d, ", TYPE_PUNCTUATOR);
				for (int j = 0; j < colLen; j++)
					putchar(*(s + i + col + j));
				printf_s(")\n");
				col += colLen;
				continue;
			}
			col += colLen;
		}

		if (*(s + i + col) == 0) break;
		else i += (col + 2);
	}
	return 0;
}
