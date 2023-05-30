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
void CreateEnemy()                              //물방울, 우산 생성
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
void FallEnemy()                               //물방울, 우산 아래로 떨어짐 
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
void DelEnemy(int *cont)                       //물방울, 우산 지면에 닿으면 사라짐
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
int DamagedPlayer(int *life, int *cont, int *end)            //물방울 닿으면 머리카락 빠짐 , 우산 닿으면 머리카락 증가
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
        else if((enemy2[i].con && enemy2[i].y == 0 && (enemy2[i].x == player.x)))  //우산 먹으면 머리카락 증가
        {
           if(*life<3)
              (*life)++;
        }
        else if(*cont == 1000)    // 카운트 300되면 게임클리어
        {
            *end=1;
            return TRUE;
        }
    }
    return FALSE;
}
void MovePlayer()                     // 
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
void PrintGame(int *life, int *cont, int *end)
{
    system("clear");
    gotoxy((WIDTH / 2) - 7, HEIGHT + 2);
    
    printf("\n╭");
    for(int i=0;i<30;i++)
    {
        printf("─");
    }
    printf("╮\n");
    
    printf("│   -춘식이의 산성비 피하기-   │\n");

    if (*life == 3)
        printf("│춘식이 머리카락: 🪶  🪶  🪶      │\n");
    else if (*life == 2)
        printf("│춘식이 머리카락: 🪶  🪶         │\n");
    else if (*life == 1)
        printf("│춘식이 머리카락: 🪶            │\n");


    printf("│비피한 횟수: %3d              │", *cont);                            
    printf("\n╰");
    for(int i=0;i<30;i++)
    {
        printf("─");
    }
    printf("╯\n");



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
    {    
        printf("■");
    
    }
    
   
}
void End(int * end)
{
    system("clear");
    
    if (*end==1)
    {
         printf("\n╭");
        for(int i=0;i<50;i++)
        {
             printf("─");
        }
        printf("╮");
        
        printf("\n│                 \x1b[31m  GAME CLEAR   \x1b[0m                  │\n");
        printf("│&@@@@@@@@@@@@@&##&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@│\n");
        printf("│&@@@@@@@@@@@B7YGPJ?&G555PPGB#&@@@@@@@@@@@@@@@@@@@@│\n");
        printf("│&@@@@@@@@@@P^&\x1b[33m@&&&&&BB\x1b[0m##BBG5YY??J5B&@@@@@@@@@@@@@@│\n");
        printf("│&@@@@@@@@&Y^&\x1b[33m@&&&&&&&&&&&&&&&&&&#\x1b[0mB5J?J?JJ??#@@@@@@│\n");
        printf("│&@@@@@@#??\x1b[33mB&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0mB^5@@@@@│\n");
        printf("│&@@@@B!J\x1b[33m#@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0mP.&555P│\n");
        printf("│@@@&!?\x1b[33m#@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0m!!&@&&│\n");
        printf("│&@B:G\x1b[33m&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&Y\x1b[0m^#@@│\n");
        printf("│5P:#\x1b[33m&&&&&&&&&&&&P^^Y&&&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0m5 Y@│\n");
        printf("│5.#\x1b[33m&&&&&&&####&&J  !&&&&&&&&&&#PP#&&&&&&&&&&&&&\x1b[0m! 5│\n");
        printf("│ \x1b[33mY&&&&&&#\x1b[35mBBBBBBB\x1b[33m#&#BGPPGB#&&&&   ^&&&&&&&&&&&&&#\x1b[0m  │\n");
        printf("│ \x1b[33m#&&&&&\x1b[35mBBBBBBBBG\x1b[33m~~!5BBBG5J??B&#5YB&&&&&&&&&&&&&&\x1b[0m: │\n");
        printf("│.\x1b[33m&&&&&&x\x1b[35mBBBBBBBBB\x1b[0m @@@@@@@@@\x1b[33m#^JGP##B###&&&&&&&&&&\x1b[0m! │\n");
        printf("│ \x1b[33mB&&&&&#\x1b[35mBBBBBBB7\x1b[33m7~7\x1b[0mB&GYB@@@@\x1b[33mJ.JY\x1b[35mBBBBBBB\x1b[33m#&&&&&&&@\x1b[0m! \x1b[0m│\n");
        printf("│.\x1b[33m?&&&&&&&######&&&BJ ?Y~:JYJ^^5#\x1b[35mBBBBBBB\x1b[33m5J?7YP7?P: \x1b[0m│\n");
        printf("│P.\x1b[33mG&&&&&&&&&&&&&&&&&~!7~Y##&&P5\x1b[35mBBBBB#\x1b[33mP~!5G#&#BBY: \x1b[0m│\n");
        printf("│\x1b[33m#G:\x1b[33mP&&&&&&&&&&&&&&&&&##&&&&&&&#\x1b[35mBBBBB\x1b[33m?:G&&G\x1b[35mB&GB&\x1b[33m&&^\x1b[0m│\n");
        printf("│\x1b[33m#&B~7\x1b[33m#&&&&&&&&&&&&JJGB&&&&&&&&&&&#&7^#&&&\x1b[35mP55P##P\x1b[33m#G\x1b[0m│\n");
        printf("│\x1b[33m#&&&Y~?\x1b[33mG&&&&&&&&&&#PYY#&&&&&&&&&&&!~&&&&&B\x1b[35mPP5B\x1b[33m&&&7\x1b[0m│\n");
        printf("│\x1b[33m#&&&&&G775\x1b[33m#&&&&&&&&&&&&&&&&&&&&&#^?&&&&&&&&&&&&&B \x1b[0m│\n");
        printf("│\x1b[33m#&&&&&&&#577\x1b[33mJPB&&&&&&&&&&&&&&&&Y^P&&&&&&&&&&&&&&..\x1b[0m│\n");
        printf("│\x1b[33m#&&&&&&&&&&&G5J77\x1b[33m?YPB#&&&&&&&B~7&&&&&&&&&&&&&&&:\x1b[0m #│\n");
        printf("│\x1b[33mB&&&&&&&&&&&&&&&#BPY?77!!7JY?:\x1b[33mP&&&&&&&&&&&&&&&^\x1b[0m ~@│\n");
 
        printf("╰");
        for(int i=0;i<50;i++)
        {
                printf("─");
        }
        printf("╯\n");
    
    }
    else if(*end==0)
    {
        
        printf("\n╭");
        for(int i=0;i<50;i++)
        {
             printf("─");
        }
        printf("╮");
        
        
        printf("\n│                  \x1b[31mGAME FAILED \x1b[0m                    │\n");
        printf("│@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@│\n");
        printf("│@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#P55P#@@@@@@@@@@@@│\n");
        printf("│@@@@@@@@@#GGB#&#G5YYJJYJJJJJJJJ?YG\x1b[33m##\x1b[0mB7!@@@@@@@@@@@│\n");
        printf("│@@@@@@@&~5BGP\x1b[33m@&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0mJ?&@@@@@@@@@│\n");
        printf("│@@@@@@@:G\x1b[33m@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0m5!5@@@@@@@│\n");
        printf("│@@@@@@G7\x1b[33m&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0mP~5@@@@@│\n");
        printf("│@@@@G~G\x1b[33m@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0m7!@@@@│\n");
        printf("│@@@Y~\x1b[33m@@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0m?~@@@│\n");
        printf("│@@5^\x1b[33m@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0m^Y@@│\n");
        printf("│@&.\x1b[33m&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\x1b[0mB.@@│\n");
        printf("│@J!\x1b[33m@&&&&&&&&&&  &&&&&&&&&BB  &&&&&&&&&&&&&&&&&&\x1b[0m:P@│\n");
        printf("│@~\x1b[33mY&&&&&&&&&&&&   &&&&&&Y   &&&&&&&&&&&&&&&&&&&\x1b[0m!J@│\n");
        printf("│@~\x1b[33mY&&&&&&&&&&&Y75#&&&&&&&&J..5&&&&&&&&&&&&&&&&&\x1b[0m^Y@│\n");
        printf("│@P:\x1b[33m&&&&&&&&&&G.  &&&##&&&&   P&&&&&&&&&&&&&&&&&\x1b[0m.&@│\n");
        printf("│@@:\x1b[33m5&&&&&&&&&#B##JJJYYYJJJBBP#&&&&&&&&&&&&&&&&\x1b[0m?.@@│\n");
        printf("│@@&:\x1b[33mG&&&&&&&&BY7 \x1b[0m#@@@@@@@&\x1b[33m 7G&&&&&&&&&&&&&&&&\x1b[0mJ^5~Y│\n");
        printf("│@@@&^\x1b[33mY&&&&&&&&G: \x1b[0mPBBY?5GB5\x1b[33m :?B&&&&&&&&&&&&&\x1b[0mP~?\x1b[33m&&&\x1b[0m7│\n");
        printf("│@@@@@Y!5\x1b[33m#&&&&&B#&BPGB&BGGB&&&&&&&&&&&&&&\x1b[0mBJ!?#\x1b[33m&&&&&\x1b[0m│\n");
        printf("│@@@@@@@P?75\x1b[33mB&&&&&&&&&&&&&&&&&&&&&&&#\x1b[0mG5J?JP\x1b[33m&&&&&&&&\x1b[0m│\n");
        printf("│@@@@@@@@B:5J??JY5PGGGBBGGGPP5YYJJ??J5G#\x1b[33m&&&&&&&&&\x1b[0m#P│\n");
        printf("│@@@@@@@@7!@\x1b[33m&&&#BG\x1b[0mPP555.!P5PGGBB#\x1b[33m&&&&&&&&&&&&&\x1b[0m#B5YY│\n");
        printf("│@@@@@@@@#:P\x1b[33m&&&&&&&&&&&\x1b[0m.P@\x1b[33m&&&&&&&&&&&&&&&&\x1b[0mGJ!55YY5Y│\n");
        printf("│@@@@@@@@@&7!JB\x1b[33m#&&&&&&&\x1b[0mP:Y#\x1b[33m&&&&&&&&&&\x1b[0m#GY7~~7JYYYYYY│\n");

        printf("╰");
        for(int i=0;i<50;i++)
        {
                printf("─");
        }
        printf("╯\n");
    }
}


