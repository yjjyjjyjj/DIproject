#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

#define WIDTH 30
#define HEIGHT 15
#define TRUE 1
#define FALSE 0
int j = 3;
int getch() // 엔터를 누르지 않아도 1문자씩 키입력을 받기 위한 함수(wasd)
{
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr); // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);        // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;                     // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0;                    // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); // 터미널에 설정 입력
    c = getchar();                              // 키보드 입력 읽음
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); // 원래의 설정으로 복구
    return c;
}
/*int main()
{
    int c;

    while(1)
    {
    printf("키 넣어 ");
    c=getch();

    if(c==49)
    {
        printf("1이다\n");
    }
    if(c!=49)
    {
        printf("아니다\n");
    }

    }
    return 0;
}*/

typedef struct
{
    int x;
    int y;
    int con;
} Enemy;

typedef struct
{
    int x;
} Player;

void gotoxy(int x, int y)
{
    printf("\033[%d;%df", y, x);
    // getch(stdout);
}

Enemy enemy1[WIDTH];
Enemy enemy2[WIDTH];
Player player;
void init()
{
    int i;
    for (i = 0; i < WIDTH; i++)
        enemy1[i].con = FALSE;
    player.x = WIDTH / 2;
}
void CreateEnemy()
{
    int i;
    for (i = 0; i < WIDTH; i++)
    {
        if (!enemy1[i].con)
        {
            enemy1[i].x = rand() % WIDTH;
            enemy1[i].y = HEIGHT - 1;
            enemy1[i].con = TRUE;
            return;
        }
        else if (enemy1[i].con)
        {
            enemy2[i].x = rand() % WIDTH;
            enemy2[i].y = HEIGHT - 1;
            enemy2[i].con = TRUE;
        }

    }
}
void FallEnemy()
{
    int i;
    int j;
    for (i = 0; i < WIDTH; i++)
    {
        if (enemy1[i].con)
        {
            enemy1[i].y--;
        }
    }
    for(i=0; i<WIDTH; i++)
    {
        if (enemy2[i].con)
        {
            enemy2[i].y--;
        }
    }
}
void DelEnemy(int *cont)
{
    int i;
    for (i = 0; i < WIDTH; i++)
    {
        if (enemy1[i].con && enemy1[i].y < 0)
        {
            enemy1[i].con = FALSE;
            (*cont)++;
        }
        else if (enemy2[i].con && enemy2[i].y < 0)
            enemy2[i].con = FALSE;
    }
}
int DamagedPlayer(int *life, int *cont, int *end)
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if ((enemy1[i].con && enemy1[i].y == 0 && (enemy1[i].x == player.x)))  // 머리카락 0개되면 게임실패
        {
            (*life)--;
            if (*life == 0)
            { 
                *end=0;
                return TRUE;
            }
        }
        else if((enemy2[i].con && enemy2[i].y == 0 && (enemy2[i].x == player.x)))  //우산 먹으면 게임 클리어
        {
            *end=1;
            return TRUE;
        }
        else if(*cont == 500)    // 카운트 500되면 게임클리어
        {
            *end=2;
            return TRUE;
        }
    }
    return FALSE;
}
void MovePlayer()
{
    int c;
    c = getch();
    if (c == 97)
        player.x--;
    if (c == 100)
        player.x++;
    if (player.x < 0)
        player.x = 0;
    if (player.x > WIDTH - 1)
        player.x = WIDTH - 1;
}
void PrintGame(int *life, int *cont)
{
    system("clear");
    gotoxy((WIDTH / 2) - 7, HEIGHT + 2);
    printf("춘식이의 산성비 피하기\n");

    if (*life == 3)
        printf("춘식이 머리카락: 🪶  🪶  🪶\n");
    else if (*life == 2)
        printf("춘식이 머리카락: 🪶  🪶\n");
    else if (*life == 1)
        printf("춘식이 머리카락: 🪶\n");

    printf("비피한 횟수: %d", *cont);                            
    int i;
    for (i = 0; i < WIDTH; i++)
    {
        if (enemy1[i].con)
        {
            gotoxy(enemy1[i].x, HEIGHT - enemy1[i].y);
            printf("💧");
        }
        else if (enemy2[i].con)
        {
            gotoxy(enemy2[i].x, HEIGHT - enemy2[i].y);
            printf("☂️");
        }
    }

    gotoxy(player.x, HEIGHT);
    printf("😺");
    gotoxy(0, HEIGHT + 1);
    for (i = 0; i < WIDTH; i++)
        printf("■");
}
void End(int * end)
{
    system("clear");
    
    if (*end==1)
        printf("우산GAME CLEAR");
    else if (*end==2)
        printf("카운트GAME CLEAR");
    else if(*end==0)
        printf("GAME FAILED");
}


void main(void)
{
    int life = 3;
    int cont = 0;
    int end;
    init();
    srand(time(NULL));
    do
    {
        CreateEnemy();
        FallEnemy();
        DelEnemy(&cont);

        MovePlayer();

        PrintGame(&life, &cont);
        usleep(10000);
    } while (!(DamagedPlayer(&life, &cont, &end)));
    
    End(&end);
}