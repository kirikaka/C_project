#define _CRT_SECURE_NO_WARNINGS
// ���� ���� ó��
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"winmm")
int stage = 5;
char Nick[10];
//����ü Ȱ�� �κ�
typedef struct {
    char x; 
    char y;
    char hp;
}enemy1;
void gotoxy(int x, int y) {
    //COORD ����ü(�ܼ� ȭ��)
    COORD Pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}//�ܼ�â �߽���ǥ�̵� �Լ�
void removeCursor(void)
{
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}//�ܼ�â Ŀ������ �ռ�
int user(void)//ȸ������,�α��� �ռ�
{
    char ID[10], CheckID[10], PW[10], CheckPW[10];
    int num, i = 0;
    char ch;
    int count, success = 0, same = 0;
    FILE* fp;
    removeCursor();
    gotoxy(18, 22);
    printf("ȸ������:R   �α���: �ƹ�Ű�� ��������(R����)\n");
    //�ϳ��� Ű�� �޴� �Լ�
    num = _getch();
    if (num == 'R' || num == 'r') {
    REGISTER://ȸ������
        same = 0;
        system("cls");
        printf("ȸ������ �� ID�Է� : ");
        scanf("%s", ID);
        //ID �ߺ��˻�
        fp = fopen("ID.txt", "rt");
        if (fp != NULL)
        {
            while (feof(fp) == 0)
            {
                //���ڿ�(string) ���� �κ�
                fscanf(fp, "%s", &CheckID);
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
            printf("�ߺ��� ID�Դϴ�. ���Է����ּ���\n");
            system("pause");
            goto REGISTER;
        }
        fp = fopen("ID.txt", "a+t");
        //���Ͽ� �Է��ϱ� ���� fprintf���
        fprintf(fp, "%s\n", ID);
        fclose(fp);
        printf("\nȸ������ �� PW�Է� : ");
        scanf("%s", PW);
        fp = fopen("PW.txt", "a+t");
        fprintf(fp, "%s\n", PW);
        fclose(fp);
        printf("\nȸ������ �� �г����Է� : ");
        scanf("%s", Nick);
        fp = fopen("Nick.txt", "a+t");
        fprintf(fp, "%s\n", Nick);
        fclose(fp);
        printf("\nȸ������ �Ϸ�. �α��� �������� �̵��մϴ�.\n");
        system("pause");
    }
IDINPUT://�α���ID�Է�
    count = 0;
    system("cls");
    printf("�α��� �� ID�Է� : ");
    scanf("%s", ID);
    //���̵� ����Ȯ��
    fp = fopen("ID.txt", "rt");
    while (feof(fp) == 0)
    {
        fscanf(fp, "%s", &CheckID);
        //�Է¹��� ID�� ID.txt�� ����� ������
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
        printf("���̵� Ʋ�Ȱų� �����ϴ�. ȸ������:Y ���̵� �ٽ��Է�:R \n");
        while (1) {
            ch = _getch();
            if (ch == 'y' || ch == 'Y')
                goto REGISTER;
            if (ch == 'R' || ch == 'r')
                goto IDINPUT;
        }
    }
    success = 0;
PWINPUT://��й�ȣ �Է�
    printf("�α��� �� PW�Է� : ");
    scanf("%s", PW);
    fp = fopen("PW.txt", "rt");
    do {
        fscanf(fp, "%s\n", &CheckPW);
        i++;
    } while (i <= count);//���̵� ���ϰ� �� ��ȣ�� ������
    if (strcmp(CheckPW, PW) == 0)
        success = 1;
    //������ ��
    if (success == 0)
    {
        fclose(fp); i = 0;
        printf("��й�ȣ�� Ʋ�Ƚ��ϴ�. ȸ������:Y ��й�ȣ �ٽ��Է�:R\n");
        while (1) {
            ch = _getch();
            if (ch == 'y' || ch == 'Y')
                goto REGISTER;
            if (ch == 'R' || ch == 'r')
                goto PWINPUT;
        }
    }
    fclose(fp);
    //�г��� �Է�
    fp = fopen("Nick.txt", "rt"); i = 0;
    do {
        fscanf(fp, "%s", Nick);
        i++;
    } while (i <= count);
    fclose(fp);

    system("cls");
    printf("%s�� ȯ���մϴ�!\n", Nick);
    return count;
}
//���� ����
int Game(void)
{
    int x1, x2, x = 11, oldx = 11;
    int dx1, dx2, dx = 17, doldx = 17;
    //ȭ�� ����
    int map[21][30] = { 0 };
    int i, j, k = 0, temp, hp = 3;
    clock_t curtime = 0, oldtime;//�ð� ����
    removeCursor();
    for (i = 0; i < 21; i++) {
        map[i][0] = 1;
        map[i][29] = 1;
    }
    gotoxy(0, 0);
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 30; j++) {
            if (map[i][j] == 0) printf("  ");
            else if (map[i][j] == 1) printf("��");
        }printf("\n");
    }
    for (i = 0; i < 4; i++) {
        gotoxy(0, 21 + i);
        printf("��");
        gotoxy(58, 21 + i);
        printf("��");
    }
    map[20][11] = 3;
    map[20][17] = 4;//ĳ���� �����
    //rand�Լ� �ʱ�ȭ
    srand((unsigned)time(NULL));
    removeCursor();
    oldtime = clock();
    system("pause");
    while (1) {
        //��
        gotoxy(2, 0);
        for (i = 0; i < 21; i++) {
            for (j = 1; j < 29; j++) {
                if (map[i][j] == 0) printf("  ");
                else if (map[i][j] == 3) {
                    //���� ����
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                    printf("��");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if (map[i][j] == 4) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    printf("��");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if (map[i][j] == 2) printf("��");
                else if (map[i][j] == 5) printf("��");
                else if (map[i][j] == 6) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    printf("��");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if (map[i][j] == 7) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    printf("��");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
            }gotoxy(2, i + 1);
        }
        gotoxy(60, 2);
        printf("STAGE: %d", stage);
        gotoxy(60, 7);
        printf("HP: %d", hp);
        gotoxy(60, 10);
        printf("���� �ð�: %.2f��", (double)(30 - (clock() - oldtime) / 1000));
        //������Է¿� ���� ĳ������ �����Ӱ� �Ѿ� ����
        //1p,2p
        x1 = x - 1;
        x2 = x + 1;
        oldx = x;
        dx1 = dx - 1;
        dx2 = dx + 1;
        doldx = dx;
        if (_kbhit()) {
            //�Ȱ�ġ��, �������� ����� �ʰ�
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
            //ź�� �߻�
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
        //�Ѿ˰� � �浹��
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
        //�Ѿ� ����� �ӵ�
        if (clock() - oldtime > (1000 - 40 * stage) * k)
        {
            for (i = 0; i < 21; i++) {
                for (j = 0; j < 30; j++) {
                    if (map[i][j] == 2)
                    {   
                        //�Ѿ��� �̵�
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
        //� �ӵ�
        if (clock() - oldtime > (1500 - 50 * stage) * k) {
            for (i = 20; i >= 0; i--) {
                for (j = 0; j < 30; j++) {
                    if (map[i][j] == 5 || map[i][j] == 6 || map[i][j] == 7)
                    {
                        //��� ���� ������� ü�� 1����
                        if (i == 20) {
                            map[i][j] = 0;
                            hp--;
                            continue;
                        }
                        //��ĭ�� �������°� ǥ��
                        temp = map[i][j];
                        map[i][j] = 0;
                        map[i + 1][j] = temp;
                    }
                }
            }
            //�����Լ��� �̿��� ���������� � ����
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
            k++;//�ð����������� ����
        }
        Sleep(30);
        if (hp <= 0)
            return -1;
        if (clock() - oldtime > 30 * 1000)
            return 0;
    }
    return 0;


}
//���� ��Ʈ
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
            if (earthmap[i][j] == 1) printf("��");
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
            else if (map1[i][j] == 1) printf("��");
        }printf("\n  ");
    }
    printf("\n  ");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 36; j++) {
            if (map2[i][j] == 0) printf("  ");
            else if (map2[i][j] == 1) printf("��");
        }printf("\n  ");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    PlaySound(TEXT("main.wav"), NULL, SND_ASYNC | SND_LOOP);//����� ���
    count = user();//ȸ������or�α���,�׸��� ���° ȸ�������� �˾Ƴ�(0��°���� ����)
                //PlaySound(NULL,0,0);//����� ����
                //���� ��ǥ �� ��� ���
    gotoxy(17, 5);
    printf("���� ��ǥ: �������� ����� �ı��Ͽ� ������ ��Ű��!");
    gotoxy(30, 7);
    printf("���� ���");
    gotoxy(4, 9);
    printf("A:�Ķ� ������ �����̵� S:�Ķ� ������ �Ѿ� �߻� D:�Ķ� ������ �����̵�");
    gotoxy(4, 11);
    printf("J:���� ������ �����̵� K:���� ������ �Ѿ� �߻� L:���� ������ �����̵�");
    gotoxy(4, 13);
    printf("�� �: 1LV, ��� �:2LV, ���� �:3LV");
    gotoxy(4, 15);
    printf("�Ѿ˷� ������ ���� 1LV�� ����, 1LV�� �� ������ � �ı�");
    gotoxy(4, 17);
    while (1)
    {
        //â �����
        system("cls");
        for (i = 0; i < 25; i++) {
            for (j = 0; j < 39; j++) {
                printf("��");
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
    }//���� ���� �� ����


    fp = fopen("SCORE.txt", "rt");
    if (fp == NULL) {
        fp = fopen("SCORE.txt", "wt");
        fprintf(fp, "0\n");
        fclose(fp);
    }//���� ó���� �� SCORE�ؽ�Ʈ���� ������ �ʱⰪ �������.
    else fclose(fp);
    fp = fopen("SCORE.txt", "rt");
    i = 0; j = 0;
    while (feof(fp) == 0)
    {
        fscanf(fp, "%d\n", &score[i]);
        i++;
    }//�� ȸ������ ������ �ҷ���,i������ ������� �˾Ƴ�.
    system("cls");//�ܼ�â ����
    gotoxy(15, 10);
    if (score[count] < stage) {//�ְ����϶�
        printf("%s�� �ְ� ��� ���! �ְ���:%dSTAGE\n\n\t\t\t", Nick, stage);
        //PlaySound(TEXT("clap.wav"),NULL,SND_ASYNC|SND_LOOP);
        score[count] = stage;
    }
    else {//�ְ��ϰ���� �ƴҶ�
        printf("%s�� �ְ� ��� ��� ����! \n\n\t\t������:%dSTAGE �ְ���:%dSTAGE\n\n\t\t\t", Nick, stage, score[count]);
        //PlaySound(TEXT("cry.wav"),NULL,SND_ASYNC|SND_LOOP);
    }
    fclose(fp);
    fp = fopen("SCORE.txt", "wt");
    for (j = 0; j <= i; j++)
        fprintf(fp, "%d\n", score[j]);
    fclose(fp);
    //���� �ְ������� �ʱ�ȭ�ϰ� ��� ���� ������ ������.
    return 0;
}