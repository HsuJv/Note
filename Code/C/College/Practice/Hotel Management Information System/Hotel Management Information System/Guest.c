#include "HMIS.h"
#include "Guest.h"
#include "Vigenere.h"
#include "Bill.h"
#include "Room.h"

extern BYTE g_authority;
extern struct _Room g_room[100];
extern struct _Bill g_bill;
struct _Guest g_guest;

void GuestAdd() {
	FILE* fGuest;
	struct _Guest guest;
	int num = 0;

	fopen_s(&fGuest, File_Guest, "ab+");
	while (fread_s(&guest, sizeof(struct _Guest), sizeof(struct _Guest), 1, fGuest))
	{
		if (guest.membership == 0) continue;
		getVigenereDecrypt((PBYTE)&guest, sizeof(struct _Guest));
		num = guest.membership;
	}

	memset(&guest, 0, sizeof(struct _Guest));
	printf("%s", "Name: ");
	scanf_s("%[^\r\n]", guest.name, 256);
	while (getchar() != '\n');
	printf("%s", "Address: ");
	scanf_s("%[^\r\n]", guest.address, 256);
	while (getchar() != '\n');
	printf("%s", "Tel: ");
	scanf_s("%[^\r\n]", guest.telephone, 16);
	while (getchar() != '\n');
	guest.membership = ++num;

	getVigenereEncrypt((PBYTE)&guest, sizeof(struct _Guest));
	fwrite(&guest, sizeof(struct _Guest), 1, fGuest);
	fclose(fGuest);
	system("cls");
}

void GuestEdit() {
	unsigned int id, num = 0;
	FILE *fGuest;
	
	if (_access(File_Guest, 0)) {
		printf("%s\n", "No Guests' information exists.");
		printf("Press any key to continue...");
		_getch();
		system("cls");
		return;
	}
	else
	{
		struct _Guest guest;

		scanf_s("%u", &id);
		while (getchar() != '\n');
		fopen_s(&fGuest, File_Guest, "rb+");
		while (fread_s(&guest, sizeof(struct _Guest), sizeof(struct _Guest), 1, fGuest))
		{
			if (guest.membership == 0) continue;
			getVigenereDecrypt((PBYTE)&guest, sizeof(struct _Guest));
			if (id == guest.membership) {
				num = guest.membership;

				system("cls");
				printf("Guest founded.\n");
				printf("%s%s\n", "Name: ", guest.name);
				printf("%s%s\n", "Address: ", guest.address);
				printf("%s%s\n", "Tel: ", guest.telephone);


				printf("\n\n\n%s\n", "You will input the updated information:");
				memset(&guest, 0, sizeof(struct _Guest));
				printf("%s", "Name: ");
				scanf_s("%[^\r\n]", guest.name, 256);
				while (getchar() != '\n');
				printf("%s", "Address: ");
				scanf_s("%[^\r\n]", guest.address, 256);
				while (getchar() != '\n');
				printf("%s", "Tel: ");
				scanf_s("%[^\r\n]", guest.telephone, 16);
				while (getchar() != '\n');
				guest.membership = num;
				break;
			}
		}

		if (!num) {
			printf("%s\n", "Guest doesn't exist.");
			fclose(fGuest);
			printf("Press any key to continue...");
			_getch();
		}
		else
		{
			fseek(fGuest, 0 - sizeof(struct _Guest), SEEK_CUR);
			getVigenereEncrypt((PBYTE)&guest, sizeof(struct _Guest));
			fwrite(&guest, sizeof(struct _Guest), 1, fGuest);
			fclose(fGuest);
		}
	}
	system("cls");
}

void GuestDel() {
	unsigned int id;
	int flag = 0;
	FILE *fGuest;

	if (_access(File_Guest, 0)) {
		printf("%s\n", "No Guests' information exists.");
		printf("Press any key to continue...");
		_getch();
		system("cls");
		return;
	}
	else
	{
		struct _Guest guest;

		printf("%s\n", "If type in the number 0, all the information will be deleted.");
		scanf_s("%u", &id);
		while (getchar() != '\n');

		if (!id) {
			fopen_s(&fGuest, File_Guest, "wb");
			fclose(fGuest);
		}
		else
		{
			fopen_s(&fGuest, File_Guest, "rb+");
			while (fread_s(&guest, sizeof(struct _Guest), sizeof(struct _Guest), 1, fGuest))
			{
				if (guest.membership == 0) continue;
				getVigenereDecrypt((PBYTE)&guest, sizeof(struct _Guest));
				if (id == guest.membership) {
					flag = 1;
					break;
				}
			}

			if (!flag) {
				printf("%s\n", "Guest doesn't exist.");
				fclose(fGuest);
				printf("Press any key to continue...");
				_getch();
			}
			else
			{
				fseek(fGuest, 0 - sizeof(struct _Guest), SEEK_CUR);
				guest.membership = 0;
				fwrite((PBYTE)&guest, 1, sizeof(struct _Guest), fGuest);
				fclose(fGuest);
			}
		}
	}
	system("cls");
}

