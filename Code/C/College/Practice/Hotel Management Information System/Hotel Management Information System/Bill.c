#include "HMIS.h"
#include "Vigenere.h"
#include "Manager.h"
#include "Guest.h"
#include "Cashier.h"
#include "Room.h"
#include "Bill.h"

struct _Bill g_bill;
extern struct _Room g_room[100];
extern char g_date[6];
extern struct _Cashier g_cashier;
extern int g_authority;

int BillComfirm() {
	int days;
	char op;

	system("cls");
	printf("Name: %s\n", g_bill.name);
	printf("Membership Id: ");
	if (!g_bill.membership) {
		printf("Not a VIP\n");
	}
	else {
		printf("%u\n", g_bill.membership);
	}
	printf("Tel: %s\n", g_bill.tel);
	printf("Ordered room: %u\n", g_bill.room);
	printf("Ordered room type: ");
	switch (g_bill.room_type)
	{
	case Class_Double_Room:
		printf("%s\n", "Double Room");
		break;
	case Class_Triple_Room:
		printf("%s\n", "Triple Room");
		break;
	case Class_Quadruple_Room:
		printf("%s\n", "Quadruple Room");
		break;
	case Class_VIP_Room:
		printf("%s\n", "VIP Room");
		break;
	default:
		break;
	}
	printf("Ordered period: %s\n", g_bill.period);

	days = countDays(g_bill.period + 6) - countDays(g_bill.period);
	g_bill.account = getRoomPrice(g_bill.room_type, days);
	printf("Raw Price: %.2lf\n", g_bill.account);

	printf("\n\nConfirmed?(Y/N)");
	op = 0;
	while (1)
	{
		switch (op) {
		case 'n':
		case 'N':
			system("cls");
			return 0;
		case 'y':
		case 'Y':
			system("cls");
			return 1;
		default:
			op = _getch();
			break;
		}
	}
}

void BillAdd() {
	FILE* fBill;
	struct _Bill bill;
	int num = 0;

	fopen_s(&fBill, File_Bill, "ab+");
	while (fread_s(&bill, sizeof(struct _Bill), sizeof(struct _Bill), 1, fBill))
	{
		if (bill.bill_num == 0) continue;
		getVigenereDecrypt((PBYTE)&bill, sizeof(struct _Bill));
		num = bill.bill_num;
	}

	g_bill.bill_num = ++num;

	getVigenereEncrypt((PBYTE)&g_bill, sizeof(struct _Bill));
	fwrite(&g_bill, sizeof(struct _Bill), 1, fBill);
	fclose(fBill);
	getVigenereDecrypt((PBYTE)&g_bill, sizeof(struct _Bill));

	g_room[getRoomOrder(g_bill.room)].occupied = 1;
	strcpy_s(g_room[getRoomOrder(g_bill.room)].period, 12, g_bill.period);
	getRoomInfoUpdated();
}

void getPeriodChange() {
	unsigned int id;
	FILE* fBill;
	struct _Bill bill;

	system("cls");
	if (_access(File_Bill, 0)) {
		printf("%s\n", "No bill exists.");
		printf("%s\n", "Press any key to continue....");
		_getch();
		system("cls");
		return;
	}
	printf("%s\n", "Please type in the bill number.");
	scanf_s("%u", &id);
	while (getchar() != '\n');

	fopen_s(&fBill, File_Bill, "rb+");
	while (fread_s(&bill, sizeof(struct _Bill), sizeof(struct _Bill), 1, fBill))
	{
		getVigenereDecrypt((PBYTE)&bill, sizeof(struct _Bill));
		if (bill.bill_num == id) {
			if (!g_room[getRoomOrder(bill.room)].occupied) {
				printf("%s\n", "This bill is overdue.");
				printf("%s\n", "Press any key to continue....");
				_getch();
				system("cls");
				fclose(fBill);
				return;
			}
			else
			{
				memcpy(&g_bill, &bill, sizeof(struct _Bill));
				if (BillComfirm()) {
					char period[12];
					while (!setBookDate(period)) {
						printf("%s\n", "Invalid date form");
					}
					memcpy(g_bill.period, period, 12);

					int days = countDays(g_bill.period + 6) - countDays(g_bill.period);
					g_bill.account = getRoomPrice(g_bill.room_type, days);
					getVigenereEncrypt((PBYTE)&g_bill, sizeof(struct _Bill));
					fseek(fBill, 0 - sizeof(struct _Bill), SEEK_CUR);
					fwrite(&g_bill, sizeof(struct _Bill), sizeof(struct _Bill), fBill);
					break;
				}
			}
		}
	}
	fclose(fBill);
	system("cls");
}

