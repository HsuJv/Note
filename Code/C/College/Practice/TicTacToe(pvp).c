// test.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Function declaration
int gameOrNot();
void boardDisplay();
void resultDisplay();
int gaming();
int termination();

// Global variable declaration
union _chessBoard{
    int l[9]; // line
    int g[3][3]; // graph
}chessBoard;

int main(int argc, char const *argv[]){
    int winner = 0;
    char player[2][255];

    // game start
    printf("%s\n", "Start a new game?(Y/N): ");
    if (!gameOrNot()) return 0;

    // gaming
    while(1) {
        printf("%s\n", "Input the name of Player 1: ");
        scanf("%[^\n]", player[0]);
        while(getchar() != '\n');
        printf("%s\n", "Input the name of Player 2: ");
        scanf("%[^\n]", player[1]);
        while(getchar() != '\n');
        
        winner = gaming();

        // Display the result
        resultDisplay();

        // Draw;
        if (!winner){
            printf("%s\n", "The game was a draw");
        } else {
            printf("Player %s wins\n", player[winner-1]);
        }

        // Ask for another
        printf("\n\n%s\n", "Would you like to play again?(Y/N): ");
        if (!gameOrNot()) return 0;
    }
}

int gameOrNot(){
    char op[2] = {0};

    op[0] = getch();
    while (stricmp(op, "Y") & stricmp(op, "N"))
        op[0] = getch();
    if (!stricmp(op, "N"))
        return 0;
    else{
        // initial the chessboard
        for(int i = 0; i < 9; i++)
            chessBoard.l[i] = 0x20;
    }
    return 1;
}

void boardDisplay(){
    // print guide
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (j%2)
                printf("%s%d%s%d%s%d\n", "  ", i*3+1, "  #  ", i*3+2, "  #  ", i*3+3);
            else
                printf("%s\n", "     #     #");
        }
        if (i == 2) break;
        printf("%s\n", "#################");
    }    
}

void resultDisplay(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (j%2)
                printf("%s%c%s%c%s%c\n", "  ", chessBoard.g[i][0], "  #  ", chessBoard.g[i][1], "  #  ", chessBoard.g[i][2]);
            else
                printf("%s\n", "     #     #");
        }
        if (i == 2) break;
        printf("%s\n", "#################");
    }    
}

int gaming(){
    int winner = 0;

    // put chess one by one
    for (int i = 0; i < 9;i++){
        char op;
        // Display what the board looks like now
        boardDisplay();
        printf("\n");
        printf("%s\n", "Now: ");
        resultDisplay();
        printf("\n");

        // Ask player to put chess
        printf("%s%d\n", "Time for player ", i%2+1);

        // Get the operation
        while (!isdigit(op = getch()));
        op-=0x31;

        // Judge whether this chess can be placed
        while (chessBoard.l[op] != 0x20){
            printf("%s\n", "There is already a chessman here!");
            printf("%s\n", "Choose another place.");
            resultDisplay();
            printf("\n");
            while (!isdigit(op = getch()));
            op-=0x31;
        }

        // Change the board
        if (i%2)
            chessBoard.l[op] = 79; // 'O';
        else
            chessBoard.l[op] = 88; // 'X';

        system("cls");

        // Judge who've won
        if (winner = termination()){
            break;
        }
    }

    return winner;
}

int termination(){
    // horizontal test
    for (int i = 0; i < 3; i++){
        if (chessBoard.g[i][0] != 0x20 && chessBoard.g[i][0] == chessBoard.g[i][1] && chessBoard.g[i][0] == chessBoard.g[i][2])
            return (chessBoard.g[i][0] % 2 + 1);
    }

    // vertical test
    for (int i = 0; i < 3; i++){
        if (chessBoard.g[0][i] != 0x20 && chessBoard.g[0][i] == chessBoard.g[1][i] && chessBoard.g[0][i] == chessBoard.g[2][i])
            return (chessBoard.g[0][i] % 2 + 1);
    }

    // diagonal test
    if (chessBoard.g[0][0] != 0x20 && chessBoard.g[0][0] == chessBoard.g[1][1] && chessBoard.g[0][0] == chessBoard.g[2][2])
        return (chessBoard.g[1][1] % 2 + 1);
    if (chessBoard.g[0][2] != 0x20 && chessBoard.g[0][2] == chessBoard.g[1][1] && chessBoard.g[0][2] == chessBoard.g[2][0])
        return (chessBoard.g[1][1] % 2 + 1);

    // haven't terminated yet
    return 0;
}