void GuestList() {
	FILE *fGuest;

	if (_access(File_Guest, 0)) {
		printf("%s\n", "No Guests' information exists.");
		printf("Press any key to continue...");
		_getch();
		system("cls");
		return;
	}
	else
	{
		struct _Guest guest;

		fopen_s(&fGuest, File_Guest, "rb");
		system("cls");
		printf("Guest List:\n");
		while (fread_s(&guest, sizeof(struct _Guest), sizeof(struct _Guest), 1, fGuest))
		{
			if (guest.membership == 0) continue;
			getVigenereDecrypt((PBYTE)&guest, sizeof(struct _Guest));

			printf("%s%s\t\t\t", "Name: ", guest.name);
			printf("%s%u\n", "Membership Id: ", guest.membership);
		}
		fclose(fGuest);
	}
	printf("Press any key to continue...");
	_getch();
	system("cls");
}

int GuestLogin() {
	struct _Guest guest;
	FILE* fGuest;
	unsigned int id;
	char name[256];

	printf("Membership card id: ");
	scanf_s("%u", &id);
	while (getchar() != '\n');
	if (!id) {
		g_authority = 0xff;
		return 1;
	}

	printf("Name: ");
	scanf_s("%[^\r\n]", name, 256);
	while (getchar() != '\n');

	fopen_s(&fGuest, File_Guest, "rb");
	while (fread_s(&guest, sizeof(struct _Guest), sizeof(struct _Guest), 1, fGuest))
	{
		getVigenereDecrypt((PBYTE)&guest, sizeof(struct _Guest));
		if (guest.membership != id) continue;

		if (!strcmp(name, guest.name)) {
			printf("%s\n", "Success!");
			g_authority = Group_VIP_GUEST;
			fclose(fGuest);
			memcpy(&g_guest, &guest, sizeof(struct _Guest));
			return 1;
		}
	}

	fclose(fGuest);
	return 0;
}

inline int GuestMenu() {
	char op = 0;

	if (g_authority == Group_VIP_GUEST) {
		printf("%s%d.\n", "Welcom, VIP ", g_guest.membership);
	}
	else {
		printf("%s.\n", "Welcom, dear guest");
	}
	printf("%s\n", "What would you like to do?");
	printf("%s\n%s\n%s\n%s\n", "1) Register a booking\
", "2) Search free room.", "3) Group bookings(Only for VIPs)", "4) Logout");

	while (op < '1' || op > '4')
	{
		op = _getch();
	}
	system("cls");
	return op - 0x30;
}

inline int getRoomClass() {
	printf("%s\n%s\n%s\n%s\n", "(D)ouble Room", "(T)riple Room", "(Q)uadruple Room", "(V)IP Room");
	char op = 0;
	while (1)
	{
		switch (op) {
		case 'd':
		case 'D':
			system("cls");
			return Class_Double_Room;
		case 't':
		case 'T':
			system("cls");
			return Class_Triple_Room;
		case 'q':
		case 'Q':
			system("cls");
			return Class_Quadruple_Room;
		case 'v':
		case 'V':
			system("cls");
			return Class_VIP_Room;
		default:
			op = _getch();
			break;
		}
	}
}

int setBookDate(char* period) {
	printf("%s\n", "Input the book date in the form of 'startDD/MM-endDD/MM':");
	printf("%s\n", "e.g. 01/12-28/12");
	scanf_s("%[^\r\n]", period, 12);
	while (getchar() != '\n');
	if (strlen(period) != 11)
		return 0;
	if (validateDate(period) && validateDate(period + 6)) {
		if (*(period + 5) != '-')
			return 0;
		if (*(period + 2) != '/' && *(period + 8) != '/')
			return 0;
		return 1;
	}
	return 0;
}

