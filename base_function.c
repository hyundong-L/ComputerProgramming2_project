#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "base.h"

void client_file_load(CLIENT** pp_client_head, CLIENT** pp_client_tail, unsigned short int* p_client_count) {    //파일에서 고객 정보 읽기
    int a;
    FILE* client_file = fopen("client.txt", "r");

    if (NULL != client_file) {
        while (1) {
            CLIENT* temp = (CLIENT*)malloc(sizeof(CLIENT));
            a = fscanf(client_file, "%d %s %s %s %hu %hu", &temp->client_num, temp->name, temp->phone_num, temp->password, &temp->montly_fee, &temp->overdue);

            if (EOF == a) {
                free(temp);
                break;
            }
            if (NULL != *pp_client_head) {
                (*pp_client_tail)->p_next = temp;
                (*pp_client_tail) = temp;
            }
            else {
                *pp_client_head = temp;
                *pp_client_tail = temp;
            }
            (*p_client_count)++;
        }
        (*pp_client_tail)->p_next = NULL;
        fclose(client_file);
    }
}

void cd_file_load(CD** pp_cd_head, CD** pp_cd_tail, unsigned short int* p_cd_count) {    //파일에서 cd 정보 읽기
    int a;
    FILE* cd_file = fopen("cd.txt", "r");

    if (NULL != cd_file) {
        while (1) {
            CD* temp = (CD*)malloc(sizeof(CD));
            a = fscanf(cd_file, "%d %s %s %hu %d", &temp->cd_num, temp->genre, temp->title, &temp->level, &temp->release_year);

            if (EOF == a) {
                free(temp);
                break;
            }
            if (NULL != *pp_cd_head) {
                (*pp_cd_tail)->p_next = temp;
                (*pp_cd_tail) = temp;
            }
            else {
                *pp_cd_head = temp;
                *pp_cd_tail = temp;
            }
            (*p_cd_count)++;
        }
        (*pp_cd_tail)->p_next = NULL;
        fclose(cd_file);
    }
}

void rent_file_load(RENT** pp_rent_head, RENT** pp_rent_tail, unsigned short int* p_rent_count) {
    int a;
    FILE* rent_file = fopen("rent.txt", "r");

    if (NULL != rent_file) {
        while (1) {
            RENT* temp = (RENT*)malloc(sizeof(RENT));
            a = fscanf(rent_file, "%d %d %d %d %d %d %d %d %d %d %d %d", &temp->client_num, &temp->cd_num, &temp->start_date[0], &temp->start_date[1], &temp->start_date[2], &temp->expected_return_date[0], &temp->expected_return_date[1], &temp->expected_return_date[2], &temp->return_date[0], &temp->return_date[1], &temp->return_date[2], &temp->overdue);

            if (EOF == a) {
                free(temp);
                break;
            }
            if (NULL != *pp_rent_head) {
                (*pp_rent_tail)->p_next = temp;
                (*pp_rent_tail) = temp;
            }
            else {
                *pp_rent_head = temp;
                *pp_rent_tail = temp;
            }
            (*p_rent_count)++;
        }
        (*pp_rent_tail)->p_next = NULL;
        fclose(rent_file);
    }
}

void log_in(CLIENT** pp_client_head, int* log) {    //로그인
    //관리자
    char manager_id[5] = "1120";
    char manager_ps[20] = "manager";
    //고객
    char in_id[5];
    char in_password[20];

    *log = 0;  //로그인 확인
    gotoxy(30, 10);
    printf("ID(전화번호 뒷자리) : ");
    scanf("%s", in_id);
    gotoxy(47, 11);
    printf("PS : ");
    scanf("%s", in_password);
    system("cls");

    CLIENT* p_node = *pp_client_head;

    if (strcmp(manager_id, in_id) == 0) {
        if (strcmp(manager_ps, in_password) == 0) {
            gotoxy(100, 0);
            printf("관리자\n");
            *log = -9999;
        }
        else *log = -1;
    }
    else {
        while (p_node != NULL) {
            if (strcmp(p_node->phone_num, in_id) == 0) {
                if (strcmp(p_node->password, in_password) == 0) {
                    gotoxy(100, 0);
                    printf("%s님\n", p_node->name);
                    *log = (p_node->client_num);
                    break;
                }
                else {
                    *log = -1;
                    break;
                }
            }
            else {
                p_node = p_node->p_next;
            }
        }
    }
}

