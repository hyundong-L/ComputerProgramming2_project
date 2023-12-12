#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "base.h"

int client_menu_choice(void) {
    int x = 50, y = 10;
    gotoxy(x - 2, y);
    printf("> 대여\n");
    gotoxy(x, y + 1);
    printf("반납\n");
    gotoxy(x, y + 2);
    printf("연장\n");
    gotoxy(x, y + 3);
    printf("월 요금제 선택\n");
    gotoxy(x, y + 4);
    printf("대여 기록 열람\n");
    gotoxy(x, y + 5);
    printf("개인정보 수정\n");
    gotoxy(x, y + 6);
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
            if (y < 16) {
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

int for_rent_cd_print(CD** pp_cd_head,unsigned short int *p_cd_count) {
    int x = 2, y = 0;
    CD* p_node = *pp_cd_head;
    gotoxy(x-2, y);
    printf(">");
    while (NULL != p_node) {
        gotoxy(x, y);
        printf("%d %s %s %hu %d", p_node->cd_num, p_node->genre, p_node->title, p_node->level, p_node->release_year);
        p_node = p_node->p_next;
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
                if (y < *p_cd_count) {
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

int cd_rent(CLIENT** pp_client_head, CD** pp_cd_head, RENT** pp_rent_head, RENT** pp_rent_tail, int* p_rent_count, int* log, int* for_rent) {
    int want_rent = 0, price = 0, a = 0;
    CLIENT* p_client_node = *pp_client_head;
    CD* p_cd_node = *pp_cd_head;
    RENT* p_rent_node = *pp_rent_head;


    while (NULL != p_rent_node) {
        if (*for_rent == p_rent_node->cd_num) {
            a = 1;
            break;
        }
        p_rent_node = p_rent_node->p_next;
    }

    
    if (a == 1) {
        printf("이미 대여 중인 CD입니다.\n");
        exit_();
        return a;
    }
    else {
        (*pp_rent_tail)->p_next = (RENT*)malloc(sizeof(RENT));
        (*pp_rent_tail) = (*pp_rent_tail)->p_next;
    
        //현재 시간 받아오기
        time_t now;
        struct tm t;
        time(&now);
        t = *localtime(&now);
    

        //대여하는 사람, 대여 cd 찾기
        while (*log != p_client_node->client_num) p_client_node = p_client_node->p_next;
        while (*for_rent != p_cd_node->cd_num) p_cd_node = p_cd_node->p_next;

        (*pp_rent_tail)->client_num = *log;
        (*pp_rent_tail)->cd_num = *for_rent;
        (*pp_rent_tail)->start_date[0] = t.tm_year+1900;
        (*pp_rent_tail)->start_date[1] = t.tm_mon+1;
        (*pp_rent_tail)->start_date[2] = t.tm_mday;
    
        //요금 관련
        printf("대여 기간(일)을 입력해주세요 : ");
        scanf("%d", &want_rent);
        t.tm_mday += want_rent;
        mktime(&t);
        if (p_client_node->montly_fee == 0 || p_client_node->montly_fee < p_cd_node->level) price = p_cd_node->level * 1000 * want_rent;
        else if (p_client_node->montly_fee >= p_cd_node->level) price = 0;
        printf("가격 : %d원\n반납 날짜 : %d년 %d월 %d일입니다.\n", price, t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);

        (*pp_rent_tail)->expected_return_date[0] = t.tm_year + 1900;
        (*pp_rent_tail)->expected_return_date[1] = t.tm_mon + 1;
        (*pp_rent_tail)->expected_return_date[2] = t.tm_mday;

        (*pp_rent_tail)->return_date[0] = 0;
        (*pp_rent_tail)->return_date[1] = 0;
        (*pp_rent_tail)->return_date[2] = 0;
        (*pp_rent_tail)->overdue = 0;
        (*p_rent_count)++;
        (*pp_rent_tail)->p_next = NULL;
        exit_();
        return 0;
    }
}

int for_return_rent_print(CD** pp_cd_head, RENT** pp_rent_head, int* log) {
    int x = 2, y = 0, count = 0;
    RENT* p_node = *pp_rent_head;
    gotoxy(x - 2, y);
    printf(">");
    while (NULL != p_node) {
        CD* p_cd_node = *pp_cd_head;
        if (p_node->client_num == *log) {
            while (NULL != p_cd_node) {
                if (p_node->cd_num == p_cd_node->cd_num && p_node->return_date[0] == 0) {
                    gotoxy(x, count);
                    printf("%s %d %d %d\n", p_cd_node->title, p_node->start_date[0], p_node->start_date[1], p_node->start_date[2]);
                    count++;
                    break;
                }
                else p_cd_node = p_cd_node->p_next;
            }
        }
        p_node = p_node->p_next;
    }
    if (count == 0) {
        gotoxy(x - 2, y);
        printf(" ");
        gotoxy(x - 2, y);
        printf("대여 내역이 없습니다.\n");
        exit_();
        return -10;
    }
    else {
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
                if (y < count - 1) {
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
}

void return_rent(CLIENT** pp_client_head, RENT** pp_rent_head, int* log, int* for_return) {
    int cnt = 0, day_diff = 0;;
    CLIENT* p_client_node = *pp_client_head;
    RENT* p_rent_node = *pp_rent_head;
    
    double diff = 0;
    time_t expected_return1, return_1;
    struct tm expected_return2, return_2;

    //현재 시간 받아오기
    time_t timer;
    struct tm* t;
    timer = time(NULL);
    t = localtime(&timer);

    while (NULL != p_rent_node) {
        if (p_rent_node->client_num == *log && p_rent_node->return_date[0] == 0) cnt += 1;
        if (cnt == *for_return + 1) {
            p_rent_node->return_date[0] = t->tm_year + 1900;
            p_rent_node->return_date[1] = t->tm_mon + 1;
            p_rent_node->return_date[2] = t->tm_mday;

            //연체 확인용 계산
            return_2.tm_year = t->tm_year;
            return_2.tm_mon = t->tm_mon;
            return_2.tm_mday = t->tm_mday;
            return_2.tm_hour = 0;
            return_2.tm_min = 0;
            return_2.tm_sec = 0;
            return_1 = mktime(&return_2);

            expected_return2.tm_year = p_rent_node->expected_return_date[0] - 1900;
            expected_return2.tm_mon = p_rent_node->expected_return_date[1] - 1;
            expected_return2.tm_mday = p_rent_node->expected_return_date[2];
            expected_return2.tm_hour = 0;
            expected_return2.tm_min = 0;
            expected_return2.tm_sec = 0;
            expected_return1 = mktime(&expected_return2);

            diff = difftime(expected_return1, return_1);
            day_diff = diff / (60 * 60 * 24);
            diff = diff - (day_diff * 60 * 60 * 24);
            

            if (day_diff < 0) {
                printf("%d일 연체되었습니다.\n", day_diff * -1);
                p_rent_node->overdue += day_diff * -1;
                while (*log != p_client_node->client_num) {
                    p_client_node = p_client_node->p_next;
                }
                p_client_node->overdue += 1;
                exit_();
            }
            else {
                printf("반납이 완료되었습니다.\n");
                exit_();
            }
            break;
        }
        p_rent_node = p_rent_node->p_next;
    }
}

void extension_return(CLIENT** pp_client_head, CD**pp_cd_head, RENT** pp_rent_head, int* log, int* for_return_2) {
    int cnt = 0, day = 0, add_price = 0;
    struct tm t;
    CLIENT* p_client_node = *pp_client_head;
    CD* p_cd_node = *pp_cd_head;
    RENT* p_node = *pp_rent_head;

    while (NULL != p_node) {
        if (p_node->client_num == *log && p_node->return_date[0] == 0) cnt += 1;
        if (cnt == *for_return_2 + 1) {
            printf("연장할 날짜(일)를 입력해주세요 : ");
            scanf("%d", &day);
            
            p_node->expected_return_date[2] += day;

            t.tm_year = p_node->expected_return_date[0] - 1900;
            t.tm_mon = p_node->expected_return_date[1] - 1;
            t.tm_mday = p_node->expected_return_date[2];
            t.tm_hour = 0;
            t.tm_min = 0;
            t.tm_sec = 0;
            mktime(&t);

            p_node->expected_return_date[0] = t.tm_year + 1900;
            p_node->expected_return_date[1] = t.tm_mon + 1;
            p_node->expected_return_date[2] = t.tm_mday;

            while (p_node->cd_num != p_cd_node->cd_num) p_cd_node = p_cd_node->p_next;
            while (p_node->client_num != p_client_node->client_num) p_client_node = p_client_node->p_next;

            if (p_client_node->montly_fee == 0 || p_client_node->montly_fee < p_cd_node->level) add_price = day * p_cd_node->level * 1000;
            else if (p_client_node->montly_fee >= p_cd_node->level) add_price = 0;

            printf("반납일 : %d년 %d월 %d일\n추가금 : %d원\n", p_node->expected_return_date[0], p_node->expected_return_date[1], p_node->expected_return_date[2], add_price);
            break;
        }
        p_node = p_node->p_next;
    }
    exit_();
}

int monthly_fee_choose() {
    int x = 2, y = 0;

    gotoxy(x - 2, y);
    printf(">");
    gotoxy(x, y);
    printf("월 30,000원 : 1단계 무제한 CD 대여\n");
    gotoxy(x, y + 1);
    printf("월 40,000원 : 2단계 무제한 CD 대여\n");
    gotoxy(x, y + 2);
    printf("월 50,000원 : 3단계 무제한 CD 대여\n");
    gotoxy(x, y + 3);
    printf("메뉴로 돌아가기\n");

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
                if (y < 3) {
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

void monthly_fee(CLIENT** pp_client_head, int* log, int *monthly_fee_) {
    CLIENT* p_node = *pp_client_head;

    if (*monthly_fee_ == 3) system("cls");
    else if (*monthly_fee_ == 0 || *monthly_fee_ == 1 || *monthly_fee_ == 2) {
        while (*log != p_node->client_num) {
            p_node = p_node->p_next;
        }
        p_node->montly_fee = *monthly_fee_ + 1;
        printf("%d단계 요금을 선택하셨습니다.\n", *monthly_fee_ + 1);
        exit_();
    }
}

void rent_log_print(CD**pp_cd_head, RENT** pp_rent_head, int* log) {
    RENT* p_node = *pp_rent_head;

    printf("제목 / 대여 날짜 / 반납 날짜 / 연체 일\n");
    printf("\n");
    while (NULL != p_node) {
        CD* p_cd_node = *pp_cd_head;
        if (*log == p_node->client_num) {
            while (p_node->cd_num != p_cd_node->cd_num) p_cd_node = p_cd_node->p_next;
            if (p_node->return_date[0] == 0) printf("%s / %d %d %d\n", p_cd_node->title, p_node->start_date[0], p_node->start_date[1], p_node->start_date[2]);
            else printf("%s / %d %d %d / %d %d %d / %d\n", p_cd_node->title, p_node->start_date[0], p_node->start_date[1], p_node->start_date[2], p_node->return_date[0], p_node->return_date[1], p_node->return_date[2], p_node->overdue);
        }
        p_node = p_node->p_next;
    }
    exit_();
}

int per_info_fix_choice() {
    int x = 50, y = 10;
    gotoxy(x - 2, y);
    printf(">");
    gotoxy(x, y);
    printf("     이름\n");
    gotoxy(x, y + 1);
    printf("   전화번호\n");
    gotoxy(x, y + 2);
    printf("   비밀번호\n");
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

void per_info_fix(CLIENT** pp_client_head, int* log) {
    CLIENT* p_node = *pp_client_head;
    int want_ = per_info_fix_choice();
    system("cls");

    while (*log != p_node->client_num) p_node = p_node->p_next;

    if (want_ == 3) printf("\n");
    else if (want_ == 0) {
        printf("변경할 이름을 입력해주세요 : ");
        scanf("%s", p_node->name);
    }
    else if (want_ == 1) {
        printf("변경할 전화번호를 입력해주세요 : ");
        scanf("%s", p_node->phone_num);
    }
    else if (want_ == 2) {
        printf("변경할 비밀번호를 입력해주세요 : ");
        scanf("%s", p_node->password);
    }
    if (want_ == 0 || want_ == 1 || want_ == 2) printf("변경이 완료되었습니다.\n");
    exit_();
}
