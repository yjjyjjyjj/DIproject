 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>

 int main(void)
 {
         
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
    return 0;
 }