void GuestBook() {
	if (g_authority == Group_VIP_GUEST) {
		g_bill.membership = g_guest.membership;
		strcpy_s(g_bill.name, 256, g_guest.name);
		strcpy_s(g_bill.tel, 16, g_guest.telephone);

		printf("%s\n", "Which type of room are you going to book?");
		g_bill.room_type = getRoomClass();

		g_bill.room = GuestSearch(0, g_bill.room_type);

		if (!g_bill.room) {
			printf("There is no vacant room left.\n");
			printf("Press any key to continue.");
			_getch();
			return;
		}

		while (!setBookDate(g_bill.period))
		{
			printf("%s\n", "Invalid date form");
		}

		if (BillComfirm()) {
			BillAdd();
			printf("%s", "Book success.\n");
			printf("%s%u%s\n", "Your bill number is ", g_bill.bill_num, ", please remember it.");
			printf("Press any key to continue.");
			_getch();
		}
	}
	else {
		g_bill.membership = 0;

		printf("%s", "Input your name: ");
		scanf_s("%[^\r\n]", g_guest.name, 256);
		while (getchar() != '\n');

		printf("%s", "Input your tel: ");
		scanf_s("%[^\r\n]", g_guest.telephone, 16);
		while (getchar() != '\n');

		printf("%s\n", "Which type of room are you going to book?");
		g_bill.room_type = getRoomClass();

		if (!g_bill.room) {
			printf("There is no vacant room left.\n");
			printf("Press any key to continue.");
			_getch();
			return;
		}

		while (!setBookDate(g_bill.period))
		{
			printf("%s\n", "Invalid date form");
		}

		g_bill.room = GuestSearch(0, g_bill.room_type);

		if (BillComfirm()) {
			BillAdd();
			printf("%s", "Book success.\n");
			printf("%s%u%s\n", "Your bill number is ", g_bill.bill_num, ", please remember it.");
			printf("Press any key to continue.");
			_getch();
		}
	}
	system("cls");
}

int GuestSearch(int hint, int rClass) {
	int rtn = 0;

	if (hint) {
		int rClass;
		printf("%s\n", "Which type of room are you going to search?");
		rClass = getRoomClass();
		printf("%s\n", "Now rooms that available are: ");

		for (int i = 0; i < 100; i++) {
			if (g_room[i].Class == rClass && !g_room[i].occupied) {
					printf("%d\t", getRoomNum(i));
				if (!rtn) {
					rtn = getRoomNum(i);
				}
			}
		}

		if (!rtn)
			printf("None\n");
		else
			printf("\n");
		printf("Press any key to continue...\n");
		_getch();
		system("cls");
	}
	else {
		for (int i = 0; i < 100; i++) {
			if (g_room[i].Class == rClass && !g_room[i].occupied) {
				if (!rtn) {
					rtn = getRoomNum(i);
					break;
				}
			}
		}
	}
	return rtn;
}

void VipBook() {
	int rClass, amount;

	printf("%s\n", "Which type of room are you going to book?");
	rClass = getRoomClass();

	printf("%s\n", "How many will you books?");
	scanf_s("%u", &amount);
	while (getchar() != '\n');

	if (amount > AvailableRoomCount(rClass)) {
		printf("There is no enough room left.\n");
		printf("Press any key to continue.");
		_getch();
		system("cls");
		return;
	}

	while (!setBookDate(g_bill.period))
	{
		printf("%s\n", "Invalid date form");
	}

	printf("Please Comfirm all this orders.\n");
	printf("Press any key to continue.");
	_getch();

	for (int i = 0; i < amount; i++) {
		g_bill.membership = g_guest.membership;
		strcpy_s(g_bill.name, 256, g_guest.name);
		strcpy_s(g_bill.tel, 16, g_guest.telephone);
		g_bill.room = GuestSearch(0, rClass);
		g_bill.room_type = rClass;
		if (BillComfirm()) {
			BillAdd();
			printf("%s", "Book success.\n");
			printf("%s%u%s\n", "Your bill number is ", g_bill.bill_num, ", please remember it.");
			printf("Press any key to continue.");
			_getch();
		}
	}

	system("cls");
	printf("Finished.\n");
	printf("Press any key to continue.");
	_getch();
	system("cls");
}

int AvailableRoomCount(int rClass) {
	int count = 0;

	for (int i = 0; i < 100; i++) {
		if (g_room[i].Class == rClass && !g_room[i].occupied) {
			count++;
		}
	}
	return count;
}

void GuestMain() {
	while (1)
	{
		int menu = GuestMenu();
		switch (menu)
		{
		case 1:
			GuestBook();
			break;
		case 2:
			GuestSearch(1, 0);
			break;
		case 3:
			if (g_authority != Group_VIP_GUEST) {
				printf("Sorry, for member only!!\n");
				printf("Press any key to continue...\n");
				_getch();
				system("cls");
				break;
			}
			else
			{
				VipBook();
				break;
			}
		case 4:
			g_authority = 0xff;
			return;
		default:
			break;
		}
	}
}