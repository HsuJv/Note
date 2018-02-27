#include "HMIS.h"
#include "Manager.h"
#include "Room.h"
#include "Guest.h"
#include "Cashier.h"
#include "Bill.h"

extern BYTE g_authority;

int ManagerLogin() {
	char* pwd, realPwd[16];
	FILE* fAdmin;
	int i;
	
	pwd = getPassword();

	fopen_s(&fAdmin, File_Admin, "rb");
	fread_s(realPwd, 16, 16, 1, fAdmin);
	fclose(fAdmin);

	for (i = 0; i < 16; i++) {
		if (*(pwd + i) != *(realPwd + i)) {
			break;
		}
	}
	free(pwd);
	if (i == 16) {
		printf("%s\n", "Success!");
		g_authority = Group_Admin;
		return 1;
	}
	return 0;
}

inline int ManagerMenu() {
	char op = 0;

	printf("%s\n", "Welcome, dear manager.");
	printf("%s\n", "What would you like to do?");
	printf("%s\n%s\n%s\n%s\n%s\n%s\n", "1) Set/amend classes for each room and the price per class\
", "2) Guest information", "3) Cashier information", "4) Hotel business \
statistics", "5) Set a new password", "6) Logout");

	while (op < '1' || op > '6')
	{
		op = _getch();
	}
	system("cls");
	return op - 0x30;
}

inline int displayGuestInfoMenu() {
	char op = 0;

	printf("%s\n", "What would you like to do?");
	printf("%s\n%s\n%s\n%s\n%s\n", "1) Add a guest", "2) Edit guest information", \
		"3) Remove a guest", "4) List all guest", "5) Back");

	while (op < '1' || op > '5')
	{
		op = _getch();
	}
	system("cls");
	return op - 0x30;
}

inline int displayCashierInfoMenu() {
	char op = 0;

	printf("%s\n", "What would you like to do?");
	printf("%s\n%s\n%s\n%s\n", "1) Add a cashier", \
		"2) Remove a cashier", "3) List all cashier", "4) Back");

	while (op < '1' || op > '4')
	{
		op = _getch();
	}
	system("cls");
	return op - 0x30;
}

void setManagerPassword() {
	FILE *fAdmin;
	char pwd[16];

	setPassword(pwd);
	fopen_s(&fAdmin, File_Admin, "wb");
	fwrite(pwd, 16, 1, fAdmin);
	fclose(fAdmin);
}

void GuestInfoMenu() {
	while (1) {
		int menu = displayGuestInfoMenu();
		switch (menu)
		{
		case 1:
			printf("%s\n", "Please input the information of the guest to be added.");
			GuestAdd();
			break;
		case 2:
			printf("%s\n", "Please type the membership card id of the guest to be modified.");
			GuestEdit();
			break;
		case 3:
			printf("%s\n", "Please type the membership card id of the guest to be deleted.");
			GuestDel();
			break;
		case 4:
			GuestList();
			break;
		case 5:
			return;
		default:
			break;
		}
	}
}

void CashierInfoMenu() {
	while (1) {
		int menu = displayCashierInfoMenu ();
		switch (menu)
		{
		case 1:
			printf("%s\n", "Please input the information of the cashier to be added.");
			CashierAdd();
			break;
		case 2:
			printf("%s\n", "Please type the staff id of the cashier to be deleted.");
			CashierDel();
			break;
		case 3:
			CashierList();
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}

void ManagerMain() {
	while (1)
	{
		int menu = ManagerMenu();
		switch (menu)
		{
		case 1:
			printf("%s\n", "Please input the number of room to be amend.");
			setRoomInfo();
			getRoomInfoUpdated();
			break;
		case 2:
			GuestInfoMenu();
			break;
		case 3:
			CashierInfoMenu();
			break;
		case 4:
			BillOverview();
			break;
		case 5:
			setManagerPassword();
			break;
		case 6:
			g_authority = 0xff;
			return;
		default:
			break;
		}
	}
}