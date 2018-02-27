#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

// Account Information file
#define _AccInfoFile "Assignment3"

// User information
struct _UserInfo {
	char Account[255], Pwd[255];
	int wins, losses;
}g_ui;

// Function declaration
int SignUp(const char *, const char *);
int SignIn(const char *, const char *);
int gameOrNot();
void boardDisplay();
void resultDisplay();
int gaming(int);
int termination();
int Where2Place(int);

// Global variable declaration
union _chessBoard {
	int l[9]; // line
	int g[3][3]; // graph
}g_chessBoard;



int main(int argc, char const *argv[]) {
	int foc = 0; // to go first or second
	int winner = 0;
	char op[2] = { 0 };
	char Account[255] = { 0 }, Pwd[255] = { 0 };

	// Sign in or up
	printf("%s\n", "Please sign in with your account or create a new one.");
	printf("%s\n%s\n", "(1)Sign In", "(2)Sign Up");
	while (_stricmp(op, "1") && _stricmp(op, "2"))
		op[0] = _getch();
	if (!_stricmp(op, "1")) {
		do {
			int i = 0;

			printf("Account: ");
			scanf_s("%[^\r\n]", Account, 255);
			printf("\nPassword: ");
			while ((Pwd[i++] = _getch()) != '\r') {
				putchar('*');
			}
			Pwd[i - 1] = 0;
			printf("\n");
			while (getchar() != '\n');
		} while (!SignIn(Account, Pwd));
	}
	else {
		do {
			int i = 0;

			printf("Account: ");
			scanf_s("%[^\r\n]", Account, 255);
			printf("\nPassword: ");
			while ((Pwd[i++] = _getch()) != '\r') {
				putchar('*');
			}
			Pwd[i - 1] = 0;
			printf("\n");
			while (getchar() != '\n');
		} while (!SignUp(Account, Pwd));
	}

	// Success Log in
	printf("Welcome %s\n", g_ui.Account);
	printf("%s: %d wins, %d losses\n", "Record", g_ui.wins, g_ui.losses);


	// game start
	printf("%s\n", "Start a new game?(Y/N): ");
	if (!gameOrNot()) return 0;

	// gaming
	while (1) {
		system("cls");

		// Ask go first or not
		printf("Would you like to go first(1) or second(any other)?\n");
		op[0] = _getch();
		foc = (strcmp(op, "1")) ? 2 : 1;

		// gaming
		winner = gaming(foc);

		// Display the result
		resultDisplay();

		// Draw;
		if (!winner) {
			printf("%s\n", "The game was a draw");
		}
		else {
			if (winner == foc) {
				printf("Congratulations! You won.\n");
				g_ui.wins++;
			}
			else {
				printf("Oops, you lost\n");
				g_ui.losses++;
			}
		}

		// Record
		printf("%s: %d wins, %d losses\n", "Now you are", g_ui.wins, g_ui.losses);

		// Ask for another
		printf("\n\n%s\n", "Would you like to play again?(Y/N): ");
		if (!gameOrNot()) {
			// Update record
			FILE* AccInfo;
			struct _UserInfo ui;
			memset(&ui, 0, sizeof(ui));

			fopen_s(&AccInfo, _AccInfoFile, "rb+");
			while (fread_s(&ui, sizeof(struct _UserInfo), sizeof(struct _UserInfo), 1, AccInfo)) {
				if (!strcmp(ui.Account, Account)) {
					fseek(AccInfo, 0-sizeof(struct _UserInfo), SEEK_CUR);
					fwrite(&g_ui, sizeof(struct _UserInfo), 1, AccInfo);
					fclose(AccInfo);
					return 0;
				}
				memset(&ui, 0, sizeof(ui));
			}
		}
	}
}

