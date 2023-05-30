#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(void)
{
    int coffee_mu_a1[4] = {4000, 4500, 5000, 5500}; // 아메리카노
    int coffee_mu_a2[4] = {4500, 5000, 5500, 6000}; // 카페라떼
    int coffee_mu_a3[4] = {4000, 4500, 5000, 5500}; // 카푸치노
    int coffee_mu_a4[4] = {5400, 5900, 6400, 6900}; // 카라멜마키아또
    int coffee_mu_a5[4] = {5400, 5900, 6400, 6900}; // 화이트초코
    int coffee_mu_a6[4] = {5000, 5500, 6000, 6500}; // 카페모카
    int coffee_mu_a7[4] = {5400, 5900, 6400, 6900}; // 스타벅스 돌체

    int coldbrew_mu_a1[3] = {5800, 6300, 6800}; // 콜드브루오트라떼
    int coldbrew_mu_a2[3] = {6000, 6500, 7000}; // 돌체콜드브루
    int coldbrew_mu_a3[3] = {5800, 6300, 6800}; // 바닐라크림콜드브루
    int coldbrew_mu_a4[3] = {4900, 5400, 5900}; // 콜드브루

    int frappuccino_mu_a1[3] = {6300, 6800, 7300}; // 더블 에스프레소칩
    int frappuccino_mu_a2[3] = {6300, 6800, 7300}; // 제주 유기농 말차
    int frappuccino_mu_a3[3] = {6300, 6800, 7300}; // 자바칩 프라푸
    int frappuccino_mu_a4[3] = {6000, 6500, 7000}; // 초콜릿 크림칩
    int frappuccino_mu_a5[3] = {6000, 6500, 7000}; // 화이트 초콜릿
    int frappuccino_mu_a6[3] = {6000, 6500, 7000}; // 모카 프라푸치노
    int frappuccino_mu_a7[3] = {5900, 6400, 6900}; // 카라멜 프라푸
    int frappuccino_mu_a8[3] = {5500, 6000, 6500}; // 에스프레소 프라푸
    int frappuccino_mu_a9[3] = {5500, 6000, 6500}; // 바닐라크림 프라푸

    int blended_mu_a1[3] = {6300, 6800, 7300}; // 민트 초콜릿
    int blended_mu_a2[3] = {6300, 6800, 7300}; // 딸기 딜라이트
    int blended_mu_a3[3] = {6300, 6800, 7300}; // 피치 & 레몬
    int blended_mu_a4[3] = {6300, 6800, 7300}; // 망고 바나나
    int blended_mu_a5[3] = {5400, 5900, 6400}; // 망고 패션 프루트

    int physio_mu_a1[3] = {5900, 6400, 6900}; // 쿨라임
    int physio_mu_a2[3] = {5400, 5900, 6400}; // 블랙티 레모네
    int physio_mu_a3[3] = {5400, 5900, 6400}; // 패션 탱고

    int tea_mu_a1[3] = {6100, 6600, 7100}; // 뉴이어 시트러스
    int tea_mu_a2[3] = {5900, 6400, 6900}; // 돌체 블랙
    int tea_mu_a3[3] = {5900, 6400, 6900}; // 유자 민트
    int tea_mu_a4[3] = {5900, 6400, 6900}; // 패션 프루트
    int tea_mu_a5[3] = {6100, 6600, 7100}; // 제주 유기농 말차
    int tea_mu_a6[3] = {5500, 6000, 6500}; // 차이 티
    int tea_mu_a7[3] = {5900, 6400, 6900}; // 라임 패션
    int tea_mu_a8[3] = {5700, 6200, 6700}; // 자몽 허니
    int i = 0, n = 0, j = 0;               // 메뉴선택
    int num[32];
    int money[32];
    int sum = 0, total = 0, cf_sum = 0, cb_sum = 0, fr_sum = 0, bl_sum = 0, ph_sum = 0, te_sum = 0, all_total = 0;

    char s1[32][30]; // 음료 명
    char size[32];   // 음료 사이즈
    char k = 0;

    while (1)
    {
        system("clear");
        if (i > 0)
        {
            for (j = 0; j < n; j++)
            {
                printf("장바구니: %s 사이즈: %c 수량: %d  가격: %d \n", s1[j], size[j], num[j], num[j] * money[j]);
                sum += num[j] * money[j];
            }
        }
        printf("1.커피  2.콜드브루  3.프라푸치노  4.블렌디드  5.피지오  6.티  7.계산하기  8.매출정산\n입력: ");
        scanf("%d", &i);

        switch (i)
        {
        case 1: // 커피 메
            printf("메뉴                Short      Tall      Grande      Venti \n");
            printf("아메리카노            %d        %d         %d          %d \n", coffee_mu_a1[0], coffee_mu_a1[1], coffee_mu_a1[2], coffee_mu_a1[3]);
            printf("카페라떼              %d        %d         %d          %d \n", coffee_mu_a2[0], coffee_mu_a2[1], coffee_mu_a2[2], coffee_mu_a2[3]);
            printf("카푸치노              %d        %d         %d          %d \n", coffee_mu_a3[0], coffee_mu_a3[1], coffee_mu_a3[2], coffee_mu_a3[3]);
            printf("카라멜마키아또         %d        %d         %d          %d \n", coffee_mu_a4[0], coffee_mu_a4[1], coffee_mu_a4[2], coffee_mu_a4[3]);
            printf("화이트초콜릿모카       %d        %d         %d          %d \n", coffee_mu_a5[0], coffee_mu_a5[1], coffee_mu_a5[2], coffee_mu_a5[3]);
            printf("카페모카              %d        %d         %d          %d \n", coffee_mu_a6[0], coffee_mu_a6[1], coffee_mu_a6[2], coffee_mu_a6[3]);
            printf("스타벅스돌체라떼       %d        %d         %d          %d \n", coffee_mu_a7[0], coffee_mu_a7[1], coffee_mu_a7[2], coffee_mu_a7[3]);
            printf("음료 선택:");
            scanf("%s", s1[j]);
            getchar();

            if (strcmp(s1[j], "아메리카노") == 0)
            {
                printf("사이즈 선택 S, T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 83)
                {
                    money[j] = coffee_mu_a1[0];
                }
                else if (size[j] == 84)
                {
                    money[j] = coffee_mu_a1[1];
                }
                else if (size[j] == 71)
                {
                    money[j] = coffee_mu_a1[2];
                }
                else if (size[j] == 86)
                {
                    money[j] = coffee_mu_a1[3];
                }
                else
                {
                    continue;
                }
                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cf_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "카페라떼") == 0)
            {
                printf("사이즈 선택 S, T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 83)
                {
                    money[j] = coffee_mu_a2[0];
                }
                else if (size[j] == 84)
                {
                    money[j] = coffee_mu_a2[1];
                }
                else if (size[j] == 71)
                {
                    money[j] = coffee_mu_a2[2];
                }
                else if (size[j] == 86)
                {
                    money[j] = coffee_mu_a2[3];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cf_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "카푸치노") == 0)
            {
                printf("사이즈 선택 S, T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 83)
                {
                    money[j] = coffee_mu_a3[0];
                }
                else if (size[j] == 84)
                {
                    money[j] = coffee_mu_a3[1];
                }
                else if (size[j] == 71)
                {
                    money[j] = coffee_mu_a3[2];
                }
                else if (size[j] == 86)
                {
                    money[j] = coffee_mu_a3[3];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cf_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "카라멜마키아또") == 0)
            {
                printf("사이즈 선택 S, T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 83)
                {
                    money[j] = coffee_mu_a4[0];
                }
                else if (size[j] == 84)
                {
                    money[j] = coffee_mu_a4[1];
                }
                else if (size[j] == 71)
                {
                    money[j] = coffee_mu_a4[2];
                }
                else if (size[j] == 86)
                {
                    money[j] = coffee_mu_a4[3];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cf_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "화이트초콜릿모카") == 0)
            {
                printf("사이즈 선택 S, T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 83)
                {
                    money[j] = coffee_mu_a5[0];
                }
                else if (size[j] == 84)
                {
                    money[j] = coffee_mu_a5[1];
                }
                else if (size[j] == 71)
                {
                    money[j] = coffee_mu_a5[2];
                }
                else if (size[j] == 86)
                {
                    money[j] = coffee_mu_a5[3];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cf_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "카페모카") == 0)
            {
                printf("사이즈 선택 S, T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 83)
                {
                    money[j] = coffee_mu_a6[0];
                }
                else if (size[j] == 84)
                {
                    money[j] = coffee_mu_a6[1];
                }
                else if (size[j] == 71)
                {
                    money[j] = coffee_mu_a6[2];
                }
                else if (size[j] == 86)
                {
                    money[j] = coffee_mu_a6[3];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cf_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "스타벅스돌체라떼") == 0)
            {
                printf("사이즈 선택 S, T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 83)
                {
                    money[j] = coffee_mu_a7[0];
                }
                else if (size[j] == 84)
                {
                    money[j] = coffee_mu_a7[1];
                }
                else if (size[j] == 71)
                {
                    money[j] = coffee_mu_a7[2];
                }
                else if (size[j] == 86)
                {
                    money[j] = coffee_mu_a7[3];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cf_sum += money[j] * num[j];
                continue;
            }
            else
                continue;
        case 2: // 콜드브루 메뉴
            printf("메뉴                Tall      Grande      Venti \n");
            printf("콜드브루오트라떼       %d         %d          %d \n", coldbrew_mu_a1[0], coldbrew_mu_a1[1], coldbrew_mu_a1[2]);
            printf("돌체콜드브루           %d         %d          %d \n", coldbrew_mu_a2[0], coldbrew_mu_a2[1], coldbrew_mu_a2[2]);
            printf("바닐라크림콜드브루     %d         %d          %d \n", coldbrew_mu_a3[0], coldbrew_mu_a3[1], coldbrew_mu_a3[2]);
            printf("콜드브루              %d         %d          %d \n", coldbrew_mu_a4[0], coldbrew_mu_a4[1], coldbrew_mu_a4[2]);

            printf("음료 선택:");
            scanf("%s", s1[j]);
            getchar();

            if (strcmp(s1[j], "콜드브루오트라떼") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = coldbrew_mu_a1[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = coldbrew_mu_a1[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = coldbrew_mu_a1[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cb_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "돌체콜드브루") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = coldbrew_mu_a2[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = coldbrew_mu_a2[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = coldbrew_mu_a2[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cb_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "바닐라크림콜드브루") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = coldbrew_mu_a3[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = coldbrew_mu_a3[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = coldbrew_mu_a3[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cb_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "콜드브루") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = coldbrew_mu_a4[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = coldbrew_mu_a4[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = coldbrew_mu_a4[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                cb_sum += money[j] * num[j];
                continue;
            }
            else
                continue;
        case 3: // 프라푸치노 메뉴
            printf("메뉴                                      Tall      Grande      Venti \n");
            printf("더블 에스프레소 칩 프라푸치노               %d         %d          %d \n", frappuccino_mu_a1[0], frappuccino_mu_a1[1], frappuccino_mu_a1[2]);
            printf("제주 유기농 말차로 만든크림 프라푸치노       %d         %d          %d \n", frappuccino_mu_a2[0], frappuccino_mu_a2[1], frappuccino_mu_a2[2]);
            printf("자바 칩 프라푸치노                         %d         %d          %d \n", frappuccino_mu_a3[0], frappuccino_mu_a3[1], frappuccino_mu_a3[2]);
            printf("초콜릿 크림칩 프라푸치노                    %d         %d          %d \n", frappuccino_mu_a4[0], frappuccino_mu_a4[1], frappuccino_mu_a4[2]);
            printf("화이트 초콜릿 모카 프라푸치노               %d         %d          %d \n", frappuccino_mu_a5[0], frappuccino_mu_a5[1], frappuccino_mu_a5[2]);
            printf("모카 프라푸치노                            %d         %d          %d \n", frappuccino_mu_a6[0], frappuccino_mu_a6[1], frappuccino_mu_a6[2]);
            printf("카라멜 프라푸치노                          %d         %d          %d \n", frappuccino_mu_a7[0], frappuccino_mu_a7[1], frappuccino_mu_a7[2]);
            printf("에스프레소 프라푸치노                      %d         %d          %d \n", frappuccino_mu_a8[0], frappuccino_mu_a8[1], frappuccino_mu_a8[2]);
            printf("바닐라크림 프라푸치노                      %d         %d          %d \n", frappuccino_mu_a9[0], frappuccino_mu_a9[1], frappuccino_mu_a9[2]);
            printf("음료 선택:");
            scanf("%s", s1[j]);
            getchar();

            if (strcmp(s1[j], "더블에스프레소칩프라푸치노") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = frappuccino_mu_a1[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = frappuccino_mu_a1[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = frappuccino_mu_a1[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                fr_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "제주유기농말차로만든크림프라루치노") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = frappuccino_mu_a2[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = frappuccino_mu_a2[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = frappuccino_mu_a2[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                fr_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "자바칩프라푸치노") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = frappuccino_mu_a3[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = frappuccino_mu_a3[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = frappuccino_mu_a3[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                fr_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "초콜릿크림칩프라푸치노") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = frappuccino_mu_a4[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = frappuccino_mu_a4[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = frappuccino_mu_a4[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                fr_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "화이트초콜릿모카프라푸치노") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = frappuccino_mu_a5[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = frappuccino_mu_a5[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = frappuccino_mu_a5[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                fr_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "모카프라푸치노") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = frappuccino_mu_a6[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = frappuccino_mu_a6[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = frappuccino_mu_a6[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                fr_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "카라멜프라푸치노") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = frappuccino_mu_a7[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = frappuccino_mu_a7[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = frappuccino_mu_a7[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                fr_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "에스프레소프라푸치노") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = frappuccino_mu_a8[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = frappuccino_mu_a8[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = frappuccino_mu_a8[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                fr_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "바닐라크림프라푸치노") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = frappuccino_mu_a9[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = frappuccino_mu_a9[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = frappuccino_mu_a9[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                fr_sum += money[j] * num[j];
                continue;
            }
            else
                continue;

        case 4: // 블렌디드 메뉴
            printf("메뉴                                     Tall      Grande      Venti \n");
            printf("민트 초콜릿 칩 블렌디드                    %d         %d          %d \n", blended_mu_a1[0], blended_mu_a1[1], blended_mu_a1[2]);
            printf("딸기 딜라이트 요거트 블렌디드              %d         %d          %d \n", blended_mu_a2[0], blended_mu_a2[1], blended_mu_a2[2]);
            printf("피치&레몬 블렌디드                         %d         %d          %d \n", blended_mu_a3[0], blended_mu_a3[1], blended_mu_a3[2]);
            printf("망고 바나나 블렌디드                       %d         %d          %d \n", blended_mu_a4[0], blended_mu_a4[1], blended_mu_a4[2]);
            printf("망고 패션 프루트 블렌디드                  %d         %d          %d \n", blended_mu_a5[0], blended_mu_a5[1], blended_mu_a5[2]);
            printf("음료 선택:");
            scanf("%s", s1[j]);
            getchar();

            if (strcmp(s1[j], "민트초콜릿칩블렌디드") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = blended_mu_a1[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = blended_mu_a1[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = blended_mu_a1[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                bl_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "딸기딜라이트요거트블렌디드") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = blended_mu_a2[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = blended_mu_a2[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = blended_mu_a2[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                bl_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "피치&레몬블렌디드") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = blended_mu_a3[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = blended_mu_a3[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = blended_mu_a3[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                bl_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "망고바나나블렌디드") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = blended_mu_a4[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = blended_mu_a4[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = blended_mu_a4[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                bl_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "망고패션프루트블렌디드") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = blended_mu_a5[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = blended_mu_a5[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = blended_mu_a5[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                bl_sum += money[j] * num[j];
                continue;
            }
            else
                continue;

        case 5: // 피지오 메뉴
            printf("메뉴                                     Tall      Grande      Venti \n");
            printf("쿨라임 피지오                              %d         %d          %d \n", physio_mu_a1[0], physio_mu_a1[1], physio_mu_a1[2]);
            printf("블랙티 레모네이드 피지오                    %d         %d          %d \n", physio_mu_a2[0], physio_mu_a2[1], physio_mu_a2[2]);
            printf("패션 탱고 티 레모네이드피지오               %d         %d          %d \n", physio_mu_a3[0], physio_mu_a3[1], physio_mu_a3[2]);
            printf("음료 선택:");
            scanf("%s", s1[j]);
            getchar();

            if (strcmp(s1[j], "쿨라임피지오") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = physio_mu_a1[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = physio_mu_a1[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = physio_mu_a1[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                ph_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "블랙티레모네이드피지오") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = physio_mu_a2[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = physio_mu_a2[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = physio_mu_a2[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                ph_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "패션탱고티레모네이드피지오") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = physio_mu_a3[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = physio_mu_a3[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = physio_mu_a3[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                ph_sum += money[j] * num[j];
                continue;
            }
            else
                continue;
        case 6: // 티 메뉴
            printf("메뉴                                     Tall      Grande      Venti \n");
            printf("뉴이어 시트러스 티                         %d         %d          %d \n", tea_mu_a1[0], tea_mu_a1[1], tea_mu_a1[2]);
            printf("돌체 블랙 밀크티                           %d         %d          %d \n", tea_mu_a2[0], tea_mu_a2[1], tea_mu_a2[2]);
            printf("유자 민트 티                               %d         %d          %d \n", tea_mu_a3[0], tea_mu_a3[1], tea_mu_a3[2]);
            printf("패션 프루트 티                             %d         %d          %d \n", tea_mu_a4[0], tea_mu_a4[1], tea_mu_a4[2]);
            printf("제주 유기농 말차로 만든 라떼                %d         %d          %d \n", tea_mu_a5[0], tea_mu_a5[1], tea_mu_a5[2]);
            printf("차이 티 라떼                               %d         %d          %d \n", tea_mu_a6[0], tea_mu_a6[1], tea_mu_a6[2]);
            printf("라임 패션 티                               %d         %d          %d \n", tea_mu_a7[0], tea_mu_a7[1], tea_mu_a7[2]);
            printf("자몽 허니 블랙티                           %d         %d          %d \n", tea_mu_a8[0], tea_mu_a8[1], tea_mu_a8[2]);
            printf("음료 선택:");
            scanf("%s", s1[j]);
            getchar();

            if (strcmp(s1[j], "뉴이어시트러스 티") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = tea_mu_a1[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = tea_mu_a1[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = tea_mu_a1[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                te_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "돌체블랙밀크티") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = tea_mu_a2[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = tea_mu_a2[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = tea_mu_a2[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                te_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "유자민트티") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = tea_mu_a3[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = tea_mu_a3[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = tea_mu_a3[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                te_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "패션프루트티") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = tea_mu_a4[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = tea_mu_a4[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = tea_mu_a4[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                te_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "제주유기농말차로만든라떼") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = tea_mu_a5[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = tea_mu_a5[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = tea_mu_a5[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                te_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "차이티라떼") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = tea_mu_a6[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = tea_mu_a6[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = tea_mu_a6[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                te_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "라임패션티") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = tea_mu_a7[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = tea_mu_a7[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = tea_mu_a7[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                te_sum += money[j] * num[j];
                continue;
            }
            if (strcmp(s1[j], "자몽허니블랙티") == 0)
            {
                printf("사이즈 선택 T, G, V: ");
                scanf(" %c", &size[j]);

                if (size[j] == 84)
                {
                    money[j] = tea_mu_a8[0];
                }
                else if (size[j] == 71)
                {
                    money[j] = tea_mu_a8[1];
                }
                else if (size[j] == 86)
                {
                    money[j] = tea_mu_a8[2];
                }

                printf("수량 입력");
                scanf("%d", &num[j]);
                n++;
                te_sum += money[j] * num[j];
                continue;
            }
            else
                continue;

        case 7: // 계산
            getchar();
            printf("스타벅스 멤버쉽 할인을 적용 하시겠습니까? Y/N: ");
            scanf("%c", &k);

            if (k == 89)
            {
                printf("              최소 금액              할인율 \n");
                printf("Silver         10000                  5%%  \n");
                printf("Gold           20000                 15%%  \n");
                printf("VIP             없음                 15%%   \n");
                getchar();
                printf("원하시는 멤버쉽을 선택해 주세요 S, G, V: ");
                scanf("%c", &k);
                if (k == 83 && sum >= 10000)
                {
                    total = sum - (sum * 0.05);
                    printf("Silver 멤버쉽 5%%할인 적용하여 결제금액은 %d 입니다 \n", total);
                    sleep(3);
                    all_total += total;
                    i = 0;
                    j = 0;
                    n = 0;
                    continue;
                }
                else if (k == 71 && sum >= 20000)
                {
                    total = sum - (sum * 0.15);
                    printf("Gold 멤버쉽 15%%할인 적용하여 결제금액은 %d 입니다 \n", total);
                    sleep(3);
                    all_total += total;
                    i = 0;
                    j = 0;
                    n = 0;
                    continue;
                }
                else if (k == 86)
                {
                    total = sum - (sum * 0.15);
                    printf("VIP 멤버쉽 15%%할인 적용하여 결제금액은 %d 입니다 \n", total);
                    sleep(3);
                    all_total += total;
                    i = 0;
                    j = 0;
                    n = 0;
                    continue;
                }
                else
                    printf("최소금액을 충족하지 못하였습니다 \n");
                printf("결제 금액은 %d 입니다 \n", sum);
                all_total += sum;
                sleep(3);
                i = 0;
                j = 0;
                n = 0;
            }
            else
                printf("결제 금액은 %d 입니다 \n", sum);
            sleep(1);
            all_total += sum;
            i = 0;
            j = 0;
            n = 0;
            continue;

        case 8: // 매출정산
            printf("카테고리별 매출\n");
            printf("커피 : %d \n콜드브루 : %d \n프라푸치노 : %d \n블렌디드 : %d \n피지오 : %d \n티 : %d \n", cf_sum, cb_sum, fr_sum, bl_sum, ph_sum, te_sum);
            printf("1일 총매출 금액 : %d \n", all_total);
            sleep(3);
            break;

        default:
            continue;
        }
    }

    return 0;
}
