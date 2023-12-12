#pragma once

#define UP 72 //위쪽 방향키
#define DOWN 80 //아래쪽 방향키
#define LEFT 75 //왼쪽 방향키
#define RIGHT 77   //오른쪽 방향키
#define ENTER 13  //엔터

typedef struct client { //고객정보
    int client_num; //고객 번호
    char name[30];  //이름
    char phone_num[5]; //전화번호 뒷 네자리 + NULL문자
    char password[20];  //비밀번호
    unsigned short int montly_fee; //월 요금제 단계
    unsigned short int overdue;    //연체 횟수
    struct client* p_next;
} CLIENT;

typedef struct cd { //CD 정보
    int cd_num;
    char genre[20]; //장르
    char title[40]; //제목
    unsigned short int level;   //단계(단계에 따른 요금 책정)
    int release_year;   //출시 연도
    struct cd* p_next;
} CD;

typedef struct rent {
    int client_num;
    int cd_num;
    int start_date[3];
    int expected_return_date[3];
    int return_date[3];
    int overdue;    //연체 날짜
    struct rent* p_next;
} RENT;

//기본 기능 함수
void client_file_load(CLIENT** pp_client_head, CLIENT** pp_client_tail, unsigned short int* p_client_count);

void cd_file_load(CD** pp_cd_head, CD** pp_cd_tail, unsigned short int* p_cd_count);

void rent_file_load(RENT** pp_rent_head, RENT** pp_rent_tail, unsigned short int* p_rent_count);

void log_in(CLIENT** pp_client_head, int* log);

void join(CLIENT** pp_client_head, CLIENT** pp_client_tail, unsigned short int* p_count);

void client_info_update(CLIENT** pp_client_head);

void cd_info_update(CD** pp_cd_chead);

void rent_info_update(RENT** pp_rent_head);

void delete_client_all_node(CLIENT* p_client_head);

void delete_cd_all_node(CD* p_cd_head);

void delete_rent_all_node(RENT* p_rent_head);

void exit_();


//방향키로 선택 관련 함수
void gotoxy(int x, int y);

int key_control(void);

int first_menu_choice(void);


//관리자 관련 함수
int manager_menu_choice(void);

int all_client_info_print(CLIENT** pp_client_head,unsigned short int *p_client_count);

int all_cd_info_print(CD** pp_cd_head, unsigned short int* cd_count);

int cd_info_fix_choice();

void cd_fix(CD** pp_cd_head, int *cd_log);

void now_rent(CLIENT** pp_client_head, CD** pp_cd_head, RENT** pp_rent_head);

void black_list_print(CLIENT** pp_client_head);


//사용자 관련 함수
int client_menu_choice(void);

int for_rent_cd_print(CD** pp_cd_head, unsigned short int* p_cd_count);

int cd_rent(CLIENT** pp_client_head, CD** pp_cd_head, RENT** pp_rent_head, RENT** pp_rent_tail, int* p_rent_count, int* log, int* for_rent);

int for_return_rent_print(CD** pp_cd_head, RENT** pp_rent_head, int* log);

void return_rent(CLIENT** pp_client_head, RENT** pp_rent_head, int* log, int* for_return);

void extension_return(CLIENT** pp_client_head, CD** pp_cd_head, RENT** pp_rent_head, int* log, int* for_return_2);

int monthly_fee_choose();

void monthly_fee(CLIENT** pp_client_head, int* log, int* monthly_fee_);

void rent_log_print(CD** pp_cd_head, RENT** pp_rent_head, int* log);

int per_info_fix_choice();

void per_info_fix(CLIENT** pp_client_head, int* log);
