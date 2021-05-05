#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define X 'X'
#define O 'O'
#define EMPTY ' '

typedef struct {
    int x, y;
}cords;

void reset_board(char board[3][3]) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void print_board(char board[3][3]) {
    int cell_nb = 1;
    for (int i=0; i<3; i++) {
        printf("\t%s%d%s%d%s%d%s\n", "----", cell_nb, "-------", cell_nb+1, "-------", cell_nb+2, "----");
        printf("\t%s\n\t", "|       |       |       |");
        cell_nb+=3;
        for (int j=0; j<3; j++) {
            printf("|   %c   ", board[i][j]);
        }
        printf("|\n\t%s\n", "|       |       |       |");
    }
    printf("\t%s\n", "-------------------------");
}

bool cell_empty(char board[3][3], int x, int y) {
    return board[x][y] == EMPTY ? true : false;
}

cords cell_cords(int cell_nb) {
    cords cell;
    int x, y;
    switch (cell_nb) {
        case 1: cell.x=0;cell.y=0;break;
        case 2: cell.x=0;cell.y=1;break;
        case 3: cell.x=0;cell.y=2;break;
        case 4: cell.x=1;cell.y=0;break;
        case 5: cell.x=1;cell.y=1;break;
        case 6: cell.x=1;cell.y=2;break;
        case 7: cell.x=2;cell.y=0;break;
        case 8: cell.x=2;cell.y=1;break;
        case 9: cell.x=2;cell.y=2;break;
    };
    return cell;
}

void play_cell(char board[3][3], char player, int x, int y) {
    if (cell_empty(board, x, y)) {
        board[x][y] = player;
    }
}

bool cell_available(char board[3][3]) {
    bool available = false;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (cell_empty(board, i, j)) {
                available = true;
            }
        }
    }
    return available;
}

int get_user_choice() {
    char user_choice[1000];

    scanf("%s", user_choice);
    return atoi(user_choice) > 0 ? atoi(user_choice) : 0;
}

bool won(char board[3][3], char player) {
    if ((board[0][0]==player && board[0][1]==player && board[0][2]==player)
     || (board[1][0]==player && board[1][1]==player && board[1][2]==player)
     || (board[2][0]==player && board[2][1]==player && board[2][2]==player)
     || (board[0][0]==player && board[1][0]==player && board[2][0]==player)
     || (board[0][1]==player && board[1][1]==player && board[2][1]==player)
     || (board[0][2]==player && board[1][2]==player && board[2][2]==player)
     || (board[0][0]==player && board[1][1]==player && board[2][2]==player)
     || (board[0][2]==player && board[1][1]==player && board[2][0]==player)) {
         return true;
    } else {
        return false;
    }
}

void print_header() {
    printf("\t%s\n", "---------------");
    printf("\t%s\n", "> TIC TAC TOE <");
    printf("\t%s\n\n", "---------------");
}

void game_result(char board[3][3], char msg[30]) {
    print_header();
    printf("\n");
    print_board(board);
    printf("\t%s\n\n", msg);
}

void play_1vs1(char board[3][3]) {
    int user_choice;
    int x, y;
    cords cell;
    int turn = 1;
    bool invalid_cell=false, cell_token=false;
    char error[30];
    char player;

    player = X;

    while (cell_available(board)) {
        do {
            print_header();
            if (invalid_cell) {
                strcpy(error, "Invalid cell number!");
            } else if (cell_token) {
                strcpy(error, "Cell token!");
            } else {
                strcpy(error, "Enter a number from 1 to 9");
            }
            printf("\t%s\n", error);

            print_board(board);
            printf("\t%s %c %s", "Player", player, "your turn: ");
            user_choice = get_user_choice();

            if (user_choice >= 1 && user_choice <= 9) {
                cell = cell_cords(user_choice);
                if (cell_empty(board, cell.x, cell.y)) {
                    play_cell(board, player, cell.x, cell.y);
                    turn = (turn==1? 2:1);
                    player = (player==X? O:X);
                    cell_token = false;
                } else {
                    cell_token = true;
                }
                invalid_cell = false;
            } else {
                invalid_cell = true;
            }

            system("clear");
        } while (cell_empty(board, cell.x, cell.y));

        if (won(board, X)) {
            game_result(board, "Player X won the game!");
            break;
        } else if (won(board, O)) {
            game_result(board, "Player O won the game!");
            break;
        } else if (!cell_available(board) && !won(board, X) && !won(board, O)) {
            game_result(board, "Draw!");
            break;
        }
    }
}

int main() {
    char board[3][3];

    system("clear");
    reset_board(board);
    play_1vs1(board);

    return 0;
}