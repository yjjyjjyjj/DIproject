#include <unistd.h>
#include <stdio.h>
void generateLine(char line[], int size)
{
    int i;
    for (i = 0; i < size - 1; i++)
    {
        if (i==rand() % 7 < 1)
        {
            line[i] = '#';
        }
        else
        {
            line[i] = ' ';
        }
    }
    line[size - 1] = 0;
}
int main()
{
    int x = 0;
    int y = 0;
    char line[80];
    printf("\033[2J");   // clear screen
    printf("\033[?25l"); // hides the cursor
    int i;
    for (i = 0; i < 2000; i++)
    {
        generateLine(line, 50);
        printf("\033[%d;%dH", y, x); // moves the cursor
        printf("%s\n", line);
        usleep(1000500);         // sleep (unit : 1/10^6 seconds)
        printf("\033[%dT\n", 1); // scroll down
    }
    printf("\033[?25h"); // shows the cursor
    return 0;
}