void getBillCheckout() {
	unsigned int id;
	FILE* fBill;
	struct _Bill bill;

	system("cls");
	if (_access(File_Bill, 0)) {
		printf("%s\n", "No bill exists.");
		printf("%s\n", "Press any key to continue....");
		_getch();
		system("cls");
		return;
	}
	printf("%s\n", "Please type in the bill number.");
	scanf_s("%u", &id);
	while (getchar() != '\n');

	fopen_s(&fBill, File_Bill, "rb+");
	while (fread_s(&bill, sizeof(struct _Bill), sizeof(struct _Bill), 1, fBill))
	{
		getVigenereDecrypt((PBYTE)&bill, sizeof(struct _Bill));
		if (bill.bill_num == id) {
			if (!g_room[getRoomOrder(bill.room)].occupied) {
				printf("%s\n", "This bill is overdue.");
				printf("%s\n", "Press any key to continue....");
				_getch();
				system("cls");
				fclose(fBill);
				return;
			}
			else
			{
				char op = 0;
				double off = 0;

				memcpy(&g_bill, &bill, sizeof(struct _Bill));
				memcpy(&g_bill.date, g_date, 6);
				g_bill.stuff = g_cashier.id;

				printf("%s%u\n", "Order ", g_bill.bill_num);
				printf("%.2lf%s\n", g_bill.account, " payable without a discount.");
				printf("Would you like to set a discount? (Y/N) (admin authority needed)\n");

				while (1)
				{
					if (off > 0.00001)
						break;
					switch (op) {
					case 'n':
					case 'N':
						off = 1;
						break;
					case 'y':
					case 'Y':
						if (g_authority != Group_Admin) {
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
									break;
								}
							}
						}
						if (g_authority == Group_Admin) {
							printf("How much off?(0-1)\n");
							scanf_s("%lf", &off);
							while (off < 0 || off > 1) {
								printf("Invalid date\nPlease retype: ");
								scanf_s("%lf", &off);
							}
							system("cls");
						}
						else
						{
							off = 1;
							system("cls");
						}
						break;
					default:
						op = _getch();
						break;
					}
				}
				g_bill.paid = g_bill.account * (1 - off);
				printf("%s%.2lf\n", "The guest should pay ", g_bill.paid);
				printf("%s\n", "Press any key to continue....");
				_getch();
				getVigenereEncrypt((PBYTE)&g_bill, sizeof(struct _Bill));
				fseek(fBill, 0 - sizeof(struct _Bill), SEEK_CUR);
				fwrite(&g_bill, sizeof(struct _Bill), 1, fBill);
				break;
			}
		}
	}
	fclose(fBill);
	system("cls");
}

void BillOverview(){
	FILE* fBill;

	system("cls");
	if (_access(File_Bill, 0)) {
		printf("%s\n", "No bill exists.");
		printf("%s\n", "Press any key to continue....");
		_getch();
		system("cls");
		return;
	}
	else
	{
		struct _Bill bill;
		double income = 0;

		fopen_s(&fBill, File_Bill, "rb");
		while (fread_s(&bill, sizeof(struct _Bill), sizeof(struct _Bill), 1, fBill)) {
			getVigenereDecrypt((PBYTE)&bill, sizeof(struct _Bill));
			income += bill.paid;
		}

		printf("%s%.2lf\n", "Income: ", income);
		printf("%s\n", "Press any key to continue....");
		_getch();
		system("cls");
	}
}