void main(void)
{
    int life = 3;
    int cont = 0;
    int end;
    printf("╭");
    for(int i=0;i<55;i++)
    {
        printf("─");
    }
    printf("╮\n");

    printf("│\t\t\t -스토리-                       │\n");
    printf("│급격한 기후 변화와 중국의 산업화와 황사로 인해 오염된  │\n");
    printf("│공기들이 편서풍을 타고 대한민국의 공기를 오염 시켰다!!!│\n");
    printf("│갑자기 하늘이 흐려지고 하늘에선 산성비가 한방울 두방울 │\n");
    printf("│씩 빗물이 떨어지기 시작한다....                        │\n");
    printf("│하지만 우산없이 모험을 나선 춘식이가 남은 세가닥의     │\n");
    printf("│머리카락을 지키기 위해                                 │\n");
    printf("│산성비를 요리 조리 피하게 되는데.....                  │\n");

    printf("╰");
    for(int i=0;i<55;i++)
    {
        printf("─");
    }
    printf("╯\n");
 
    printf("╭");
    for(int i=0;i<55;i++)
    {
        printf("─");
    }
    printf("╮\n");

    printf("│\t\t\t-게임설명-                      │\n");
    printf("│ㆍ산성비를 피하며 춘식의 머리카락을 지켜라!!!          │\n");
    printf("│                                                       │\n");
    printf("│ㆍ조작키 : a - 좌로이동  d - 우로이동                  │\n");
    printf("│                                                       │\n");
    printf("│ㆍ아이템 : ☂️ 를 먹으면 머리카락 증가                   │\n");
    printf("│                                                       │\n");
    printf("│ㆍ비를 피한 회수가 300이상이면 게임 클리어             │\n");
    printf("│                                                       │\n");
    printf("│ㆍ머리카락이(🪶 ) 다 빠지면 게임 실패                   │\n");
    printf("│                                                       │\n");
    printf("│ㆍ시작하려면 Enter를 누르세요                          │\n");

    printf("╰");
    for(int i=0;i<55;i++)
    {
        printf("─");
    }
    printf("╯\n");


    init();
    srand(time(NULL));
    do
    {
        CreateEnemy();
        FallEnemy();
        DelEnemy(&cont);

        MovePlayer();

        PrintGame(&life, &cont, &end);
        usleep(10000);
    } while (!(DamagedPlayer(&life, &cont, &end)));
    
    End(&end);
}
