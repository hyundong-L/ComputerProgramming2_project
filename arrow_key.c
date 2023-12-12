#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "base.h"

void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int key_control(void) {
    char temp = getch();

    if (temp == UP) return UP;
    else if (temp == DOWN) return DOWN;
    else if (temp == LEFT) return LEFT;
    else if (temp == RIGHT) return RIGHT;
    else if (temp == ENTER) return ENTER;
    else return 0;
}

int first_menu_choice(void) {
    int x = 50, y = 10;
    gotoxy(x - 2, y);
    printf(">  로그인\n");
    gotoxy(x, y + 1);
    printf("회원가입\n");
    gotoxy(x, y + 2);
    printf("  종료\n");

    while (1) {
        int n = key_control();
        switch (n) {
            case UP: {
                if (y > 10) {
                    gotoxy(x - 2, y);
                    printf(" ");
                    gotoxy(x - 2, --y);
                    printf(">");
                }
                break;
            }
            case DOWN: {
                if (y < 12) {
                    gotoxy(x - 2, y);
                    printf(" ");
                    gotoxy(x - 2, ++y);
                    printf(">");
                }
                break;
            }
            case ENTER: {
                return y - 10;
            }
        }
    }
}

