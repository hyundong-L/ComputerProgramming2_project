#pragma once

#define UP 72 //���� ����Ű
#define DOWN 80 //�Ʒ��� ����Ű
#define LEFT 75 //���� ����Ű
#define RIGHT 77   //������ ����Ű
#define ENTER 13  //����

typedef struct client { //������
    int client_num; //�� ��ȣ
    char name[30];  //�̸�
    char phone_num[5]; //��ȭ��ȣ �� ���ڸ� + NULL����
    char password[20];  //��й�ȣ
    unsigned short int montly_fee; //�� ����� �ܰ�
    unsigned short int overdue;    //��ü Ƚ��
    struct client* p_next;
} CLIENT;

typedef struct cd { //CD ����
    int cd_num;
    char genre[20]; //�帣
    char title[40]; //����
    unsigned short int level;   //�ܰ�(�ܰ迡 ���� ��� å��)
    int release_year;   //��� ����
    struct cd* p_next;
} CD;

typedef struct rent {
    int client_num;
    int cd_num;
    int start_date[3];
    int expected_return_date[3];
    int return_date[3];
    int overdue;    //��ü ��¥
    struct rent* p_next;
} RENT;

//�⺻ ��� �Լ�
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


//����Ű�� ���� ���� �Լ�
void gotoxy(int x, int y);

int key_control(void);

int first_menu_choice(void);


//������ ���� �Լ�
int manager_menu_choice(void);

int all_client_info_print(CLIENT** pp_client_head,unsigned short int *p_client_count);

int all_cd_info_print(CD** pp_cd_head, unsigned short int* cd_count);

int cd_info_fix_choice();

void cd_fix(CD** pp_cd_head, int *cd_log);

void now_rent(CLIENT** pp_client_head, CD** pp_cd_head, RENT** pp_rent_head);

void black_list_print(CLIENT** pp_client_head);


//����� ���� �Լ�
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