int SignUp(const char * Account, const char * Pwd) {
	FILE* AccInfo = NULL; // Account Info
	struct _UserInfo ui;
	memset(&ui, 0, sizeof(ui));

	// Account is null
	if (!strlen(Account)) {
		printf("The length of account cann't be 0.\n");
		return 0;
	}

	// Open or create
	fopen_s(&AccInfo, _AccInfoFile, "ab+");

	// Duplicate checking
	while (fread_s(&ui, sizeof(struct _UserInfo), sizeof(struct _UserInfo), 1, AccInfo)) {
		if (!strcmp(ui.Account, Account)) {
			char op[2] = { 0 };

			// Account exists
			fclose(AccInfo);
			printf("Account exists!\n");
			printf("Would you like to create another(C) or just exit(Q)?\n");
			while (_stricmp(op, "c") && _stricmp(op, "q"))
				op[0] = _getch();
			if (!_stricmp(op, "c")) {
				system("cls");
				return 0;
			}
			else
				exit(0);
		}
		memset(&ui, 0, sizeof(ui));
	}

	// Account new
	strcpy_s(g_ui.Account, strlen(Account) + 1, Account);
	strcpy_s(g_ui.Pwd, strlen(Pwd) + 1, Pwd);
	g_ui.wins = 0; g_ui.losses = 0;
	fwrite(&g_ui, sizeof(struct _UserInfo), 1, AccInfo);
	fclose(AccInfo);
	return 1;
}

int SignIn(const char * Account, const char * Pwd) {
	FILE* AccInfo = NULL; // Account Info
	struct _UserInfo ui;
	memset(&ui, 0, sizeof(ui));
	char op[2] = { 0 };

	// Account is null
	if (!strlen(Account)) {
		printf("The length of account cann't be 0.\n");
		return 0;
	}

	if (!fopen_s(&AccInfo, _AccInfoFile, "rb")) {
		while (fread_s(&ui, sizeof(struct _UserInfo), sizeof(struct _UserInfo), 1, AccInfo)) {
			if (!strcmp(ui.Account, Account))
				if (!strcmp(ui.Pwd, Pwd)) {
					// Log in successfully
					fclose(AccInfo);
					g_ui.wins = ui.wins;
					g_ui.losses = ui.losses;
					strcpy_s(g_ui.Account, sizeof(ui.Account) + 1, ui.Account);
					strcpy_s(g_ui.Pwd, sizeof(ui.Pwd) + 1, ui.Pwd);
					return 1;
				}
				else {
					printf("Wrong Password, please check again.\n");
					return 0;
				}
				memset(&ui, 0, sizeof(ui));
		}

		// Account not exists
		fclose(AccInfo);
		printf("Account not exists, would you like to create a new one(C) or just exit(Q)?\n");
		while (_stricmp(op, "c") && _stricmp(op, "q"))
			op[0] = _getch();
		if (!_stricmp(op, "c")) {
			// Create a new account information file
			SignUp(Account, Pwd);
		}
		else
			exit(0);
	}
	else {
		// Failed to open file
		printf("There aren't any accounts, please create a new one first(C) or just exit(Q)?\n");
		while (_stricmp(op, "c") && _stricmp(op, "q"))
			op[0] = _getch();
		if (!_stricmp(op, "c")) {
			// Create a new account information file
			SignUp(Account, Pwd);
		}
		else
			exit(0);
	}

	return 1;
}

int gameOrNot() {
	char op[2] = { 0 };

	op[0] = _getch();
	while (_stricmp(op, "Y") & _stricmp(op, "N"))
		op[0] = _getch();
	if (!_stricmp(op, "N"))
		return 0;
	else {
		// initial the chessboard
		for (int i = 0; i < 9; i++)
			g_chessBoard.l[i] = 0x20;
	}
	return 1;
}

void boardDisplay() {
	// print guide
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (j % 2)
				printf("%s%d%s%d%s%d\n", "  ", i * 3 + 1, "  #  ", i * 3 + 2, "  #  ", i * 3 + 3);
			else
				printf("%s\n", "     #     #");
		}
		if (i == 2) break;
		printf("%s\n", "#################");
	}
}

