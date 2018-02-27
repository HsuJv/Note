#include "HMIS.h"
#include "Room.h"
#include "Vigenere.h"

struct _Room g_room[100];
extern char g_date[6];

inline int getRoomNum(int id) {
	return (id % 20 + 1) + (id / 20 + 1) * 100;
}

inline int getRoomOrder(int id) {
	return (id % 100 - 1) + (id / 100 - 1) * 20;
}

double getRoomPrice(unsigned int type, int days) {
	switch (type)
	{
	case Class_Double_Room:
		return Price_Double_Room * days;
	case Class_Triple_Room:
		return Price_Triple_Room * days;
	case Class_Quadruple_Room:
		return Price_Quadruple_Room * days;
	case Class_VIP_Room:
		return Price_VIP_Room * days;
	default:
		return 0;
	}
}

void RoomInit() {
	FILE* fRoom;
	int curMon, curDay;
	char szMonth[3], szDay[3];

	printf("%s\n", "Type in the date today (in the form of dd/mm):");
	scanf_s("%s", g_date, 6);
	while (getchar() != '\n');
	while (!validateDate(g_date))
	{
		printf("%s\n", "Invalid date form");
		printf("%s\n", "Please retype.");
		scanf_s("%s", g_date, 6);
		while (getchar() != '\n');
	}
	
	if (_access(File_Room, 0)) {
		memset(g_room, 0, sizeof(struct _Room) * 100);
		for (int i = 0; i < 100; i++)
		{
			g_room[i].Num = getRoomNum(i);
		}
		getVigenereEncrypt((PBYTE)g_room, sizeof(struct _Room) * 100);
		fopen_s(&fRoom, File_Room, "wb");
		fwrite(g_room, sizeof(struct _Room), 100, fRoom);
		fclose(fRoom);
	}
	else
	{
		fopen_s(&fRoom, File_Room, "rb");
		fread_s(g_room, sizeof(struct _Room) * 100, sizeof(struct _Room) * 100, 1, fRoom);
		fclose(fRoom);
	}
	getVigenereDecrypt((PBYTE)g_room, sizeof(struct _Room) * 100);
	
	for (int j = 0; j < 2; j++) {
		szMonth[j] = *(g_date + j + 3);
		szDay[j] = *(g_date + j);
	}
	curMon = atoi(szMonth);
	curDay = atoi(szDay);

	for (int i = 0; i < 100; i++) {
		if (g_room[i].occupied) {
			int month, day;

			for (int j = 0; j < 2; j++) {
				szMonth[j] = *(g_room[i].period + 6 + j + 3);
				szDay[j] = *(g_room[i].period + 6 + j);
			}
			month = atoi(szMonth);
			day = atoi(szDay);

			if (day + month * 32 < curDay + curMon * 32) {
				g_room[i].occupied = 0;
			}
		}
	}
	system("cls");
}

void setRoomInfo() {
	unsigned int id, rid;
	char op = 0;

	scanf_s("%u", &id);
	while (getchar() != '\n');

	if (id % 100 > 20 || id / 100 > 5 || !(id % 100) || !(id / 100)) {
		printf("Invalid number.\n");
		printf("Press any key to continue....");
		_getch();
		system("cls");
		return;
	}

	system("cls");
	rid = getRoomOrder(id);
	printf("%s%u%s\n", "The room ", id, " is: ");
	printf("%s", "Type: ");
	switch (g_room[rid].Class)
	{
	case Class_Double_Room:
		printf("%s\n", "Double Room.");
		break;
	case Class_Triple_Room:
		printf("%s\n", "Triple Room.");
		break;
	case Class_Quadruple_Room:
		printf("%s\n", "Quadruple Room.");
		break;
	case Class_VIP_Room:
		printf("%s\n", "Vip Room.");
	default:
		printf("%s\n", "Not set yet.");
		break;
	}
	printf("%s", "Is occupied: ");
	printf("%s\n", g_room[rid].occupied ? "Yes." : "No.");
	if (g_room[rid].occupied) {
		printf("%s", "Occupied period: ");
		printf("%s\n", g_room[rid].period);
	}

	printf("\n\n\n%s\n", "Which class you'd like to set it to: ");
	printf("%s\n%s\n%s\n%s\n", "(D)ouble Room", "(T)riple Room", "(Q)uadruple Room", "(V)IP Room");

	while (1)
	{
		switch (op) {
		case 'd':
		case 'D':
			g_room[rid].Class = Class_Double_Room;
			system("cls");
			return;
		case 't':
		case 'T':
			g_room[rid].Class = Class_Triple_Room;
			system("cls");
			return;
		case 'q':
		case 'Q':
			g_room[rid].Class = Class_Quadruple_Room;
			system("cls");
			return;
		case 'v':
		case 'V':
			g_room[rid].Class = Class_VIP_Room;
			system("cls");
			return;
		default:
			op = _getch();
			break;
		}
	}
}

void getRoomInfoUpdated() {
	FILE* fRoom;

	getVigenereEncrypt((PBYTE)g_room, sizeof(struct _Room) * 100);
	fopen_s(&fRoom, File_Room, "wb");
	fwrite(g_room, sizeof(struct _Room), 100, fRoom);
	fclose(fRoom);
	getVigenereDecrypt((PBYTE)g_room, sizeof(struct _Room) * 100);
}