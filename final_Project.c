#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
//오류 예외처리
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"winmm")
int stage = 1;
char Nick[10];

int stack[MAX_STACK_SIZE];      //스택 구현
int top = -1;

int IsEmpty() { //비어있는지 확인
    if (top < 0)
        return 1;
    else
        return 0;
}
int IsFull() {      //꽉차있으면 Push 싪패
    if (top >= MAX_STACK_SIZE - 1)
        return 1;
    else
        return 0;
}


void push(int value) {
    if (IsFull() == 1)
        printf("스택이 가득 찼습니다.");
    else
        stack[++top] = value;
}

int pop() {         //회원 정보 삭제 위한 pop구현
    if (IsEmpty() == 1)
        printf("스택이 비었습니다.");
    else
        return stack[top--];
}
//구조체 활용부분
typedef struct {
    char x;
    char y;
    char hp;
}enemy1;
void gotoxy(int x, int y) {
    COORD Pos = { x,y };//"COORD 구조체(콘솔화면)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}//콘솔창 중심좌표이동 함수
void removeCursor(void)
{
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}//콘솔창 커서제거 합수
int user(void)//회원가입,로그인 합수
{
    char ID[20], CheckID[20], PW[20], CheckPW[20];
    int num, i = 0;
    char ch;
    int count, success = 0, same = 0;
    FILE* fp;
    removeCursor();
    gotoxy(18, 22);
    printf("회원가입: R   회원삭제 : D \n");
    printf("                로그인: 아무키나 누르세요(R제외)\n");
    num = _getch();
    if (num == 'R' || num == 'r') {
    REGISTER://회원가입
        same = 0;
        system("cls");
        printf("회원가입 할 ID입력 : ");
        //하나의 키만 받는 함수
        scanf("%s", ID);
        //ID 중복검사
        fp = fopen("ID.txt", "rt");
        if (fp != NULL)
        {
            while (feof(fp) == 0)
            {
                fscanf(fp, "%s", &CheckID); //문자열(STRING) 구현 부분
                if (strcmp(CheckID, ID) == 0)
                {
                    same = 1;
                    break;
                }
            }
            fclose(fp);
        }
        if (same == 1)
        {
            printf("중복된 ID입니다. 재입력해주세요\n");
            system("pause");
            goto REGISTER;
        }
        fp = fopen("ID.txt", "a+t");
        fprintf(fp, "%s\n", ID);    //파일에 입력위한 FPRINT사용
        fclose(fp);
        printf("\n회원가입 할 PW입력 : ");
        scanf("%s", PW);
        fp = fopen("PW.txt", "a+t");
        fprintf(fp, "%s\n", PW);
        fclose(fp);
        printf("\n회원가입 할 닉네임입력 : ");
        scanf("%s", Nick);
        fp = fopen("Nick.txt", "a+t");
        fprintf(fp, "%s\n", Nick);
        fclose(fp);
        printf("\n회원가입 완료. 로그인 페이지로 이동합니다.\n");
        system("pause");
    }
    
    if (num == 'D' || num == 'd') { //Stack으로 가장 최근에 넣은 아이디 정보 삭제
        system("cls");
        struct Info {       //구조체 선언
            char ID[20];
            char PW[40];
            char Nick[40];
        }Info;
       
        
        struct Info info[100];
        FILE* fID = fopen("ID.txt", "a+t"); //파일 오픈
        FILE* fPW = fopen("PW.txt", "a+t");
        FILE* fNick = fopen("Nick.txt", "a+t");
        
        char readID[20];
        char readPW[40];
        char readNick[40];
        char mem[20][3];
        
        int cnt = 0;
        while (fgets(readID, sizeof(readID), fID) != NULL) {
            strcpy(info[cnt].ID, readID);       //==으로 할당이 안되니 strcpy로 할당
            cnt++;
        }
        fclose(fID);
        cnt = 0;
        while (fgets(readPW, sizeof(readPW), fPW) != NULL) {
            strcpy(info[cnt].PW, readPW);       //구조체 배열에 PW할당
            cnt++;
        }
        fclose(fPW);

        cnt = 0;
        while (fgets(readNick, sizeof(readNick), fNick) != NULL) {
            strcpy(info[cnt].Nick, readNick);       //구조체 배열에 Nick할당
            cnt++;
        }
        fclose(fNick);

        for (int i = 0; i < cnt; i++) {
            push(i);
        }

        printf("%d번째. 마지막 원소 삭제\n", pop());
        int new_cnt = top;

        FILE* fID_new = fopen("ID.txt", "wt");      //새로운 파일 입출력 만들어서
        FILE* fPW_new = fopen("PW.txt", "wt");      //다시 파일에 쓰기
        FILE* fNick_new = fopen("Nick.txt", "wt");

        for (int i = 0; i <= new_cnt; i++) {
            fprintf(fID_new, "%s", info[i].ID);
            fprintf(fPW_new, "%s", info[i].PW);
            fprintf(fNick_new, "%s", info[i].Nick);
        }
        fclose(fID);
        fclose(fPW);
        fclose(fNick);

        system("pause");
    }
    
IDINPUT://로그인ID입력
    count = 0;
    system("cls");
    printf("로그인 할 ID입력 : ");
    scanf("%s", ID);
    //아이디 존재확인
    fp = fopen("ID.txt", "rt");
    while (feof(fp) == 0)
    {
        fscanf(fp, "%s", &CheckID);
        if (strcmp(CheckID, ID) == 0)
        {
            success = 1;
            break;
        }
        count++;
    }
    fclose(fp);
    if (success == 0)
    {
        fclose(fp);
        printf("아이디가 틀렸거나 없습니다. 회원가입:Y 아이디 다시입력:R\n");
        while (1) {
            ch = _getch();
            if (ch == 'y' || ch == 'Y')
                goto REGISTER; 
            if (ch == 'R' || ch == 'r')
                goto IDINPUT;
        }
    }
    success = 0;
PWINPUT://비밀번호 입력
    printf("로그인 할 PW입력 : ");
    scanf("%s", PW);
    fp = fopen("PW.txt", "rt");
    //success = 1;
    do {
        fscanf(fp, "%s\n", CheckPW);
        i++;
    } while (i <= count);//아이디 파일과 줄 번호를 맞춰줌
    
    if (strcmp(CheckPW, PW) == 0)
        success = 1;
    if (success == 0)
    {
        fclose(fp); i = 0;
        printf("비밀번호가 틀렸습니다. 회원가입:Y 비밀번호 다시입력:R\n");
        while (1) {
            ch = _getch();
            if (ch == 'y' || ch == 'Y')
                goto REGISTER;
            if (ch == 'R' || ch == 'r')
                goto PWINPUT;
        }
    }
    fclose(fp);

    fp = fopen("Nick.txt", "rt"); i = 0;
    do {
        fscanf(fp, "%s", Nick);
        i++;
    } while (i <= count);
    fclose(fp);

    system("cls");
    printf("%s님 안녕하세요!\n", Nick);
    return count;
}//게임 구현
int Game(void)
{
    int x1, x2, x = 11, oldx = 11;
    int dx1, dx2, dx = 17, doldx = 17;
    //화면 비율
    int map[21][30] = { 0 };
    int i, j, k = 0, temp, hp = 3;
    clock_t curtime = 0, oldtime;//시간 저장
    removeCursor();
    for (i = 0; i < 21; i++) {
        map[i][0] = 1;
        map[i][29] = 1;
    }
    gotoxy(0, 0);
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 30; j++) {
            if (map[i][j] == 0) printf("  ");
            else if (map[i][j] == 1) printf("■");
        }printf("\n");
    }
    for (i = 0; i < 4; i++) {
        gotoxy(0, 21 + i);
        printf("■");
        gotoxy(58, 21 + i);
        printf("■");
    }
    map[20][11] = 3;
    map[20][17] = 4;//캐릭터 만들기
    srand((unsigned)time(NULL));
    removeCursor();
    oldtime = clock();
    system("pause");
    while (1) {
        //맵
        gotoxy(2, 0);
        for (i = 0; i < 21; i++) {
            for (j = 1; j < 29; j++) {
                if (map[i][j] == 0) printf("  ");
                else if (map[i][j] == 3) {
                    //배경색 변경
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                    printf("△");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if (map[i][j] == 4) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    printf("△");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if (map[i][j] == 2) printf("º");
                else if (map[i][j] == 5) printf("●");
                else if (map[i][j] == 6) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    printf("●");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if (map[i][j] == 7) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    printf("●");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
            }gotoxy(2, i + 1);
        }
        gotoxy(60, 2);
        printf("STAGE: %d", stage);
        gotoxy(60, 7);
        printf("HP: %d", hp);
        gotoxy(60, 10);
        printf("남은 시간: %.2f초", (double)(30 - (clock() - oldtime) / 1000));
        //사용자입력에 따른 캐릭터의 움직임과 총알 생성
        x1 = x - 1;
        x2 = x + 1;
        oldx = x;
        dx1 = dx - 1;
        dx2 = dx + 1;
        doldx = dx;
        if (_kbhit()) {
            //안 겹치게, 프레임을 벗어나지 않게
            if (GetAsyncKeyState(0x41)) {//a
                if (x1 != 0 && x1 != oldx && map[20][x1] != 1)
                    x--;
            }
            if (GetAsyncKeyState(0x44)) {//d
                if (x2 != 29 && x2 != doldx && map[20][x2] != 1)
                    x++;
            }

            if (GetAsyncKeyState(0x4A)) {//j
                if (dx1 != oldx && dx1 != 0 && map[20][x1] != 1)
                    dx--;
            }
            if (GetAsyncKeyState(0x4C)) {//k
                if (dx2 != 29 && dx2 != oldx && map[20][x2] != 1)
                    dx++;
            }
            if (GetAsyncKeyState(0x53)) {//s
                map[19][oldx] = 2;
            }
            if (GetAsyncKeyState(0x4B)) {//k
                map[19][doldx] = 2;
            }
        }
        if (oldx != x) {
            map[20][x] = 3;
            map[20][oldx] = 0;
        }

        if (doldx != dx) {
            map[20][dx] = 4;
            map[20][doldx] = 0;
        }
        //총알과 운석 충돌시
        for (i = 1; i < 20; i++) {
            for (j = 0; j < 30; j++) {
                if (map[i][j] == 2)
                {
                    if (map[i - 1][j] == 6 || map[i - 1][j] == 7) {
                        map[i - 1][j]--; map[i][j] = 0;
                    }
                    else if (map[i - 1][j] == 5) {
                        map[i - 1][j] = 0; map[i][j] = 0;
                    }

                }
            }
        }
        //총알 진행과 속도
        if (clock() - oldtime > (1000 - 40 * stage) * k)
        {
            for (i = 0; i < 21; i++) {
                for (j = 0; j < 30; j++) {
                    if (map[i][j] == 2)
                    {
                        if (i == 0)
                        {
                            map[i][j] = 0;
                            continue;
                        }
                        map[i][j] = 0;
                        map[i - 1][j] = 2;
                    }
                }
            }
        }
        //운석 속도
        if (clock() - oldtime > (1500 - 50 * stage) * k) {
            for (i = 20; i >= 0; i--) {
                for (j = 0; j < 30; j++) {
                    if (map[i][j] == 5 || map[i][j] == 6 || map[i][j] == 7)
                    {
                        if (i == 20) {
                            map[i][j] = 0;
                            hp--;
                            continue;
                        }
                        temp = map[i][j];
                        map[i][j] = 0;
                        map[i + 1][j] = temp;
                    }
                }
            }
            //랜덤함수를 이용한 스테이지별 운석 생성
            if (stage == 1 || stage == 2) {
                for (i = 0; i < 3; i++) {
                    map[0][1 + rand() % 28] = 5;
                    map[0][1 + rand() % 28] = 6;
                }
            }
            else if (stage == 3 || stage == 4) {
                for (i = 0; i < 3; i++) {
                    map[0][1 + rand() % 28] = 5;
                    map[0][1 + rand() % 28] = 7;
                }
            }
            else if (stage == 5 || stage == 6) {
                for (i = 0; i < 3; i++) {
                    map[0][1 + rand() % 28] = 5;
                    map[0][1 + rand() % 28] = 6;
                    map[0][1 + rand() % 28] = 7;
                }
            }
            else if (stage >= 7) {
                for (i = 0; i < 3; i++) {
                    map[0][1 + rand() % 28] = 5;
                    map[0][1 + rand() % 28] = 6;
                    map[0][1 + rand() % 28] = 7;
                    map[0][1 + rand() % 28] = 6;
                    map[0][1 + rand() % 28] = 7;
                }
            }
            k++;//시간제한유지용 변수
        }
        Sleep(30);
        if (hp <= 0)
            return -1;
        if (clock() - oldtime > 30 * 1000)
            return 0;
    }
    return 0;


}
//지구도트
void ShowEarth(void) {
    int i, j;
    int earthmap[4][28] = {
       0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
       0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
       0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };
    gotoxy(0, 21);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 28; j++) {
            if (earthmap[i][j] == 1) printf("■");
            else if (earthmap[i][j] == 0) printf("  ");
        }
        printf("\n  ");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
