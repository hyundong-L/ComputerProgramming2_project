#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "base.h"

int manager_menu_choice(void) {
    int x = 50, y = 10;
    gotoxy(x - 2, y);
    printf("> 고객 정보 열람\n");
    gotoxy(x, y + 1);
    printf("CD 정보 열람\n");
    gotoxy(x, y + 2);
    printf("현재 대여 정보 열람\n");
    gotoxy(x, y + 3);
    printf("블랙리스트 정보 열람\n");
    gotoxy(x, y + 4);
    printf("로그아웃\n");

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
                if (y < 14) {
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

int all_client_info_print(CLIENT** pp_client_head, unsigned short int *p_client_count) {
    int x = 2, y = 0;
    CLIENT* p_node = *pp_client_head;
    gotoxy(x-2, y);
    printf(">");
    while (NULL != p_node) {
        gotoxy(x, y);
        printf("%d %s %s %s %hu %hu\n", p_node->client_num, p_node->name, p_node->phone_num, p_node->password, p_node->montly_fee, p_node->overdue);
        p_node = (p_node)->p_next;
        y++;
    }
    gotoxy(x, y);
    printf("메뉴로 돌아가기\n");
    y = 0;
    while (1) {
        int n = key_control();
        switch (n) {
            case UP: {
                if (y > 0) {
                    gotoxy(x - 2, y);
                    printf(" ");
                    gotoxy(x - 2, --y);
                    printf(">");
                }
                break;
            }
            case DOWN: {
                if (y < *p_client_count) {
                    gotoxy(x - 2, y);
                    printf(" ");
                    gotoxy(x - 2, ++y);
                    printf(">");
                }
                break;
            }
            case ENTER: {
                system("cls");
                return y;
            }
        }
    }
}

int all_cd_info_print(CD** pp_cd_head, unsigned short int* cd_count) {
    int x = 2, y = 0;
    CD* p_node = *pp_cd_head;

    gotoxy(x, 10);
    printf("%d", *cd_count);

    gotoxy(x - 2, y);
    printf(">");

    while (NULL != p_node) {
        gotoxy(x, y);
        printf("%d %s %s %hu %d\n", p_node->cd_num, p_node->genre, p_node->title, p_node->level, p_node->release_year);
        y++;
        p_node = p_node->p_next;
    }
    gotoxy(x, y);
    printf("메뉴로 돌아가기\n");
    y = 0;
    while (1) {
        int n = key_control();
        switch (n) {
        case UP: {
            if (y > 0) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, --y);
                printf(">");
            }
            break;
        }
        case DOWN: {
            if (y < *cd_count) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, ++y);
                printf(">");
            }
            break;
        }
        case ENTER: {
            system("cls");
            return y;
        }
        }
    }
}

int cd_info_fix_choice() {
    int x = 50, y = 10;
    gotoxy(x - 2, y);
    printf(">");
    gotoxy(x, y);
    printf("  장르\n");
    gotoxy(x, y + 1);
    printf("  제목\n");
    gotoxy(x, y + 2);
    printf("출시연도\n");
    gotoxy(x, y + 3);
    printf("메뉴로 돌아가기\n");

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
            if (y < 13) {
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

void cd_fix(CD** pp_cd_head, int* cd_log) {
    CD* p_node = *pp_cd_head;
    int want = cd_info_fix_choice();
    system("cls");

    while (*cd_log != p_node->cd_num) p_node = p_node->p_next;

    if (want == 3) printf("\n");
    else if (want == 0) {
        printf("변경할 장르를 입력해주세요 : ");
        scanf("%s", p_node->genre);
    }
    else if (want == 1) {
        printf("변경할 제목을 입력해주세요 : ");
        scanf("%s", p_node->title);
    }
    else if (want == 2) {
        printf("변경할 출시연도를 입력해주세요 : ");
        scanf("%s", p_node->release_year);
    }
    if (want == 0 || want == 1 || want == 2) printf("변경이 완료되었습니다.\n");
    exit_();
}

void now_rent(CLIENT**pp_client_head, CD** pp_cd_head, RENT** pp_rent_head) {
    RENT* p_rent_node = *pp_rent_head;

    while (NULL != p_rent_node) {
        CLIENT* p_client_node = *pp_client_head;
        CD* p_cd_node = *pp_cd_head;
        if (p_rent_node->return_date[0] == 0) {
            while (p_rent_node->cd_num != p_cd_node->cd_num) p_cd_node = p_cd_node->p_next;
            while (p_rent_node->client_num != p_client_node->client_num) p_client_node = p_client_node->p_next;
            printf("%s님 / %s / %d %d %d / %d %d %d\n", p_client_node->name, p_cd_node->title, p_rent_node->start_date[0], p_rent_node->start_date[1], p_rent_node->start_date[2], p_rent_node->expected_return_date[0], p_rent_node->expected_return_date[1], p_rent_node->expected_return_date[2]);
        }
        p_rent_node = p_rent_node->p_next;
    }
    exit_();
}

void black_list_print(CLIENT** pp_client_head) {
    CLIENT* p_node = *pp_client_head;
    while (NULL != p_node) {
        if (p_node->overdue >= 3) printf("%d번 고객님\n", p_node->client_num);
        p_node = (p_node)->p_next;
    }
    exit_();
}
