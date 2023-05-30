#include <stdio.h>

void main()
{
	//char c = 'a';
	//printf("%I64d\n", sizeof(c));
	//printf("%c\n", c);

	//int n = 100;
	//printf("%I64d\n", sizeof(n));
	//printf("%d\n", n);

	char c1 = 'A';
	char c2 = 'B';
	printf("%c\n", c1);

	char* ptr = &c1;
	printf("         c1 : %c\n",           c1);
	printf("        ptr : %p\n",          ptr);
	printf("       *ptr : %c\n",         *ptr);
	printf("     *(&c1) : %c\n",       *(&c1));
	printf("       *&c1 : %c\n",         *&c1);
	printf("        &c1 : %p\n",          &c1);
	printf(" (char*)&c1 : %p\n",   (char*)&c1);
	//printf("  (char*)c1 : %p\n",    (char*)c1); //16진수 포인터 형변환
	printf("  (char*)c1 : %d\n",      (int)c1);
	printf("*(char*)&c1 : %c\n",  *(char*)&c1);
	printf("       *&c1 : %c\n",         *&c1);

	//printf("%x\n", (int)&c1);
	//printf("%p\n", &c1);
	//printf("%d\n", (int)&c1);
	//printf("%d\n", (int)sizeof(&c1));
	//printf("%p\n", &c2);
}