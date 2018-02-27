#include "HMIS.h"
#include "Cashier.h"
#include "Vigenere.h"
#include "md5.h"
#include "Bill.h"

extern BYTE g_authority;
struct _Cashier g_cashier;

int CashierLogin() {
	char* pwd;
	struct _Cashier cashier;
	FILE* fCashier;
	int i;
	unsigned int id;

	printf("Stuff id: ");
	scanf_s("%u", &id);
	while (getchar() != '\n');

	pwd = getPassword();

	fopen_s(&fCashier, File_Cashier, "rb");
	while (fread_s(&cashier, sizeof(struct _Cashier), sizeof(struct _Cashier), 1, fCashier))
	{
		getVigenereDecrypt((PBYTE)&cashier, sizeof(struct _Cashier));
		if (cashier.id != id) continue;
		for (i = 0; i < 16; i++) {
			if (*(pwd + i) != *(cashier.pwd + i)) {
				break;
			}
		}
		if (i == 16) {
			printf("%s\n", "Success!");
			g_authority = Group_Cashier;
			free(pwd);
			fclose(fCashier);
			memcpy(&g_cashier, &cashier, sizeof(struct _Cashier));
			return 1;
		}
	}

	free(pwd);
	fclose(fCashier);
	return 0;
}

void CashierAdd() {
	FILE* fCashier;
	struct _Cashier cashier;
	int num = 0;
	unsigned char encrypt[] = "123456";
	MD5_CTX md5;

	fopen_s(&fCashier, File_Cashier, "ab+");
	while (fread_s(&cashier, sizeof(struct _Cashier), sizeof(struct _Cashier), 1, fCashier))
	{
		if (cashier.id == 0) continue;
		getVigenereDecrypt((PBYTE)&cashier, sizeof(struct _Cashier));
		num = cashier.id;
	}

	memset(&cashier, 0, sizeof(struct _Cashier));
	printf("%s", "Account: ");
	scanf_s("%[^\r\n]", cashier.account, 256);
	while (getchar() != '\n');
	cashier.id = ++num;

	MD5Init(&md5);
	MD5Update(&md5, encrypt, strlen((char *)encrypt));
	MD5Final(&md5, (unsigned char*)cashier.pwd);
	
	getVigenereEncrypt((PBYTE)cashier.pwd, 16);
	getVigenereEncrypt((PBYTE)&cashier, sizeof(struct _Cashier));
	fwrite(&cashier, sizeof(struct _Cashier), 1, fCashier);
	fclose(fCashier);

	printf("%s%d%s\n", "Cashier ", num, "'s account is initialized with the default password '123456'.");
	printf("%s\n", "Press any key to continue.");
	_getch();
	system("cls");
}

void CashierDel() {
	unsigned int id;
	int flag = 0;
	FILE *fCashier;

	if (_access(File_Cashier, 0)) {
		printf("%s\n", "No Cashiers' information exists.");
		printf("Press any key to continue...");
		_getch();
		system("cls");
		return;
	}
	else
	{
		struct _Cashier cashier;

		printf("%s\n", "If type in the number 0, all the information will be deleted.");
		scanf_s("%u", &id);
		while (getchar() != '\n');

		if (!id) {
			fopen_s(&fCashier, File_Cashier, "wb");
			fclose(fCashier);
		}
		else
		{
			fopen_s(&fCashier, File_Cashier, "rb+");
			while (fread_s(&cashier, sizeof(struct _Cashier), sizeof(struct _Cashier), 1, fCashier))
			{
				if (cashier.id == 0) continue;
				getVigenereDecrypt((PBYTE)&cashier, sizeof(struct _Cashier));
				if (id == cashier.id) {
					flag = 1;
					break;
				}
			}

			if (!flag) {
				printf("%s\n", "Cashier doesn't exist.");
				fclose(fCashier);
				printf("Press any key to continue...");
				_getch();
			}
			else
			{
				fseek(fCashier, 0 - sizeof(struct _Cashier), SEEK_CUR);
				cashier.id = 0;
				fwrite((PBYTE)&cashier, 1, sizeof(struct _Cashier), fCashier);
				fclose(fCashier);
			}
		}
	}
	system("cls");
}

void CashierList() {
	FILE *fCashier;

	if (_access(File_Cashier, 0)) {
		printf("%s\n", "No Cashiers' information exists.");
		printf("Press any key to continue...");
		_getch();
		system("cls");
		return;
	}
	else
	{
		struct _Cashier cashier;

		fopen_s(&fCashier, File_Cashier, "rb");
		system("cls");
		printf("Cashier List:\n");
		while (fread_s(&cashier, sizeof(struct _Cashier), sizeof(struct _Cashier), 1, fCashier))
		{
			if (cashier.id == 0) continue;
			getVigenereDecrypt((PBYTE)&cashier, sizeof(struct _Cashier));

			printf("%s%s\t\t\t", "Account: ", cashier.account);
			printf("%s%u\n", "Stuff Id: ", cashier.id);
		}
		fclose(fCashier);
	}
	printf("Press any key to continue...");
	_getch();
	system("cls");
}

inline int CashierMenu() {
	printf("%s%d.\n", "Welcom, stuff ", g_cashier.id);
	printf("%s\n", "What would you like to do?");
	printf("%s\n%s\n%s\n%s\n", "1) Change booking period", "2) Check out", "3) Set a new password", "4) Logout");

	char op = 0;
	while (op < '1' || op > '5')
	{
		op = _getch();
	}
	system("cls");
	return op - 0x30;
}

void setCashierPassword() {
	FILE *fCashier;
	char pwd[16];
	struct _Cashier cashier;

	setPassword(pwd);
	fopen_s(&fCashier, File_Cashier, "rb+");
	while (fread_s(&cashier, sizeof(struct _Cashier), sizeof(struct _Cashier), 1, fCashier))
	{
		getVigenereDecrypt((PBYTE)&cashier, sizeof(struct _Cashier));
		if (cashier.id == g_cashier.id) break;
	}

	memcpy(cashier.pwd, pwd, 16);
	getVigenereEncrypt((PBYTE)&cashier, sizeof(struct _Cashier));

	fseek(fCashier, 0 - sizeof(struct _Cashier), SEEK_CUR);
	fwrite(&cashier, sizeof(struct _Cashier), 1, fCashier);
	fclose(fCashier);
}

void CashierMain() {
	while (1)
	{
		int menu = CashierMenu();
		switch (menu)
		{
		case 1:
			getPeriodChange();
			break;
		case 2:
			getBillCheckout();
			break;
		case 3:
			setCashierPassword();
			break;
		case 4:
			g_authority = 0xff;
			return;
		default:
			break;
		}
	}
}