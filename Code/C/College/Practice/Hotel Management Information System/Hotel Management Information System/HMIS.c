#include "HMIS.h"
#include "Vigenere.h"
#include "md5.h"
#include "Manager.h"
#include "Guest.h"
#include "Cashier.h"
#include "Room.h"
#include "Bill.h"

BYTE g_authority = 0xff;
char g_date[6];

void _init_() {
	if (_access(File_Admin, 0)) {
		FILE* f;
		unsigned char encrypt[] = "admin";
		unsigned char pwd[16];
		MD5_CTX md5;

		MD5Init(&md5);
		MD5Update(&md5, encrypt, strlen((char *)encrypt));
		MD5Final(&md5, pwd);

		getVigenereEncrypt(pwd, 16);

		fopen_s(&f, File_Admin, "wb");
		fwrite(pwd, 16, 1, f);
		fclose(f);
	}

	RoomInit();
}

int _menu_() {
	printf("%s\n", "Thank you for using this production.");
	printf("%s\n", "In which role will you login:");
	printf("%s\n%s\n%s\n%s\n", "1) Manager", "2) Cashier", "3) Guest", "4) Exit");
	
	char op = 0;
	while (op < '1' || op > '4')
	{
		op = _getch();
	}
	system("cls");
	return op - 0x30;
}

char* getPassword() {
	MD5_CTX md5;

	printf("%s", "Password: ");

	char ch, pwd[256], *rtn;
	int i = 0;

	memset(pwd, 0, 256);
	while ((ch = _getch()) != '\r')
	{
		if (ch == '\b') {
			if (i) {
				*(pwd + --i) = 0;
			}
		}
		else if (ch >= 0x20 && ch <= 0x7e)
		{
			*(pwd + i++) = ch;
		}
	}

	rtn = (char *)malloc(16);

	MD5Init(&md5);
	MD5Update(&md5, pwd, strlen(pwd));
	MD5Final(&md5, rtn);

	getVigenereEncrypt(rtn, 16);
	printf("\n");
	return rtn;
}

char* setPassword(char* raw) {
	char ch, pwd[256];
	int i = 0;
	MD5_CTX md5;

	printf("%s", "New password: ");

	memset(pwd, 0, 256);
	while ((ch = _getch()) != '\r')
	{
		if (ch == '\b') {
			if (i) {
				*(pwd + --i) = 0;
			}
		}
		else if (ch >= 0x20 && ch <= 0x7e)
		{
			*(pwd + i++) = ch;
		}
	}

	MD5Init(&md5);
	MD5Update(&md5, pwd, strlen(pwd));
	MD5Final(&md5, raw);

	getVigenereEncrypt(raw, 16);
	printf("\n");
	return raw;
}

int validateDate(char* dm) {
	int month, day;
	char szMonth[3], szDay[3];

	for (int i = 0; i < 2; i++) {
		szMonth[i] = *(dm + i + 3);
		szDay[i] = *(dm + i);
	}
	month = atoi(szMonth);
	day = atoi(szDay);
	if (day && month) {
		switch (month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (day > 31) return 0;
			return 1;
		case 2:
			if (day > 28) return 0;
			return 1;
		case 4:
		case 6:
		case 9:
		case 11:
			if (day > 30) return 0;
			return 1;
		default:
			return 0;
		}
	}
	return 0;
}

int countDays(char* dm) {
	int month, day;
	char szMonth[3], szDay[3];

	for (int i = 0; i < 2; i++) {
		szMonth[i] = *(dm + i + 3);
		szDay[i] = *(dm + i);
	}
	month = atoi(szMonth);
	day = atoi(szDay);

	switch (month)
	{
	case 1:
		return day;
	case 2:
		return 31 + day;
	case 3:
		return 59 + day;
	case 4:
		return 90 + day;
	case 5:
		return 120 + day;
	case 6:
		return 151 + day;
	case 7:
		return 181 + day;
	case 8:
		return 212 + day;
	case 9:
		return 243 + day;
	case 10:
		return 273 + day;
	case 11:
		return 303 + day;
	case 12:
		return 334 + day;
	default:
		return 0;
	}
}

int main(int arg, char** argv) {
	_init_();

	while (1)
	{
		int menu = _menu_();
		switch (menu)
		{
		case 1:
			while (!ManagerLogin())
			{
				char op[2] = { 0 };

				printf("%s\n", "Wrong password.");
				printf("%s\n", "Again(A) or Back to menu(B)?");

				while (_stricmp(op, "b") && _stricmp(op, "a"))
				{
					op[0] = _getch();
				}
				if (_stricmp(op, "a")) {
					goto next;
				}
			}
			ManagerMain();
			break;
		case 2:
			if (_access(File_Cashier, 0)) {
				system("cls");
				printf("No cashier exists.\n");
				printf("Please connect the administrator to add one first.\n");
				printf("Press any key to continue...");
				_getch();
				goto next;
			}
			while (!CashierLogin())
			{
				char op[2] = { 0 };
			
				printf("%s\n", "Wrong password.");
				printf("%s\n", "Again(A) or Back to menu(B)?");

				while (_stricmp(op, "b") && _stricmp(op, "a"))
				{
					op[0] = _getch();
				}
				if (_stricmp(op, "a")) {
					goto next;
				}
			}
			CashierMain();
			break;
		case 3:
			printf("%s", "If you are not a VIP, just type 0 for membership card id.\n");
			while (!GuestLogin())
			{
				char op[2] = { 0 };
			
				printf("%s\n", "Membership card id is not related to your name.");
				printf("%s\n", "Again(A) or Back to menu(B)?");

				while (_stricmp(op, "b") && _stricmp(op, "a"))
				{
					op[0] = _getch();
				}
				if (_stricmp(op, "a")) {
					goto next;
				}
			}
			GuestMain();
			break;
		case 4:
			return 0;
		default:
			break;
		}
	next:
		;
	}
}