void resultDisplay() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (j % 2)
				printf("%s%c%s%c%s%c\n", "  ", g_chessBoard.g[i][0], "  #  ", g_chessBoard.g[i][1], "  #  ", g_chessBoard.g[i][2]);
			else
				printf("%s\n", "     #     #");
		}
		if (i == 2) break;
		printf("%s\n", "#################");
	}
}

int gaming(int foc) {
	int winner = 0;

	// put chess one by one
	for (int i = 0; i < 9; i++) {
		char op;

		if (i % 2 == foc - 1) {
			// User's time

			// Display what the board looks like now
			boardDisplay();
			printf("\n");
			printf("%s\n", "Now: ");
			resultDisplay();
			printf("\n");

			// Ask player to put chess
			printf("%s\n", "Time for you ");

			// Get the operation
			while (!isdigit(op = _getch()));
			op -= 0x31;

			// Judge whether this chess can be placed
			while (g_chessBoard.l[op] != 0x20) {
				printf("%s\n", "There is already a chessman here!");
				printf("%s\n", "Choose another place.");
				resultDisplay();
				printf("\n");
				while (!isdigit(op = _getch()));
				op -= 0x31;
			}
		}
		else {
			// Computer's time
			
			// for test
			/*
			op = 0;
			while (g_chessBoard.l[op++] != 0x20);
			op--;
			*/

			// find the best place
			op = Where2Place(i % 2);
		}

		// Change the board
		if (i % 2)
			g_chessBoard.l[op] = 79; // 'O';
		else
			g_chessBoard.l[op] = 88; // 'X';

		system("cls");

		// Judge who've won
		if (winner = termination()) {
			break;
		}
	}

	return winner;
}

int termination() {
	// horizontal test
	for (int i = 0; i < 3; i++) {
		if (g_chessBoard.g[i][0] != 0x20 && g_chessBoard.g[i][0] == g_chessBoard.g[i][1] && g_chessBoard.g[i][0] == g_chessBoard.g[i][2])
			return (g_chessBoard.g[i][0] % 2 + 1);
	}

	// vertical test
	for (int i = 0; i < 3; i++) {
		if (g_chessBoard.g[0][i] != 0x20 && g_chessBoard.g[0][i] == g_chessBoard.g[1][i] && g_chessBoard.g[0][i] == g_chessBoard.g[2][i])
			return (g_chessBoard.g[0][i] % 2 + 1);
	}

	// diagonal test
	if (g_chessBoard.g[0][0] != 0x20 && g_chessBoard.g[0][0] == g_chessBoard.g[1][1] && g_chessBoard.g[0][0] == g_chessBoard.g[2][2])
		return (g_chessBoard.g[1][1] % 2 + 1);
	if (g_chessBoard.g[0][2] != 0x20 && g_chessBoard.g[0][2] == g_chessBoard.g[1][1] && g_chessBoard.g[0][2] == g_chessBoard.g[2][0])
		return (g_chessBoard.g[1][1] % 2 + 1);

	// haven't terminated yet
	return 0;
}

