#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "base.h"


void test(CLIENT** pp_client_head,CD** pp_cd_head,RENT** pp_rent_head) {    //입출력 테스트용
    CLIENT* p_node = *pp_client_head;
    CD* p_cd_node = *pp_cd_head;
    RENT* p_rent_node = *pp_rent_head;
    while (NULL != p_node) {
        printf("%d %s %s %s %hu %hu\n", p_node->client_num, p_node->name, p_node->phone_num, p_node->password, p_node->montly_fee, p_node->overdue);
        p_node = (p_node)->p_next;
    }
    
    while (NULL != p_cd_node) {
        printf("%d %s %s %hu %d\n", p_cd_node->cd_num, p_cd_node->genre, p_cd_node->title, p_cd_node->level, p_cd_node->release_year);
        p_cd_node = p_cd_node->p_next;
    }

    while (NULL != p_rent_node) {
        printf("%d %d %d %d %d %d %d %d %d\n", p_rent_node->client_num, p_rent_node->cd_num, p_rent_node->start_date[0], p_rent_node->start_date[1], p_rent_node->start_date[2], p_rent_node->return_date[0], p_rent_node->return_date[1], p_rent_node->return_date[2], p_rent_node->overdue);
        p_rent_node = p_rent_node->p_next;
    }
}

int main(void) {
    unsigned short int client_count = 0, cd_count = 0, rent_count = 0;
    int want_ = 0, log = 0;

    CLIENT* p_client_head = NULL, * p_client_tail = NULL;  //고객 연결리스트 헤드, 테일
    CD* p_cd_head = NULL, * p_cd_tail = NULL;    //CD 연결리스트 헤드, 테일
    RENT* p_rent_head = NULL, * p_rent_tail = NULL;

    client_file_load(&p_client_head, &p_client_tail, &client_count); //txt 파일에 저장된 고객정보 불러오기.
    cd_file_load(&p_cd_head, &p_cd_tail, &cd_count);
    rent_file_load(&p_rent_head, &p_rent_tail, &rent_count);

    for (;;) {
        int want_ = first_menu_choice();
        system("cls");

        if (want_ == 0) {
            int after_login;
            log_in(&p_client_head, &log);
            if (log == -9999) { //관리자 메뉴
                while (1) {
                    back:
                        after_login = manager_menu_choice();
                        system("cls");

                        if (after_login == 4) break;
                        else if (after_login == 0) {
                            int fir = all_client_info_print(&p_client_head, &client_count) + 1;
                            if (fir == client_count+1) goto back;
                            per_info_fix(&p_client_head, &fir);
                        }
                        else if (after_login == 1) {
                            int sec_ = all_cd_info_print(&p_cd_head, &cd_count) + 1;
                            if (sec_ == cd_count + 1) goto back;
                            cd_fix(&p_cd_head, &sec_);
                        }
                        else if (after_login == 2) now_rent(&p_client_head, &p_cd_head, &p_rent_head);
                        else if (after_login == 3) black_list_print(&p_client_head);
                }
            }
            else if (log >= 1) {   //사용자 메뉴
                int want_2 = 0;
                while (1) {
                    back_2:
                        after_login = client_menu_choice();
                        system("cls");

                        if (after_login == 6) break;
                        else if (after_login == 0) {
                            int for_rent = for_rent_cd_print(&p_cd_head, &cd_count)+1;
                            if (for_rent == cd_count + 1) goto back_2;
                            int a = cd_rent(&p_client_head, &p_cd_head, &p_rent_head, &p_rent_tail, &rent_count, &log, &for_rent);
                            if (a == 1) goto back_2;
                        }
                        else if (after_login == 1) {
                            int for_return = for_return_rent_print(&p_cd_head, &p_rent_head, &log);
                            return_rent(&p_client_head, &p_rent_head, &log, &for_return);
                        }
                        else if (after_login == 2) {
                            int for_return_2 = for_return_rent_print(&p_cd_head, &p_rent_head, &log);
                            if (for_return_2 != -10) extension_return(&p_client_head, &p_cd_head, &p_rent_head, &log, &for_return_2);
                        }
                        else if (after_login == 3) {
                            int monthly_fee_ = monthly_fee_choose();
                            monthly_fee(&p_client_head, &log, &monthly_fee_);
                        }
                        else if (after_login == 4) rent_log_print(&p_cd_head, &p_rent_head, &log);
                        else if (after_login == 5) per_info_fix(&p_client_head, &log);
                }
            }
            else if (log == -1) {
                gotoxy(50, 13);
                printf("비밀번호가 잘못되었습니다.\n");
            }
            else if (log == 0) {
                gotoxy(50, 13);
                printf("아이디가 잘못되었습니다.\n");
            }
        }
        else if (want_ == 1) {
            join(&p_client_head, &p_client_tail, &client_count);
        }
        else if (want_ == 2) {
            //test(&p_client_head,&p_cd_head, &p_rent_head);

            client_info_update(&p_client_head);
            cd_info_update(&p_cd_head);
            rent_info_update(&p_rent_head);

            delete_client_all_node(p_client_head);
            delete_cd_all_node(p_cd_head);
            delete_rent_all_node(p_rent_head);

            break;
        }
        else {
            printf("1~3 사이의 숫자를 입력해주세요.\n");
        }
    }
}