int main(void)
{
    char count;
    int score[500];
    int i = 0, j = 0;
    char map1[9][36] = {
       1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,0,0,
       1,0,0,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,
       1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,

       1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,
       1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,0,0,
       1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
       1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
       1,0,0,1,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
       1,1,1,1,0,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0 };
    char map2[9][36] = {
       1,1,1,1,1,0,0,1,1,1,0,0,1,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,0,
       1,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,0,
       1,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,
       1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,0,
       1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,0,
       1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,1,0,0,0,0,
       1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,
       1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,
       1,1,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0 };
    FILE* fp = NULL;
    gotoxy(2, 1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 36; j++) {
            if (map1[i][j] == 0) printf("  ");
            else if (map1[i][j] == 1) printf("●");
        }printf("\n  ");
    }
    printf("\n  ");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 36; j++) {
            if (map2[i][j] == 0) printf("  ");
            else if (map2[i][j] == 1) printf("●");
        }printf("\n  ");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    PlaySound(TEXT("main.wav"), NULL, SND_ASYNC | SND_LOOP);//배경음 출력
    count = user();//회원가입or로그인,그리고 몇번째 회원인지를 알아냄(0번째부터 있음)
    //PlaySound(NULL,0,0);//배경음 종료
    //게임 목표 및 방법 출력
    gotoxy(17, 5);
    printf("게임 목표: 떨어지는 운석들을 파괴하여 지구를 지키자!");
    gotoxy(30, 7);
    printf("게임 방법");
    gotoxy(4, 9);
    printf("A:파랑 전투기 좌측이동 S:파랑 전투기 총알 발사 D:파랑 전투기 우측이동");
    gotoxy(4, 11);
    printf("J:빨강 전투기 좌측이동 K:빨강 전투기 총알 발사 L:빨강 전투기 우측이동");
    gotoxy(4, 13);
    printf("흰 운석: 1LV, 노랑 운석:2LV, 빨강 운석:3LV");
    gotoxy(4, 15);
    printf("총알로 맞힐때 마다 1LV씩 감소, 1LV일 때 맞히면 운석 파괴");
    gotoxy(4, 17);
    while (1)
    {
        system("cls");
        for (i = 0; i < 25; i++) {
            for (j = 0; j < 39; j++) {
                printf("■");
                //Sleep();
            }
            printf("\n");
        }
        gotoxy(35, 13);
        printf("STAGE %d", stage);
        gotoxy(25, 14);
        system("pause");
        system("cls");
        ShowEarth();
        if (Game() == -1)
            break;
        stage++;
    }//게임 실행 및 종료


    fp = fopen("SCORE.txt", "rt");
    if (fp == NULL) {
        fp = fopen("SCORE.txt", "wt");
        fprintf(fp, "0\n");
        fclose(fp);
    }//게임 처음일 때 SCORE텍스트파일 생성과 초기값 출력해줌.
    else fclose(fp);
    fp = fopen("SCORE.txt", "rt");
    i = 0; j = 0;
    while (feof(fp) == 0)
    {
        fscanf(fp, "%d\n", &score[i]);
        i++;
    }//각 회원들의 점수를 불러옴,i변수로 몇명인지 알아냄.
    system("cls");//콘솔창 지움
    gotoxy(15, 10);
    if (score[count] < stage) {//최고기록일때
        printf("%s님 최고 기록 경신! 최고기록:%dSTAGE\n\n\t\t\t", Nick, stage);
        //PlaySound(TEXT("clap.wav"),NULL,SND_ASYNC|SND_LOOP);
        score[count] = stage;
    }
    else {//최고기록경신이 아닐때
        printf("%s님 최고 기록 경신 실패! \n\n\t\t현재기록:%dSTAGE 최고기록:%dSTAGE\n\n\t\t\t", Nick, stage, score[count]);
        //PlaySound(TEXT("cry.wav"),NULL,SND_ASYNC|SND_LOOP);
    }
    //printf("count: %d, i:%d",count,i);//오류확인용 
    fclose(fp);
    fp = fopen("SCORE.txt", "wt");
    for (j = 0; j <= i; j++)
        fprintf(fp, "%d\n", score[j]);
    fclose(fp);
    //유저 최고점수를 초기화하고 모든 유저 점수를 재등록함.
    return 0;
}