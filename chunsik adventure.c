#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define WIDTH 30
#define HEIGHT 15
#define TRUE 1
#define FALSE 0

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
void CreateEnemy() // 물방울, 우산 생성
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
void FallEnemy() // 물방울, 우산 아래로 떨어짐
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
    for (i = 0; i < WIDTH; i++)
    {
        if (enemy2[i].con)
        {
            enemy2[i].y--;
        }
    }
}
void DelEnemy(int *cont) // 물방울, 우산 지면에 닿으면 사라짐
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
int DamagedPlayer(int *life, int *cont, int *end) // 물방울 닿으면 머리카락 빠짐 , 우산 닿으면 머리카락 증가
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if ((enemy1[i].con && enemy1[i].y == 0 && (enemy1[i].x == player.x))) // 머리카락 0개되면 게임실패
        {
            (*life)--;
            if (*life == 0)
            {
                *end = 0;
                return TRUE;
            }
        }
        else if ((enemy2[i].con && enemy2[i].y == 0 && (enemy2[i].x == player.x))) // 우산 먹으면 머리카락 증가
        {
            if (*life < 3)
                (*life)++;
        }
        else if (*cont == 300) // 카운트 300되면 게임클리어
        {
            *end = 1;
            return TRUE;
        }
    }
    return FALSE;
}
void MovePlayer() //
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
    for (int i = 0; i < 30; i++)
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
    for (int i = 0; i < 30; i++)
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
void End(int *end)
{
    system("clear");

    if (*end == 1)
    {
        printf("\n╭");
        for (int i = 0; i < 50; i++)
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
        for (int i = 0; i < 50; i++)
        {
            printf("─");
        }
        printf("╯\n");
    }
    else if (*end == 0)
    {

        printf("\n╭");
        for (int i = 0; i < 50; i++)
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
        for (int i = 0; i < 50; i++)
        {
            printf("─");
        }
        printf("╯\n");
    }
}
void ending()
{
    system("clear");
    printf("╭");
    for (int i = 0; i < 120; i++)
    {
        printf("─");
    }
    printf("╮\n");
    printf("│\t\x1b[34m                        .:::.         ..                     ......                                              \x1b[0m│\n");
    printf("│\t\x1b[34m                        ^~~!!?J!!!!!!^!!                  ~7~~~~~!!!.             7:                             \x1b[0m│\n");
    printf("│\t\x1b[34m                             7?  .... 7!                  ?!                      Y:                             \x1b[0m│\n");
    printf("│\t\x1b[34m                             J~       ?!                  77                      Y:                             \x1b[0m│\n");
    printf("│\t\x1b[34m             .~~!!~~~^^.     Y^       J! .:.   :^^^.      !Y~!!!!!!...   ..       Y^^ !!~~~^^:                   \x1b[0m│\n");
    printf("│\t\x1b[34m              .:::^^^^^:     Y^       ?!!7!J^ !J^:~J.     7?....... ^? ~7!?~ .7!!~5^. ::^^^^^:                   \x1b[0m│\n");
    printf("│\t\x1b[34m                             Y:       ?P~  :Y^P!~~7!      7?        .J!7. .J^J! .~G^                             \x1b[0m│\n");
    printf("│\t\x1b[34m                            .5:       J7    J7?!::.       7? .       YP.   ~J!?:. Y!                             \x1b[0m│\n");
    printf("│\t\x1b[34m                             7:       7:    :: ^!7~       ^J777!!!!~.~7    .~ :!!!?^                             \x1b[0m│\n");
    printf("│\t\x1b[34m                                                                                                                 \x1b[0m│\n");
    printf("│\t\x1b[33m                       ..                                                                              .:        \x1b[0m│\n");
    printf("│\t\x1b[33m   .^~!!!^      :!     7~          .                               :~~~^:    :.     .~~~!7 ~!!?        ~J        \x1b[0m│\n");
    printf("│\t\x1b[33m   :~~^~~~^     7!     ?~  :^:     ?:  ^~~!^   :~       .?!!!!!?~  :^^~~^.   J:         !J   :Y        ~J        \x1b[0m│\n");
    printf("│\t\x1b[33m   .:^^5J^:   .^57:.   ?^.7!~!7.   J^ ?!:..7!  ~J       ^Y     ??  :!77!^::^~Y.         ^^   :7        ~J        \x1b[0m│\n");
    printf("│\t\x1b[33m   ^!!~~~~!: :!~.^!~.  ?^?~   ?~   Y~ ?7:::7~  ~J       :Y~~~~~Y!  77::!7 ^^!5.      ^~~~~~~~~~:       ~J        \x1b[0m│\n");
    printf("│\t\x1b[33m .^^^^^^^^^^:          ~:Y.   J^   Y~  :^^^:   ~?        :::7:::.  ~7~~7~   :?        ^~~~~~~~~.       ~J        \x1b[0m│\n");
    printf("│\t\x1b[33m  ^~^^:^5^^^: ^!!!!!!!7. ~?^:!?    Y^......... !?          :Y       ^?7!!!!~7^        ?J~~~~~^^:                 \x1b[0m│\n");
    printf("│\t\x1b[33m  .J    !            .5:  .~!~     J:^~~~~!!!~ ~7      :!!!7Y!!!!~. !J    . Y!        ~5~~~~~~~:      :JJ^       \x1b[0m│\n");
    printf("│\t\x1b[33m  J7~~~~~~^.         J:           :.          ..      ...........  .J!!!!!!J:        :Y~~~~~~~^      .7?:        \x1b[0m│\n");
    printf("│\t\x1b[33m   .::::::..          .                                               ....             .........                 \x1b[0m│\n");
    printf("╰");
    for (int i = 0; i < 120; i++)
    {
        printf("─");
    }
    printf("╯\n");

    sleep(1);

    for (int i = 0; i < 4; i++)
    {
        system("clear");
        printf("                   &&&                           GPGB                                \n");
        printf("                &Y7\x1b[33m~~~\x1b[0m!?J?7~^^^:::::::::::::^^^~!~^\x1b[33m:::\x1b[0m^!G                            \n");
        printf("               &7:\x1b[33m:::::::::::::::\x1b[0m^^^^^^^^^\x1b[33m::::::::::^::\x1b[0m:^#                           \n");
        printf("               P^:\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:J#                          \n");
        printf("             &P!^:\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:~Y#                        \n");
        printf("            B7::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:::~5                       \n");
        printf("           5^::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^::J&                     \n");
        printf("          Y::\x1b[33m^^^^^^^^^^^^^\x1b[0m::::\x1b[33m^^^^^^^^^^^^^^\x1b[0m::::\x1b[33m^^^^^^^^^^^^^\x1b[0m^::7&                    \n");
        printf("         5::\x1b[33m^^^^^^^^^^^^^\x1b[0m:^~~\x1b[0m::\x1b[33m^^^^^^^^^^^^\x1b[0m:~7!^\x1b[0m:\x1b[33m^^^^^^^^^^^^^^\x1b[0m^:?                    \n");
        printf("        #~:\x1b[33m^^^^^^^^^^^^\x1b[0m::!B&&P^\x1b[0m:\x1b[33m^^^^^^^^^^\x1b[0m:?&@@B!\x1b[0m:::::\x1b[33m^^^^^^^^^\x1b[0m^:^P                   \n");
        printf("        ?::\x1b[33m^^^^^^^\x1b[0m:::::::!#&&G^\x1b[0m::::::::::::~PBBJ^\x1b[0m:^^^^:::\x1b[33m^^^^^^^\x1b[0m^:!                   \n");
        printf("       #!:\x1b[33m^^^^^^^\x1b[0m::\x1b[35m^^~~~~^^\x1b[0m~^:::^!7?JJJ?7!^::::^~~\x1b[35m!!!!~~\x1b[0m^::\x1b[33m^^^^^\x1b[0m^:~#                  \n");
        printf("       #~:\x1b[33m^^^^^^\x1b[0m:^\x1b[35m~!!!!!!!\x1b[0m?J!^75BPYYJJJYYPB5!75P?\x1b[35m!!!!!!!!~\x1b[0m^^\x1b[33m^^^^\x1b[0m^:^B                  \n");
        printf("       #~:\x1b[33m^^^^^\x1b[0m:^\x1b[35m!!!!!!!!!\x1b[0m?PG#&J:         ^P #YJ7\x1b[35m!!!!!!!!!\x1b[0m^:\x1b[33m^^^^\x1b[0m^:^B                  \n");
        printf("       #!:\x1b[33m^^^^\x1b[0m^:~\x1b[35m!!!!!!!!!!!!\x1b[0m&G     .:     ~ #?7\x1b[35m!!!!!!!!!!\x1b[0m^:\x1b[33m^^^^\x1b[0m^:^#                  \n");
        printf("        7::\x1b[33m^^^^\x1b[0m:^\x1b[35m!!!!!!!!!\x1b[0m?GBB#57!!?B#P?7?JBGYGBJ\x1b[35m!!!!!!!!\x1b[0m~^^\x1b[33m^^^^\x1b[0m^:~&                  \n");
        printf("        B^:\x1b[33m^^^^^\x1b[0m:^\x1b[35m~!!!!!!!\x1b[0m7?~:~?5P& PYG BJ?!::^~~~\x1b[35m!!!!~\x1b[0m~^::\x1b[33m^^^^^\x1b[0m^:5                   \n");
        printf("         Y::\x1b[33m^^^^\x1b[0m::^^^~~~~^^:::::::!GBGB5~::::\x1b[33m^:::\x1b[0m^^^^^:::\x1b[33m^^^^\x1b[0m:::? &    &######&      \n");
        printf("          J::\x1b[33m^^^^^::::::::::\x1b[33m^^^^^^::^~^::^^^^^^^^::::::^^^\x1b[0m:::^!Y&&GPY?!~^^^^^^!JB    \n");
        printf("           5^::\x1b[33m^^^^^^^^^^^^^^^^^^^^:::::^^^^^^^^^^^^^^^\x1b[0m:::^7YGG5?~^::::\x1b[33m:::::::\x1b[0m::^P   \n");
        printf("            #?^:::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m:::!5BBY!^::::\x1b[33m^^^^^^^^^^^^^\x1b[0m:~B  \n");
        printf("              BY!^:::\x1b[33m:::^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m::::^?GB5!^::::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::!B  \n");
        printf("                &B5?!^^::::\x1b[33m::::::::::::::::::::\x1b[0m:::^!YBG?^:::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::::^?B   \n");
        printf("                   & BGPYJ?7!!~~~~^^^^~~~~!!7??J5PGBP!:::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::::^!YB     \n");
        printf("                  #P?~~7JJYYPPGBBGGGGGGBBGGP5YYJ?!~^:::\x1b[33m^^^^^^^^^^^^^^\x1b[0m::::~75#        \n");
        printf("               #P?~:::\x1b[33m::::::::^^^^^^^^^^^^:::::::::::\x1b[33m^^^^^^^^^^^^^^\x1b[0m:::~JP&           \n");
        printf("       &##BGPJ7^:::\x1b[33m:^^^^^^^::::::::::::::::::^^^^^^^^^^^^^^^^^^^\x1b[0m:::~?P&              \n");
        printf("  B5J?!~^^^:::\x1b[33m:::^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m::~5#                 \n");
        printf("B7^:::::\x1b[33m:::::^^^^^^::::^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m:^Y&                   \n");
        printf("?::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m:^77^:^\x1b[33m^^^^:::::::::::::::::::::::::::::::\x1b[0m::~G                     \n");
        printf("J::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m:!#P^::\x1b[33m:::::^^^^^^~~~~~~~~~~~~~~~~~~~^^^^^\x1b[0m^^G                      \n");
        printf("#?^:::\x1b[33m:::::::::::\x1b[0m::7 5~~!!!777?JJJJJJJJJJJJJJJJJJJJJJJJJJJJJ?5&                      \n");
        printf("  BY7~^^::\x1b[33m:::\x1b[0m^^^~775 PJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJG                       \n");
        printf("     &#GGGPGGGB#&    PJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJB                       \n");
        printf("                     GJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJYB                       \n");
        printf("                     GJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJB                       \n");
        printf("                     #JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ5#                       \n");
        printf("                     &GGPP5YYYYYYYYYYYYYYYYYYYYY55PGGGBB##&&                         \n");

        usleep(250000);
        system("clear");
        printf("                             &&&                           GPGB                                \n");
        printf("                          &Y7\x1b[33m~~~\x1b[0m!?J?7~^^^:::::::::::::^^^~!~^\x1b[33m:::\x1b[0m^!G                            \n");
        printf("                         &7:\x1b[33m:::::::::::::::\x1b[0m^^^^^^^^^\x1b[33m::::::::::^::\x1b[0m:^#                           \n");
        printf("                         P^:\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:J#                          \n");
        printf("                       &P!^:\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:~Y#                        \n");
        printf("                      B7::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^:::~5                       \n");
        printf("                     5^::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m^::J&                     \n");
        printf("                    Y::\x1b[33m^^^^^^^^^^^^^\x1b[0m::::\x1b[33m^^^^^^^^^^^^^^\x1b[0m::::\x1b[33m^^^^^^^^^^^^^\x1b[0m^::7&                    \n");
        printf("                   5::\x1b[33m^^^^^^^^^^^^^\x1b[0m:^~~\x1b[0m::\x1b[33m^^^^^^^^^^^^\x1b[0m:~7!^\x1b[0m:\x1b[33m^^^^^^^^^^^^^^\x1b[0m^:?                    \n");
        printf("                  #~:\x1b[33m^^^^^^^^^^^^\x1b[0m::!B&&P^\x1b[0m:\x1b[33m^^^^^^^^^^\x1b[0m:?&@@B!\x1b[0m:::::\x1b[33m^^^^^^^^^\x1b[0m^:^P                   \n");
        printf("                  ?::\x1b[33m^^^^^^^\x1b[0m:::::::!#&&G^\x1b[0m::::::::::::~PBBJ^\x1b[0m:^^^^:::\x1b[33m^^^^^^^\x1b[0m^:!                   \n");
        printf("                 #!:\x1b[33m^^^^^^^\x1b[0m::\x1b[35m^^~~~~^^\x1b[0m~^:::^!7?JJJ?7!^::::^~~\x1b[35m!!!!~~\x1b[0m^::\x1b[33m^^^^^\x1b[0m^:~#                  \n");
        printf("                 #~:\x1b[33m^^^^^^\x1b[0m:^\x1b[35m~!!!!!!!\x1b[0m?J!^75BPYYJJJYYPB5!75P?\x1b[35m!!!!!!!!~\x1b[0m^^\x1b[33m^^^^\x1b[0m^:^B                  \n");
        printf("                 #~:\x1b[33m^^^^^\x1b[0m:^\x1b[35m!!!!!!!!!\x1b[0m?PG#&J:         ^P #YJ7\x1b[35m!!!!!!!!!\x1b[0m^:\x1b[33m^^^^\x1b[0m^:^B                  \n");
        printf("                 #!:\x1b[33m^^^^\x1b[0m^:~\x1b[35m!!!!!!!!!!!!\x1b[0m&G     .:     ~ #?7\x1b[35m!!!!!!!!!!\x1b[0m^:\x1b[33m^^^^\x1b[0m^:^#                  \n");
        printf("                  7::\x1b[33m^^^^\x1b[0m:^\x1b[35m!!!!!!!!!\x1b[0m?GBB#57!!?B#P?7?JBGYGBJ\x1b[35m!!!!!!!!\x1b[0m~^^\x1b[33m^^^^\x1b[0m^:~&                  \n");
        printf("                  B^:\x1b[33m^^^^^\x1b[0m:^\x1b[35m~!!!!!!!\x1b[0m7?~:~?5P& PYG BJ?!::^~~~\x1b[35m!!!!~\x1b[0m~^::\x1b[33m^^^^^\x1b[0m^:5                   \n");
        printf("       &######&    & ?:::\x1b[33m^^^^:::^^^^^:::^::::~5BGBG!:::::::^^~~~~^^^::^^^^\x1b[0m::Y             \n");
        printf("     BJ!^^^^^^~!?YPG&&Y!^:::\x1b[33m^^^::::::^^^^^^^^::^~^::^^^^^^::::::::::^^^^^\x1b[0m::J              \n");
        printf("    P^::\x1b[33m::::::::\x1b[0m:::^~?5GGY7^:::\x1b[33m^^^^^^^^^^^^^^^:::::^^^^^^^^^^^^^^^^^^^^\x1b[0m::^5               \n");
        printf("   B~:\x1b[33m^^^^^^^^^^^^^\x1b[0m::::^!YBB5!:::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\x1b[0m:::^?#                \n");
        printf("   B!::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::::^!5BG?^::::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^:::\x1b[0m:::^!YB                  \n");
        printf("    B?^::::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m:::^?GBY!^::::\x1b[33m:::::::::::::::::::\x1b[0m::::^^!?5B&                    \n");
        printf("      BY!^::::\x1b[33m^^^^^^^^^^^^^^^\x1b[0m:::!PBGP5J??7!!~~~~^^^^~~~~!!7?JYPGB &                       \n");
        printf("         #57~::::\x1b[33m^^^^^^^^^^^^^^\x1b[0m:::^~!?JYY5PGGBBGGGGGGBBGPPYYJJ7~~?P#                      \n");
        printf("            &PJ~:::\x1b[33m^^^^^^^^^^^^^^\x1b[0m:::::::::::^^^^^^^^^^^^::::::::\x1b[0m:::~?P#                   \n");
        printf("               &P?~:::\x1b[33m^^^^^^^^^^^^^^^^^^^::::::::::::::::::^^^^^^^:\x1b[0m:::^7JPGB##&           \n");
        printf("                  #5~::\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^:::\x1b[0m:::^^^~!?J5B      \n");
        printf("                    &Y^:\x1b[33m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^::::^^^^^^:::::\x1b[0m:::::^7B    \n");
        printf("                      G~::\x1b[33m:::::::::::::::::::::::::::::::^^^^\x1b[0m^:^77^:\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::?    \n");
        printf("                       G^^\x1b[33m^^^^^~~~~~~~~~~~~~~~~~~~^^^^^^:::::\x1b[0m::^P#!:\x1b[33m^^^^^^^^^^^^^^^\x1b[0m::J    \n");
        printf("                       &5?JJJJJJJJJJJJJJJJJJJJJJJJJJJJJ?777!!!~~5 7::\x1b[33m:::::::::::::\x1b[0m:^?#    \n");
        printf("                        GJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJP 577~^^^\x1b[33m:::::\x1b[0m^^~7YB      \n");
        printf("                        BJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJP    &#BGGGPGGG#&         \n");
        printf("                        BYJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJG                         \n");
        printf("                        BJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJG                         \n");
        printf("                        #5JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ#                         \n");
        printf("                          &&##BBGGGP55YYYYYYYYYYYYYYYYYYYYY5PPGG&                         \n");
        usleep(250000);
    }

    sleep(1);
    system("clear");

    printf("╭");
    for (int i = 0; i < 120; i++)
    {
        printf("─");
    }
    printf("╮\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│\t\t\t\t\t\t      - 만든 사람 -                                                      │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│\t\t\t\t\t\t양  정  주( ♥  공 주 ♥  )                                                │\n");
    usleep(50000);
    printf("│\t\t\t\t\t\t이  시  영(  시  녀  1  )                                                │\n");
    usleep(50000);
    printf("│\t\t\t\t\t\t유  미  유(  시  녀  2  )                                                │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);
    printf("│                                                                                                                        │\n");
    usleep(50000);

    printf("╰");
    for (int i = 0; i < 120; i++)
    {
        printf("─");
    }
    printf("╯\n");
}
void start()
{
    printf("╭");
    for (int i = 0; i < 104; i++)
    {
        printf("─");
    }
    printf("╮\n");
    printf("│                                                                                                        │\n");
    printf("│                                                                                                        │\n");
    printf("│\t\t\t\x1b[33m     :^^:    :   ^                           .::.  .                             \x1b[0m│\n");
    printf("│\t\t\t\x1b[33m     .^~7~.  :7   7 :^:  ~:.^^^. ~.    .!^^~! :!!^. !.                           \x1b[0m│\n");
    printf("│\t\t\t\x1b[33m    .^~7~^ :~~^  7~~.!: !^!~.!^ ?.    :7::~? ~!~~:^J.                            \x1b[0m│\n"); // 50
    printf("│\t\t\t\x1b[33m    ^~^~~^:.::::::7: 7: !^ :::  7.     :^~.. ^~!!..!                             \x1b[0m│\n");
    printf("│\t\t\t\x1b[33m    ^^ ^^  .::::?:.~~^  !^^^^^^.!     :^!7^^: ?^::~7                             \x1b[0m│\n");
    printf("│\t\t\t\x1b[33m    :!^^^^.     ~.      ..      .     ....... ^^^^~^                             \x1b[0m│\n");
    printf("│                                                                                                        │\n");
    printf("│                                                                                                        │\n");
    printf("│                                                                                                        │\n");
    printf("╰");
    for (int i = 0; i < 104; i++)
    {
        printf("─");
    }
    printf("╯\n");

    usleep(600000);
    system("clear");

    printf("╭");
    for (int i = 0; i < 104; i++)
    {
        printf("─");
    }
    printf("╮\n");
    printf("│                                                                                                        │\n");
    printf("│\t\t\x1b[34m      .....            :                                                                 \x1b[0m│\n");
    printf("│\t\t\x1b[34m     .^~~~~.     7.   :?         ^.  ...    .       ::::::. .^~~~:   ^:                  \x1b[0m│\n");
    printf("│\t\t\x1b[34m     .~^~Y!^.   ~J.   :? :!!!.   J:.!~^~!. .?      :J^^^:?7 .^!!!^:..?^                 \x1b[0m │\n");
    printf("│\t\t\x1b[34m     .~~~7~~: :~~~!~  :?^7. :?   J:^?:.:?^ :J      :J::::?7 .7~^!~.~~5:                 \x1b[0m │\n");
    printf("│\t\t\x1b[34m    :~~^^^^^^: ...... .^7~  :J   J: .^^^.  :J       ::!~::. .7~~7~   7.                 \x1b[0m │\n"); // 70
    printf("│\t\t\x1b[34m    .!:..!7.:. ^~~~~~!7 .!!~7:   J::^^^^^^.:J      .. ?!....  ?~~^^^!7                  \x1b[0m │\n");
    printf("│\t\t\x1b[34m     ?~..:^..        ^J   .:.    !.:::::::..~     .~~~!!~~~^  J^::::77                  \x1b[0m │\n");
    printf("│\t\t\x1b[34m     :~^^^^^:.       .^                                       .^:::::.                  \x1b[0m │\n");
    printf("│                                                                                                        │\n");
    printf("│                                                                                                        │\n");

    printf("╰");
    for (int i = 0; i < 104; i++)
    {
        printf("─");
    }
    printf("╯\n");

    usleep(600000);
    system("clear");

    printf("╭");
    for (int i = 0; i < 104; i++)
    {
        printf("─");
    }
    printf("╮\n");
    printf("│\x1b[32m        ......                 .:                                                                       \x1b[0m│\n");
    printf("│\x1b[32m       ^~!!77!:        ?~      7J             :.                                     .!!!!!~.     ~.    \x1b[0m│\n");
    printf("│\x1b[32m      .^^^^^^^^^.     .5:      7?    ::       J^   :~!!~.    :~         .?7777777?:  .::^^^^:.   .Y.    \x1b[0m│\n");
    printf("│\x1b[32m      .^^^:7G~^^      7P:      ??  !?77?^     Y! .7?~::^J~   !Y         ^P:.....:P~  :~!777!~:...^5.    \x1b[0m│\n");
    printf("│\x1b[32m      .^~!7JY7!!^  :!77!?7!.   ?7 J7.  :5:    5! ~5.    7J   7Y         ^P......:G^   ~77!77..!77Y5     \x1b[0m│\n");
    printf("│\x1b[32m      .~^:.   .^:  ::    .:.   ?!^5     Y~    5!  ~?7!!77:   7J         .J?77777?J:  ^P^  .57    !Y     \x1b[0m│\n");
    printf("│\x1b[32m    .~!!!!!!!7!~!!.  ....      :.~5    :5:    5!    ....     7J             ^?        ~7!!7!.    ~7     \x1b[0m│\n");
    printf("│\x1b[32m     .^^:::.?Y::::. ~777777777J.  7J~::Y7     5! ..........  7?             !J         ~?77777777?:     \x1b[0m│\n");
    printf("│\x1b[32m      J!    ^7               :P:   :!77^      5^:!!77777777: ?7        ^!!!~J5!!!!!~.  JJ       :P^     \x1b[0m│\n");
    printf("│\x1b[32m      7Y:::::::::.           :P:              !.             ^:        :^^^^^^^^^^^:.  ~5~~~~~~~?5.     \x1b[0m│\n");
    printf("│\x1b[32m      .!!!!!!!!~~:           .!.                                                        ^~^^^^^^:.      \x1b[0m│\n");

    printf("╰");
    for (int i = 0; i < 104; i++)
    {
        printf("─");
    }
    printf("╯\n");
    sleep(1);

    system("clear");
    printf("╭");
    for (int i = 0; i < 104; i++)
    {
        printf("─");
    }
    printf("╮\n");
    printf("│                                      ^5GBBG5!::::::::..                                                │\n");
    printf("│                                    .B&J^::^?GBGGGPGGGGGBBBGY7^.                                        │\n");
    printf("│                                   7&&^..................:^~?5G#B5!~!7!^.                               │\n");
    printf("│                                .5&B7...........................^?PPYY5G&G.                             │\n");
    printf("│                              .P&G^.....................................^&&                             │\n");
    printf("│                             J@B^........................................5@:                            │\n");
    printf("│                           .#&7..........................................!@G                            │\n");
    printf("│                          :@#:..........:5&&5.............................~@B                           │\n");
    printf("│                         .@#............:#@@B..........:?P5^...............7@Y                          │\n");
    printf("│                         B@^...........:..:^:^^^:......!@@@G................G@.                         │\n");
    printf("│                        ^@Y...........:G&PGBBGGGBBBP?:..^7!:................~@Y                         │\n");
    printf("│                        Y@~.............#@!       .!P&PJY!..................:&#                         │\n");
    printf("│                        G@:...........JB@@!...::     J@G?~...................#&                         │\n");
    printf("│                        P@^...........:^:?GBBBB#B5?75&@G^...................:&#                         │\n");
    printf("│                        ~@J.....................^7JJ?^~57...................!@J                         │\n");
    printf("│                      .:~&@^................................................B@.                         │\n");
    printf("│                  .?GBBGPP&&~..............................................J@?                          │\n");
    printf("│                .G&G!:....:G@5:...........................................?@5                           │\n");
    printf("│               ~&B:.........!B&P~........................................5@Y                            │\n");
    printf("│           ^&5!@@P5PP5J!^.....~5##P7:..................................7##^                             │\n");
    printf("│       .G&##&&##BGGGGB#&&#5~.....~YB#BPJ!^:..............:^~7JY55PPPPG&@&?:.                            │\n");
    printf("│       Y@GYYJJJJJJJJJJJJYP@@7.......:^?5GB#BBG5YJ?7!!!YGB#BGPYJ?77!!!!77?5GB#P^                         │\n");
    printf("│       ?@GJJJJJJJJJJJJJJJG@P..............:^~!?JY5PPGG57^:..................^Y&B.                       │\n");
    printf("│       :@#JJJJJJJJJJJJJJG@P...................................................^@G                       │\n");
    printf("│       :#@PJJJJJJJJJJJJP@#~^^::::..............................................&&                       │\n");
    printf("│       JYB@BJJJJJJJJJJ5@@YJJJJJJ??7!!~^^::....................................Y@?                       │\n");
    printf("│        .G&@&PJJY5GBB#@@5JJJJJJJJJJJJJJJJJ??7!~^::..............:^^~~~^^^~~75##!                        │\n");
    printf("│         . .?#&&&&#BBGG5JJJJJJJJJJJJJJJJJJJJJJJJJJ?7!~^:......G&BGPPPPPGGGPY7:                          │\n");
    printf("│             ?@#5JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ???~^?@J                                        │\n");
    printf("│            .&&JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ&@!                                        │\n");
    printf("│            .&&JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJY@@&&#5:                                    │\n");
    printf("│             7@#YJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJBBJY5#@5                                   │\n");
    printf("│              ^B&&BPYYJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJB@~                                  │\n");
    printf("│                .!5G##&###########BBBGP5YJJJJJJJJJJJJJJJJJJJJJJJJJJB@~                                  │\n");
    printf("│                      ..::^^^~~~~~!7J5PB#&&#G5YJJJJJJJJJJJJJJJJJJJG@G         !!!!!       !!!!!         │\n");
    printf("│                                         .^?PB#&##BGPP55YYYYYY5PB&&J       !!! 춍 !!!   !!! 춍 !!!      │\n");
    printf("│                                               .^!?YPGBB######BGY~            !!!!!       !!!!!         │\n");
    printf("│                                                                                                        │\n");
    printf("│                                            잘자란 춘식이...                                            │\n");
    printf("│                         어느날 바람에 날아온 잡지가 춘식이의 얼굴을 강타하였다.                        │\n");
    printf("│                                     툭 떨어진 잡지를 보게된 춘식이                                     │\n");
    printf("│                              새로운 세상을 보게된 춘식이는 모험을 떠난다....                           │\n");

    printf("╰");
    for (int i = 0; i < 104; i++)
    {
        printf("─");
    }
    printf("╯\n");
    sleep(2);
}

void gullmove(int *gh_x, int *gh_y, int arr[][30], int x, int y, int *a) // 유령 좌표바꿔주기.
{
    if (*gh_x > x) // 유령이 더 아래
    {
        if (*gh_y < y) // 유령이 더 왼쪽
        {
            if (arr[*gh_x - 1][*gh_y] == 0 || arr[*gh_x - 1][*gh_y] == 3) // 위
            {

                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x - 1][*gh_y]; // a도 함수의 인자로. 포인트인자.
                arr[*gh_x - 1][*gh_y] = 5;

                *gh_x -= 1;
            }
            else if (arr[*gh_x][*gh_y + 1] == 0 || arr[*gh_x][*gh_y + 1] == 3) // 오
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y + 1];
                arr[*gh_x][*gh_y + 1] = 5;
                *gh_y += 1;
            }
            else if (arr[*gh_x + 1][*gh_y] == 0 || arr[*gh_x + 1][*gh_y] == 3) // 아래
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x + 1][*gh_y];
                arr[*gh_x + 1][*gh_y] = 5;
                *gh_x += 1;
            }
            else if (arr[*gh_x][*gh_y - 1] == 0 || arr[*gh_x][*gh_y - 1] == 3) // 왼
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y - 1];
                arr[*gh_x][*gh_y - 1] = 5;
                *gh_y -= 1;
            }
        }
        else if (*gh_y > y) // 유령이 더 오른쪽
        {
            if (arr[*gh_x - 1][*gh_y] == 0 || arr[*gh_x - 1][*gh_y] == 3) // 위
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x - 1][*gh_y]; // a도 함수의 인자로. 포인트인자.
                arr[*gh_x - 1][*gh_y] = 5;

                *gh_x -= 1;
            }
            else if (arr[*gh_x][*gh_y - 1] == 0 || arr[*gh_x][*gh_y - 1] == 3) // 왼
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y - 1];
                arr[*gh_x][*gh_y - 1] = 5;
                *gh_y -= 1;
            }

            else if (arr[*gh_x][*gh_y + 1] == 0 || arr[*gh_x][*gh_y + 1] == 3) // 오
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y + 1];
                arr[*gh_x][*gh_y + 1] = 5;
                *gh_y += 1;
            }
            else if (arr[*gh_x + 1][*gh_y] == 0 || arr[*gh_x + 1][*gh_y] == 3) // 아래
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x + 1][*gh_y];
                arr[*gh_x + 1][*gh_y] = 5;
                *gh_x += 1;
            }
        }
        else // y가 같다
        {
            if (arr[*gh_x - 1][*gh_y] == 0 || arr[*gh_x - 1][*gh_y] == 3) // 위
            {

                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x - 1][*gh_y];
                // a도 함수의 인자로. 포인트인자.
                arr[*gh_x - 1][*gh_y] = 5;

                *gh_x -= 1;
            }
            else if (arr[*gh_x + 1][*gh_y] == 0 || arr[*gh_x + 1][*gh_y] == 3) // 아래
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x + 1][*gh_y];
                arr[*gh_x + 1][*gh_y] = 5;
                *gh_x += 1;
            }
            else if (arr[*gh_x][*gh_y - 1] == 0 || arr[*gh_x][*gh_y - 1] == 3) // 왼
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y - 1];
                arr[*gh_x][*gh_y - 1] = 5;

                *gh_y -= 1;
            }

            else if (arr[*gh_x][*gh_y + 1] == 0 || arr[*gh_x][*gh_y + 1] == 3) // 오
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y + 1];
                arr[*gh_x][*gh_y + 1] = 5;
                *gh_y += 1;
            }
            else if (arr[*gh_x + 1][*gh_y] == 0 || arr[*gh_x + 1][*gh_y] == 3) // 아래
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x + 1][*gh_y];
                arr[*gh_x + 1][*gh_y] = 5;
                *gh_x += 1;
            }
        }
    }
    else if (*gh_x < x) // 유령이 더 위.
    {
        if (*gh_y < y) // 유령이 더 왼쪽
        {

            if (arr[*gh_x][*gh_y + 1] == 0 || arr[*gh_x][*gh_y + 1] == 3) // 오
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y + 1];
                arr[*gh_x][*gh_y + 1] = 5;
                *gh_y += 1;
            }
            else if (arr[*gh_x + 1][*gh_y] == 0 || arr[*gh_x + 1][*gh_y] == 3) // 아래
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x + 1][*gh_y];
                arr[*gh_x + 1][*gh_y] = 5;
                *gh_x += 1;
            }
            else if (arr[*gh_x][*gh_y - 1] == 0 || arr[*gh_x][*gh_y - 1] == 3) // 왼
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y - 1];
                arr[*gh_x][*gh_y - 1] = 5;
                *gh_y -= 1;
            }
            else if (arr[*gh_x - 1][*gh_y] == 0 || arr[*gh_x - 1][*gh_y] == 3) // 위
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x - 1][*gh_y]; // a도 함수의 인자로. 포인트인자.
                arr[*gh_x - 1][*gh_y] = 5;

                *gh_x -= 1;
            }
        }
        else if (*gh_y > y) // 유령 오른쪽

        {

            if (arr[*gh_x + 1][*gh_y] == 0 || arr[*gh_x + 1][*gh_y] == 3) // 아래
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x + 1][*gh_y];
                arr[*gh_x + 1][*gh_y] = 5;
                *gh_x += 1;
            }
            else if (arr[*gh_x][*gh_y - 1] == 0 || arr[*gh_x][*gh_y - 1] == 3) // 왼
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y - 1];
                arr[*gh_x][*gh_y - 1] = 5;
                *gh_y -= 1;
            }
            else if (arr[*gh_x][*gh_y + 1] == 0 || arr[*gh_x][*gh_y + 1] == 3) // 오
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y + 1];
                arr[*gh_x][*gh_y + 1] = 5;
                *gh_y += 1;
            }

            else if (arr[*gh_x - 1][*gh_y] == 0 || arr[*gh_x - 1][*gh_y] == 3) // 위
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x - 1][*gh_y]; // a도 함수의 인자로. 포인트인자.
                arr[*gh_x - 1][*gh_y] = 5;

                *gh_x -= 1;
            }
        }
        else // y같
        {
            if (arr[*gh_x + 1][*gh_y] == 0 || arr[*gh_x + 1][*gh_y] == 3) // 아래
            {

                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x + 1][*gh_y];
                arr[*gh_x + 1][*gh_y] = 5;
                *gh_x += 1;
            }
            else if (arr[*gh_x][*gh_y - 1] == 0 || arr[*gh_x][*gh_y - 1] == 3) // 왼
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y - 1];
                arr[*gh_x][*gh_y - 1] = 5;
                *gh_y -= 1;
            }
            else if (arr[*gh_x][*gh_y + 1] == 0 || arr[*gh_x][*gh_y + 1] == 3) // 오
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y + 1];
                arr[*gh_x][*gh_y + 1] = 5;
                *gh_y += 1;
            }

            else if (arr[*gh_x - 1][*gh_y] == 0 || arr[*gh_x - 1][*gh_y] == 3) // 위
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x - 1][*gh_y]; // a도 함수의 인자로. 포인트인자.
                arr[*gh_x - 1][*gh_y] = 5;

                *gh_x -= 1;
            }
        }
    }
    else // 같은행
    {
        if (*gh_y < y) // 유령이 더 왼쪽
        {

            if (arr[*gh_x][*gh_y + 1] == 0 || arr[*gh_x][*gh_y + 1] == 3) // 오
            {

                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y + 1];
                arr[*gh_x][*gh_y + 1] = 5;
                *gh_y += 1;
            }

            else if (arr[*gh_x][*gh_y - 1] == 0 || arr[*gh_x][*gh_y - 1] == 3) // 왼
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y - 1];
                arr[*gh_x][*gh_y - 1] = 5;
                *gh_y -= 1;
            }
            else if (arr[*gh_x - 1][*gh_y] == 0 || arr[*gh_x - 1][*gh_y] == 3) // 위
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x - 1][*gh_y]; // a도 함수의 인자로. 포인트인자.
                arr[*gh_x - 1][*gh_y] = 5;

                *gh_x -= 1;
            }
            else if (arr[*gh_x + 1][*gh_y] == 0 || arr[*gh_x + 1][*gh_y] == 3) // 아래
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x + 1][*gh_y];
                arr[*gh_x + 1][*gh_y] = 5;
                *gh_x += 1;
            }
        }
        else if (*gh_y > y) // 유령 오른쪽

        {
            if (arr[*gh_x][*gh_y - 1] == 0 || arr[*gh_x][*gh_y - 1] == 3) // 왼
            {

                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y - 1];
                arr[*gh_x][*gh_y - 1] = 5;
                *gh_y -= 1;
            }
            else if (arr[*gh_x][*gh_y + 1] == 0 || arr[*gh_x][*gh_y + 1] == 3) // 오
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x][*gh_y + 1];
                arr[*gh_x][*gh_y + 1] = 5;
                *gh_y += 1;
            }

            else if (arr[*gh_x - 1][*gh_y] == 0 || arr[*gh_x - 1][*gh_y] == 3) // 위
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x - 1][*gh_y]; // a도 함수의 인자로. 포인트인자.
                arr[*gh_x - 1][*gh_y] = 5;

                *gh_x -= 1;
            }
            else if (arr[*gh_x + 1][*gh_y] == 0 || arr[*gh_x + 1][*gh_y] == 3) // 아래
            {
                arr[*gh_x][*gh_y] = *a;
                *a = arr[*gh_x + 1][*gh_y];
                arr[*gh_x + 1][*gh_y] = 5;
                *gh_x += 1;
            }
        }
    }
}
void key(int i)
{
    char key[15][17] = {{'3', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '4'},
                        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                        {'1', '0', '0', '0', '0', '0', '3', '2', '2', '2', '4', '0', '0', '0', '0', '0', '1'},
                        {'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
                        {'1', '0', '0', '0', '0', '0', '1', '0', 'w', '0', '1', '0', '0', '0', '0', '0', '1'},
                        {'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
                        {'1', '0', '0', '0', '0', '0', '6', '2', '2', '2', '5', '0', '0', '0', '0', '0', '1'},
                        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                        {'1', '3', '2', '2', '2', '4', '3', '2', '2', '2', '4', '3', '2', '2', '2', '4', '1'},
                        {'1', '1', '0', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '0', '1', '1'},
                        {'1', '1', '0', 'a', '0', '1', '1', '0', 's', '0', '1', '1', '0', 'd', '0', '1', '1'},
                        {'1', '1', '0', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '0', '1', '1'},
                        {'1', '6', '2', '2', '2', '5', '6', '2', '2', '2', '5', '6', '2', '2', '2', '5', '1'},
                        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                        {'6', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '5'}};

    for (int j = 0; j < 17; j++)
    {
        if (key[i][j] == '0')
        {
            printf(" ");
        }
        else if (key[i][j] == '1')
        {
            printf("│");
        }
        else if (key[i][j] == '2')
        {
            printf("─");
        }
        else if (key[i][j] == '3')
        {
            printf("╭");
        }
        else if (key[i][j] == '4')
        {
            printf("╮");
        }
        else if (key[i][j] == '5')
        {
            printf("╯");
        }
        else if (key[i][j] == '6')
        {
            printf("╰");
        }
        else
            printf("%c", key[i][j]);
    }
}

void RandNum(int *ptr1, int *ptr2) // 포인터와함수 인자 받아야돼 메인에서 주소를 던져서 포인터로 받는다고
{
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        ptr1[i] = ((rand() % 10 + 1) * 2);
        for (int j = 0; j < i; j++)
        {
            if (ptr1[i] == ptr1[j])
            {
                i--;
            }
        }
    }

    for (int i = 0; i < 10; i++)
    {
        ptr2[i] = ((rand() % 10 + 1) * 2);
        for (int j = 0; j < i; j++)
        {
            if (ptr2[i] == ptr2[j])
            {
                i--;
            }
        }
    }
}

void Card1Print(int *ptr1)
{
    for (int i = 0; i < 10; i++)
    {
        printf(" %d", i + 1);
        if (ptr1[i] == 2)
            printf(" 🐵");
        else if (ptr1[i] == 4)
            printf(" 🐶");
        else if (ptr1[i] == 6)
            printf(" 🦊");
        else if (ptr1[i] == 8)
            printf(" 🐯");
        else if (ptr1[i] == 10)
            printf(" 🐱");
        else if (ptr1[i] == 12)
            printf(" 🐷");
        else if (ptr1[i] == 14)
            printf(" 🦝");
        else if (ptr1[i] == 16)
            printf(" 🐼");
        else if (ptr1[i] == 18)
            printf(" 🐻");
        else if (ptr1[i] == 20)
            printf(" 🐸");
    }
}

void BackPrint(int *ptr1)
{
    for (int i = 0; i < 10; i++)
    {
        printf(" %d", i + 1);
        if (ptr1[i] == 3)
            printf(" 🐵");
        else if (ptr1[i] == 5)
            printf(" 🐶");
        else if (ptr1[i] == 7)
            printf(" 🦊");
        else if (ptr1[i] == 9)
            printf(" 🐯");
        else if (ptr1[i] == 11)
            printf(" 🐱");
        else if (ptr1[i] == 13)
            printf(" 🐷");
        else if (ptr1[i] == 15)
            printf(" 🦝");
        else if (ptr1[i] == 17)
            printf(" 🐼");
        else if (ptr1[i] == 19)
            printf(" 🐻");
        else if (ptr1[i] == 21)
            printf(" 🐸");
        else
            printf(" ■ ");
    }
}

void LifePrint(int num)
{
    if (num == 5)
    {
        printf("  목숨 :  ❤️   ❤️   ❤️   ❤️   ❤️  │\n");
    }
    else if (num == 4)
    {
        printf("  목숨 :  ❤️   ❤️   ❤️   ❤️      │\n");
    }
    else if (num == 3)
    {
        printf("  목숨 :  ❤️   ❤️   ❤️          │\n");
    }
    else if (num == 2)
    {
        printf("  목숨 :  ❤️   ❤️              │\n");
    }
    else if (num == 1)
    {
        printf("  목숨 :  ❤️                  │\n");
    }
    else if (num == 0)
    {
        printf("  목숨 :                     │\n");
    }
}

void ItemPrint(int num)
{
    if (num == 2)
    {
        printf("  아이템 :         ⭐   ⭐   │");
    }
    else if (num == 1)
    {
        printf("  아이템 :              ⭐   │");
    }
    else if (num == 0)
    {
        printf("  아이템 :                   │");
    }
}

void ItemCard(int *ptr1)
{
    for (int i = 0; i < 10; i++)
    {
        printf(" %d", i + 1);
        if (ptr1[i] == 3 || ptr1[i] == 2)
            printf(" 🐵");
        else if (ptr1[i] == 5 || ptr1[i] == 4)
            printf(" 🐶");
        else if (ptr1[i] == 7 || ptr1[i] == 6)
            printf(" 🦊");
        else if (ptr1[i] == 9 || ptr1[i] == 8)
            printf(" 🐯");
        else if (ptr1[i] == 11 || ptr1[i] == 10)
            printf(" 🐱");
        else if (ptr1[i] == 13 || ptr1[i] == 12)
            printf(" 🐷");
        else if (ptr1[i] == 15 || ptr1[i] == 14)
            printf(" 🦝");
        else if (ptr1[i] == 17 || ptr1[i] == 16)
            printf(" 🐼");
        else if (ptr1[i] == 19 || ptr1[i] == 18)
            printf(" 🐻");
        else if (ptr1[i] == 21 || ptr1[i] == 20)
            printf(" 🐸");
    }
}

void Line1(void)
{
    printf("╭");
    for (int i = 0; i < 80; i++)
    {
        printf("─");
    }
    printf("╮\n");
    printf("│");
}

void Line2(void)
{
    printf("\n");
    printf("╰");
    for (int i = 0; i < 80; i++)
    {
        printf("─");
    }
    printf("╯\n");
}

void mazefull(int arr[][27])
{
    system("clear");
    for (int i = 0; i < 27; i++)
    {
        for (int j = 0; j < 27; j++)
        {

            if (arr[i][j] == 1)
            {
                printf("\x1b[40m");
                printf("   ");
                printf("\x1b[0m");
            }
            else if (arr[i][j] == 0 || arr[i][j] == 3)
            {
                printf("\x1b[47m");
                printf("   ");
                printf("\x1b[0m");
            }
            else if (arr[i][j] == 5)
            {
                printf("\x1b[47m");
                printf("🎁 ");
                printf("\x1b[0m");
            }
            else if (arr[i][j] == 4)
            {
                printf("\x1b[47m");
                printf("😺 ");
                printf("\x1b[0m");
            }
        }
        printf("\n");
    }
    sleep(3);
}
int cardgame()
{
    int x;
    int y;
    int a;
    int b = 0;
    int heart = 5;
    int item = 2;
    int choice;
    int card1[10] = {
        0};
    int card2[10] = {
        0};

    system("clear");
    printf("╭");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╮\n");

    printf("│\t\t\t -스토리-                       │\n");
    printf("│  시골에 도착한 춘식이...                              │\n");
    printf("│  새로운 동물들을 보게되는데...                        │\n");
    printf("│  동물들과 친구가 되고 싶은 춘식이가                   │\n");
    printf("│  동물들의 짝을 맞춰 친구가 되려 하는데...             │\n");

    printf("╰");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╯\n");

    printf("╭");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╮\n");

    printf("│\t\t\t-게임설명-                      │\n");
    printf("│ㆍ윗줄 10장 아랫줄 10장 총 20장의 카드                 │\n");
    printf("│                                                       │\n");
    printf("│ㆍ조작방법 : 카드의 숫자 입력                          │\n");
    printf("│                                                       │\n");
    printf("│ㆍ아이템 : ⭐ 11, 11을 입력하면 카드 정답이 3초 공개   │\n");
    printf("│                                                       │\n");
    printf("│ㆍ모든 카드를 짝에 맞게 뒤집으면 게임 클리어           │\n");
    printf("│                                                       │\n");
    printf("│ㆍ❤️  5개를 다 사용하면 게임 실패                       │\n");
    printf("│                                                       │\n");

    printf("╰");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╯\n");
    sleep(2);
    system("clear");

    RandNum(card1, card2);

    Line1();

    Card1Print(card1);

    printf("   목숨 : ❤️   ❤️   ❤️   ❤️   ❤️  │\n");
    printf("│");

    Card1Print(card2);

    printf("  아이템 :           ⭐   ⭐ │");

    Line2();

    sleep(5);

    while (1)
    {
        system("clear");

        Line1();

        BackPrint(card1);

        LifePrint(heart);

        printf("│");

        BackPrint(card2);

        ItemPrint(item);

        Line2();

        printf("                   ⭐ 아이템을 사용하려면 11, 11을 입력하세요!\n");
        if (heart == 0)
        {
            printf("5번의 목숨을 다 사용하여 춘식이 사망\n");
            sleep(1);
            int ju = 0;
            End(&ju);
            sleep(2);
            return 4;
        }
        if (b == 10)
        {
            printf("\n카드를 다 뒤집었어요! 성공!\n");
            int ju = 1;
            End(&ju);
            sleep(2);
            return 0;
        }
        printf("\n");
        printf("윗자리의 카드번호를 선택하세요");
        scanf("%d", &x);
        printf("아랫자리의 카드번호를 선택하세요");
        scanf("%d", &y);

        if (x == 11 && y == 11 && item >= 1)
        {
            system("clear");
            printf("  아이템을 사용합니다\n");

            ItemCard(card1);
            printf("\n");
            ItemCard(card2);
            printf("\n");

            sleep(3);
            item--;
            continue;
        }
        else if (x == 11 && y == 11 && item == 0)
        {
            printf("아이템을 다 사용했습니다!\n");
            sleep(1);
            continue;
        }

        if (card1[x - 1] == card2[y - 1])
        {
            a = card1[x - 1];
            a++;
            card1[x - 1] = a;
            card2[y - 1] = a;
            b++;
        }
        else
        {
            printf("땡 틀렸습니다!\n");
            heart -= 1;
            sleep(1);
        }
    }
}
int gullgame()
{

    int map[15][30] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 1, 5, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
                       {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1},
                       {1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
                       {1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
                       {1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1},
                       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                       {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1},
                       {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
                       {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
                       {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
                       {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
                       {1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 5, 1, 1, 1, 0, 1},
                       {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    // 1벽 0 먹이있는길 3 먹이없는길 4는 춘식이 5는 유령
    int x = 14;
    int y = 15;
    int vector;
    int eat = 0; // 팩맨 먹이
    int gh1_x = 1;
    int gh1_y = 2;
    int gh2_x = 3;
    int gh2_y = 15;
    int gh3_x = 12;
    int gh3_y = 24;
    int a1 = 0;
    int a2 = 0;
    int a3 = 0;    // 유령의 처음위치는 0
    int heart = 3; // 춘식이의 목숨.
    system("clear");

    printf("╭");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╮\n");

    printf("│\t\t\t -스토리-                       │\n");
    printf("│  바다에 도착한 춘식이 배가 꼬르륵 꼬르륵....          │\n");
    printf("│  물고기를 먹고싶지만  앞에는 무서운 갈매기때가!!!!    │\n");
    printf("│  갈매기를 피해서 생선을 먹어라                        │\n");

    printf("╰");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╯\n");
    printf("╭");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╮\n");

    printf("│\t\t\t-게임설명-                      │\n");
    printf("│                                                       │\n");
    printf("│ㆍ조작키 : a - 좌로이동  d - 우로이동                  │\n");
    printf("│ㆍ조작키 : w - 위로이동  s - 아래로이동                │\n");
    printf("│                                                       │\n");

    printf("│ㆍ   🦤  에게 3번 잡히면 게임 실패                      │\n");
    printf("│ㆍ   🐟  160마리 먹으면 게임 클리어                    │\n");
    printf("│                                                       │\n");

    printf("│                                                       │\n");
    printf("╰");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╯\n");

    sleep(2);

    while (1)
    {
        system("clear");
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (map[i][j] == 1)
                {
                    printf("\x1b[44m");
                    printf("▒▒▒");
                    printf("\x1b[0m");
                }

                else if (map[i][j] == 0)
                {
                    printf("\x1b[31m");
                    printf(" 🐟");
                    printf("\x1b[0m");
                }
                else if (map[i][j] == 4)
                    printf("😺 ");
                else if (map[i][j] == 5)
                    printf("🦤  "); // 유령
                else
                    printf("   ");
            }
            key(i);

            printf("\n");
        }
        printf("│");
        LifePrint(heart);
        printf("춘식이가 먹은 먹이 수 : %d\n", eat);

        if (heart == 0) // 목숨이 다해 사망.
        {
            system("clear");
            printf("\n\n\n춘식이는 갈매기에게 야금야금 뜯어먹혔다........\n");
            int ju = 0;
            End(&ju);
            sleep(2);
            return 3;
        }

        printf("방향키를 입력해주세요: \n");

        vector = getch();

        if (vector == 87 || vector == 119) // W
        {
            if (map[x - 1][y] == 0 || map[x - 1][y] == 3)
            {
                if (map[x - 1][y] == 0)
                {
                    eat++;
                }

                map[x][y] = 3;
                x = x - 1;
                map[x][y] = 4;
            }
            else if (map[x - 1][y] == 5) // 유령과 만나는경우.
            {

                map[x][y] = 3;

                x = 14;
                y = 15;
                map[x][y] = 4;
                heart--;
            }
        }
        else if (vector == 97 || vector == 65) // A
        {
            if (map[x][y - 1] == 0 || map[x][y - 1] == 3)
            {
                if (map[x][y - 1] == 0)
                {
                    eat++;
                }
                map[x][y] = 3;
                y = y - 1;
                map[x][y] = 4;
            }
            else if (map[x][y - 1] == 5)
            {

                map[x][y] = 3;

                x = 14;
                y = 15;
                map[x][y] = 4;
                heart--;
            }
        }
        else if (vector == 68 || vector == 100) // D
        {
            if (map[x][y + 1] == 0 || map[x][y + 1] == 3)
            {
                if (map[x][y + 1] == 0)
                {
                    eat++;
                }
                map[x][y] = 3;
                y = y + 1;
                map[x][y] = 4;
            }
            else if (map[x][y + 1] == 5)
            {

                map[x][y] = 3;

                x = 14;
                y = 15;
                map[x][y] = 4;
                heart--;
            }
        }
        else if (vector == 83 || vector == 115) // S
        {
            if (map[x + 1][y] == 0 || map[x + 1][y] == 3)
            {
                if (map[x + 1][y] == 0)
                {
                    eat++;
                }
                map[x][y] = 3;
                x = x + 1;
                map[x][y] = 4;
            }
            else if (map[x + 1][y] == 5)
            {

                map[x][y] = 3;
                x = 14;
                y = 15; // 유령과 만나면 처음자리로빽
                map[x][y] = 4;
                heart--;
            }
        }
        if (eat == 160)
        {
            system("clear");
            printf("\n\n\t\t춘식이가 게임에 성공하여 🦤를 얻었다!!\n");
            int ju = 1;
            End(&ju);
            sleep(2);

            return 0;
        }
        gullmove(&gh1_x, &gh1_y, map, x, y, &a1);
        gullmove(&gh2_x, &gh2_y, map, x, y, &a2);
        gullmove(&gh3_x, &gh3_y, map, x, y, &a3);
    }
}
int raingame(void)
{
    int life = 3;
    int cont = 0;
    int end;

    system("clear");
    printf("╭");
    for (int i = 0; i < 55; i++)
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
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╯\n");

    printf("╭");
    for (int i = 0; i < 55; i++)
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
    for (int i = 0; i < 55; i++)
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

    printf("\n");

    if (end == 0)
    {

        End(&end);
        sleep(2);
        return 5;
    }
    else if (end == 1)
    {

        End(&end);
        sleep(2);
        return 0;
    }
}

int mirogame()
{
    int a = 0;

    char vector;
    int x = 26, y = 13;
    int miro[27][27] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
                        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 1, 5, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
                        {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 5, 1, 0, 1},
                        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
                        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
                        {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
                        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1},
                        {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 5, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 5, 1, 0, 1, 0, 1},
                        {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
                        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1},
                        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 5, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
                        {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1},
                        {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 5, 0, 0, 1, 0, 0, 5, 1, 0, 0, 0, 1},
                        {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 5, 1, 0, 0, 0, 1, 0, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    // 1벽 0길 4춘식이 5아이템/

    printf("╭");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╮\n");
    printf("│\t\t\t -스토리-                       │\n");
    printf("│  시장에 도착한 춘식이...                              │\n");
    printf("│  복잡해서 길을 잃어버리는데...                        │\n");
    printf("│  길을 찾으려는 춘식이                                 │\n");
    printf("│  미로를 통과하여 시장을 벗어나라!                     │\n");

    printf("╰");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╯\n");

    printf("╭");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╮\n");
    printf("│\t\t\t-게임설명-                      │\n");
    printf("│                                                       │\n");
    printf("│ㆍ조작키 : a - 좌로이동  d - 우로이동                  │\n");
    printf("│ㆍ조작키 : w - 위로이동  s - 아래로이동                │\n");
    printf("│                                                       │\n");
    printf("│ㆍ아이템 : 🎁 를 먹으면 맵이 밝혀짐                    │\n");
    printf("│                                                       │\n");
    printf("│ㆍ출구에 도착하면 게임 클리어                          │\n");
    printf("│                                                       │\n");
    printf("╰");
    for (int i = 0; i < 55; i++)
    {
        printf("─");
    }
    printf("╯\n");

    while (1)
    {

        system("clear");
        for (int i = 0; i < 27; i++)
        {
            for (int j = 0; j < 27; j++)
            {
                if (miro[i][j] == 3)

                {
                    printf("\x1b[47m");
                    printf("   ");
                    printf("\x1b[0m");
                }

                else if (miro[i][j] == 4)
                {
                    printf("\x1b[47m");
                    printf("😺 ");
                    printf("\x1b[0m");
                }
                else if (miro[i][j] == 5)
                {
                    printf("\x1b[47m");
                    printf("🎁 ");
                    printf("\x1b[0m");
                }
                else
                {
                    printf("\x1b[40m");
                    printf("   ");
                    printf("\x1b[0m");
                }
            }

            printf("\n");
        }

        printf("방향키를 입력해주세요: \n");
        vector = getch();

        if (vector == 87 || vector == 119) // W
        {
            if (miro[x - 1][y] == 0 || miro[x - 1][y] == 5 || miro[x - 1][y] == 3)
            {
                if (miro[x - 1][y] == 5)
                {
                    mazefull(miro);
                }
                miro[x][y] = 3;
                x = x - 1;
                miro[x][y] = 4;
            }
        }
        else if (vector == 97 || vector == 65) // A
        {
            if (miro[x][y - 1] == 0 || miro[x][y - 1] == 5 || miro[x][y - 1] == 3)
            {
                if (miro[x][y - 1] == 5)
                {
                    mazefull(miro);
                }
                miro[x][y] = 3;
                y = y - 1;
                miro[x][y] = 4;
            }
        }
        else if (vector == 68 || vector == 100) // D
        {
            if (miro[x][y + 1] == 0 || miro[x][y + 1] == 5 || miro[x][y + 1] == 3)
            {
                if (miro[x][y + 1] == 5)
                {
                    mazefull(miro);
                }
                miro[x][y] = 3;
                y = y + 1;
                miro[x][y] = 4;
            }
        }
        else if (vector == 83 || vector == 115) // S
        {
            if (miro[x + 1][y] == 0 || miro[x + 1][y] == 5 || miro[x + 1][y] == 3)
            {
                if (miro[x + 1][y] == 5)
                {
                    mazefull(miro);
                }
                miro[x][y] = 3;
                x = x + 1;
                miro[x][y] = 4;
            }
        }

        if (x == 0 && y == 13)
        {
            int ju = 1;
            End(&ju);
            sleep(2);

            return 0;
        }
    }
}

int main()
{
    system("clear");
    start();
    int vector;
    int minimap[10][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                           {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
                           {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                           {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                           {1, 3, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 4, 1},
                           {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                           {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                           {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                           {1, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 1},
                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int x = 4;
    int y = 7; // 메인에있어야함.
    while (1)
    {
        system("clear");
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                if (minimap[i][j] == 1)
                {
                    printf("\x1b[32m");
                    printf("▒▒▒");
                    printf("\x1b[0m");
                }
                else if (minimap[i][j] == 0)
                {

                    printf("   ");
                }
                else if (minimap[i][j] == 2) // 1 7

                {
                    printf(" 🎁");
                }
                else if (minimap[i][j] == 3) // 4 1
                {
                    printf(" 🦤 ");
                }
                else if (minimap[i][j] == 4) // 4 13
                {
                    printf("🃏 ");
                }
                else if (minimap[i][j] == 5) // 8 7
                {
                    printf(" 💧");
                }
                else if (minimap[i][j] == 10) // 4 7
                {
                    printf(" 😺");
                }
            }
            printf("\n");
        }

        printf("\t\t\t");
        printf("먹은 아이템 : ");
        if (minimap[1][7] == 0 || minimap[1][7] == 10)
        {
            printf(" 🎁");
        }
        if (minimap[4][1] == 0 || minimap[4][1] == 10)

        {
            printf(" 🦤");
        }
        if (minimap[4][13] == 0 || minimap[4][13] == 10)
        {
            printf(" 🃏");
        }
        if (minimap[8][7] == 0 || minimap[8][7] == 10)
        {
            printf(" 💧");
        }
        printf("\n");

        if (minimap[1][7] == 0 && minimap[4][1] == 0 && minimap[4][13] == 0 && minimap[8][7] == 0) // 4 게임 모두 성공하면 모험 끝.
        {
            ending();
            break;
        }

        printf("\n방향키를 입력해주세요: \n");
        vector = getch();

        if (vector == 87 || vector == 119) // W
        {
            if (minimap[x - 1][y] != 1)
            {

                if (minimap[x - 1][y] == 2)
                {
                    minimap[1][7] = mirogame();
                }
                else if (minimap[x - 1][y] == 4)
                {
                    minimap[4][13] = cardgame();
                }
                else if (minimap[x - 1][y] == 3)
                {
                    minimap[4][1] = gullgame();
                }
                else if (minimap[x - 1][y] == 5)
                {
                    minimap[8][7] = raingame();
                }
                else
                {

                    minimap[x][y] = 0; // 춘식이를 길로 만들로 길을 춘식으로 만듬
                    x = x - 1;
                    minimap[x][y] = 10;
                }
            }
        }
        else if (vector == 97 || vector == 65) // A
        {
            if (minimap[x][y - 1] != 1)
            {
                if (minimap[x][y - 1] == 2)
                {
                    minimap[1][7] = mirogame();
                }
                else if (minimap[x][y - 1] == 4)
                {
                    minimap[4][13] = cardgame();
                }
                else if (minimap[x][y - 1] == 3)
                {
                    minimap[4][1] = gullgame();
                }
                else if (minimap[x][y - 1] == 5)
                {
                    minimap[8][7] = raingame();
                }
                else
                {

                    minimap[x][y] = 0;
                    y = y - 1;
                    minimap[x][y] = 10;
                }
            }
        }
        else if (vector == 68 || vector == 100) // D
        {
            if (minimap[x][y + 1] != 1)
            {
                if (minimap[x][y + 1] == 2)
                {
                    minimap[1][7] = mirogame();
                }
                else if (minimap[x][y + 1] == 4)
                {
                    minimap[4][13] = cardgame();
                }
                else if (minimap[x][y + 1] == 3)
                {
                    minimap[4][1] = gullgame();
                }
                else if (minimap[x][y + 1] == 5)
                {
                    minimap[8][7] = raingame();
                }
                else
                {

                    minimap[x][y] = 0;
                    y = y + 1;
                    minimap[x][y] = 10;
                }
            }
        }
        else if (vector == 83 || vector == 115) // S
        {
            if (minimap[x + 1][y] != 1)
            {
                if (minimap[x + 1][y] == 2)
                {
                    minimap[1][7] = mirogame();
                }
                else if (minimap[x + 1][y] == 4)
                {
                    minimap[4][13] = mirogame();
                }
                else if (minimap[x + 1][y] == 3)
                {
                    minimap[4][1] = gullgame();
                }
                else if (minimap[x + 1][y] == 5)
                {
                    minimap[8][7] = raingame();
                }
                else
                {

                    minimap[x][y] = 0;
                    x = x + 1;
                    minimap[x][y] = 10;
                }
            }
        }
    }
    return 0;
}