int Where2Place(int op) {
	int count;
	int blank;

	// occupy the center
	if (g_chessBoard.g[1][1] == 0x20)
		return 4;

	// 2 computer's chess in a line
	for (int i = 0; i < 3; i++) {
		// horizontal
		count = 0; blank = 9;
		for (int j = 0; j < 3; j++) {
			if (g_chessBoard.g[i][j] != 0x20 && g_chessBoard.g[i][j] % 2 == op) count++;
			else if (g_chessBoard.g[i][j] == 0x20) blank = i * 3 + j;
		}
		if (count == 2 && blank != 9) return blank;
		// vertical
		count = 0; blank = 9;
		for (int j = 0; j < 3; j++) {
			if (g_chessBoard.g[j][i] != 0x20 && g_chessBoard.g[j][i] % 2 == op) count++;
			else if (g_chessBoard.g[j][i] == 0x20) blank = j * 3 + i;
		}
		if (count == 2 && blank != 9) return blank;
	}
	// diagonal
	count = 0; blank = 9;
	for (int i = 0; i < 3; i++) {
		if (g_chessBoard.g[i][i] != 0x20 && g_chessBoard.g[i][i] % 2 == op) count++;
		else if (g_chessBoard.g[i][i] == 0x20) blank = i * 4;
	}
	if (count == 2 && blank != 9) return blank;
	count = 0; blank = 9;
	for (int i = 0; i < 3; i++) {
		if (g_chessBoard.g[i][2 - i] != 0x20 && g_chessBoard.g[i][2 - i] % 2 == op) count++;
		else if (g_chessBoard.g[i][2-i] == 0x20) blank = i * 2 + 2;
	}
	if (count == 2 && blank != 9) return blank;

	// 2 user's chess in a line
	for (int i = 0; i < 3; i++) {
		// horizontal
		count = 0; blank = 9;
		for (int j = 0; j < 3; j++) {
			if (g_chessBoard.g[i][j] != 0x20 && g_chessBoard.g[i][j] % 2 != op) count++;
			else if (g_chessBoard.g[i][j] == 0x20) blank = i * 3 + j;
		}
		if (count == 2 && blank != 9) return blank;
		// vertical
		count = 0; blank = 9;
		for (int j = 0; j < 3; j++) {
			if (g_chessBoard.g[j][i] != 0x20 && g_chessBoard.g[j][i] % 2 != op) count++;
			else if (g_chessBoard.g[j][i] == 0x20) blank = j * 3 + i;
		}
		if (count == 2 && blank != 9) return blank;
	}
	// diagonal
	count = 0; blank = 9;
	for (int i = 0; i < 3; i++) {
		if (g_chessBoard.g[i][i] != 0x20 && g_chessBoard.g[i][i] % 2 != op) count++;
		else if (g_chessBoard.g[i][i] == 0x20) blank = i * 4;
	}
	if (count == 2 && blank != 9) return blank;
	count = 0; blank = 9;
	for (int i = 0; i < 3; i++) {
		if (g_chessBoard.g[i][2 - i] != 0x20 && g_chessBoard.g[i][2 - i] % 2 != op) count++;
		else if (g_chessBoard.g[i][2 - i] == 0x20) blank = i * 2 + 2;
	}
	if (count == 2 && blank != 9) return blank;

	// occupy corners
	if (g_chessBoard.g[0][0] == 0x20 && g_chessBoard.g[2][2] == 0x20) return 0;
	if (g_chessBoard.g[0][2] == 0x20 && g_chessBoard.g[2][0] == 0x20) return 2;

	// 1 computer's chess in a line
	for (int i = 0; i < 3; i++) {
		// horizontal
		count = 0; blank = 9;
		for (int j = 0; j < 3; j++) {
			if (g_chessBoard.g[i][j] != 0x20 && g_chessBoard.g[i][j] % 2 == op) count++;
			else if (g_chessBoard.g[i][j] == 0x20) blank = i * 3 + j;
		}
		if (count == 1 && blank != 9) return blank;
		// vertical
		count = 0; blank = 9;
		for (int j = 0; j < 3; j++) {
			if (g_chessBoard.g[j][i] != 0x20 && g_chessBoard.g[j][i] % 2 == op) count++;
			else if (g_chessBoard.g[j][i] == 0x20) blank = j * 3 + i;
		}
		if (count == 1 && blank != 9) return blank;
	}
	// diagonal
	count = 0; blank = 9;
	for (int i = 0; i < 3; i++) {
		if (g_chessBoard.g[i][i] != 0x20 && g_chessBoard.g[i][i] % 2 == op) count++;
		else if (g_chessBoard.g[i][i] == 0x20) blank = i * 4;
	}
	if (count == 1 && blank != 9) return blank;
	count = 0; blank = 9;
	for (int i = 0; i < 3; i++) {
		if (g_chessBoard.g[i][2 - i] != 0x20 && g_chessBoard.g[i][2 - i] % 2 == op) count++;
		else if (g_chessBoard.g[i][2 - i] == 0x20) blank = i * 2 + 2;
	}
	if (count == 1 && blank != 9) return blank;
}