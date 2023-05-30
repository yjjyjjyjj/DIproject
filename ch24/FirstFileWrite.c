#include <stdio.h>

int main(void)
{
    FILE * fp=fopen("data.txt", "wt");    // 현재 디렉터리에 저장된 파일 data.txt를 찾는다.
    if(fp==NULL)
    {
        puts("파일오픈 실패!");
        return -1;   // 비정상적 종료를 의미하기 위해서 -1을 반환
    }

    fputc('A', fp);   // 문자 A를 fp가 가리키는 파일에 저장해라!
    fputc('B', fp);
    fputc('C', fp);
    fclose(fp);    // 스트림의 종료
    return 0;
}