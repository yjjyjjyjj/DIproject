#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int getch()     //엔터를 누르지 않아도 1문자씩 키입력을 받기 위한 함수(wasd)
{
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
    c = getchar();                               // 키보드 입력 읽음
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
    return c;
}
int main()
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
}