void join(CLIENT** pp_client_head, CLIENT** pp_client_tail, unsigned short int* p_client_count) { //회원가입 시 파일과 연결리스트에 고객 정보 추가
    if (NULL != *pp_client_head) {
        (*pp_client_tail)->p_next = (CLIENT*)malloc(sizeof(CLIENT));
        (*pp_client_tail) = (*pp_client_tail)->p_next;
    }
    else {
        *pp_client_head = (CLIENT*)malloc(sizeof(CLIENT));
        *pp_client_tail = *pp_client_head;
    }
    (*p_client_count)++;
    (*pp_client_tail)->client_num = (*p_client_count);  //사용자 번호
    printf("이름을 입력해주세요 : ");
    scanf("%s", (*pp_client_tail)->name);
    printf("전화번호 뒷 네자리를 입력해주세요(예: 0000) : ");
    scanf("%s", (*pp_client_tail)->phone_num);
    printf("비밀번호를 입력해주세요 : ");
    scanf("%s", (*pp_client_tail)->password);
    (*pp_client_tail)->montly_fee = 0;   //요금제
    (*pp_client_tail)->overdue = 0;  //연체 횟수
    (*pp_client_tail)->p_next = NULL;
    system("cls");
    printf("%s님 회원가입이 완료되었습니다.\n", (*pp_client_tail)->name);
    exit_();
}

void client_info_update(CLIENT** pp_client_head) {  //client 파일 내용을 모두 지우고 새로 업데이트
    CLIENT* p_node = *pp_client_head;

    FILE* client_file = fopen("client.txt", "w");

    while (NULL != p_node) {
        fprintf(client_file, "%d %s %s %s %hu %hu\n", p_node->client_num, p_node->name, p_node->phone_num, p_node->password, p_node->montly_fee, p_node->overdue);
        p_node = p_node->p_next;
    }
    fclose(client_file);
}

void cd_info_update(CD** pp_cd_head) {  //CD 파일 내용을 모두 지우고 새로 업데이트
    CD* p_node = *pp_cd_head;

    FILE* cd_file = fopen("cd.txt", "w");

    while (NULL != p_node) {
        fprintf(cd_file, "%d %s %s %hu %d\n", p_node->cd_num, p_node->genre, p_node->title, p_node->level, p_node->release_year);
        p_node = p_node->p_next;
    }
    fclose(cd_file);
}

void rent_info_update(RENT** pp_rent_head) {
    RENT* p_node = *pp_rent_head;

    FILE* rent_file = fopen("rent.txt", "w");

    while (NULL != p_node) {
        fprintf(rent_file, "%d %d %d %d %d %d %d %d %d %d %d %d\n", p_node->client_num, p_node->cd_num, p_node->start_date[0], p_node->start_date[1], p_node->start_date[2], p_node->expected_return_date[0], p_node->expected_return_date[1], p_node->expected_return_date[2], p_node->return_date[0], p_node->return_date[1], p_node->return_date[2], p_node->overdue);
        p_node = p_node->p_next;
    }
    fclose(rent_file);
}

void delete_client_all_node(CLIENT* p_client_head) {   //프로그램 종료 시 고객 연결리스트 비우기
    CLIENT* p_node;
    while (p_client_head != NULL) {
        p_node = p_client_head;
        p_client_head = p_client_head->p_next;
        free(p_node);
    }
}

void delete_cd_all_node(CD* p_cd_head) {     //프로그램 종료 시 cd 연결리스트 비우기
    CD* p_node;
    while (p_cd_head != NULL) {
        p_node = p_cd_head;
        p_cd_head = p_cd_head->p_next;
        free(p_node);
    }
}

void delete_rent_all_node(RENT* p_rent_head) {
    RENT* p_node;
    while (p_rent_head != NULL) {
        p_node = p_rent_head;
        p_rent_head = p_rent_head->p_next;
        free(p_node);
    }
}

void exit_(void) {
    char input;
    printf("\n종료하려면 q를 입력하세요.\n");
    input = getch();
    if (input == 'q') system("cls");
}