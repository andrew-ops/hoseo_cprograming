/*
1. 총 5개의 상품을 판매한다.(추후 확대 할 예정이다.)
2. 5개의 상품 별 입고, 판매, 재고수량 관리를 진행한다.
3. 초기 입고, 판매, 재고 수량은 모두 0으로 설정한다.
4. 프로그램이 실행되면 아래의 메뉴를 반복적으로 보여주며, 해당 메뉴
를 동작시킨다.
1. 입고 >> 상품의 입고수량을 입력한다.
2. 판매 >> 상품의 판매수량을 입력한다.
3. 상품현황
4. 프로그램 종료
*/
#include<stdio.h>
#include<string.h>
#define type 5

int inbound(int *totalstk,int *buyamount)
{
    int j = 1;
    while(j == 1)
        {
        printf("입고수량 입력 : 전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택하세요. ");
        int choice;
        int amount = 0;
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("전체 상품 입고수량 입력 : ");
            scanf("%d", &amount);
            for (int i = 0; i < type; i++)
            {
                totalstk[i] += amount;
                *buyamount += amount;
            }
            j=0;
        }
        else if (choice == 2)
        {
            printf("상품ID:");
            int id;
            scanf("%d", &id);
                    if(id < 1 || id > type)
            {
                printf("잘못된 상품ID입니다.\n 1~%d 사이의 값을 입력하세요.\n", type);
                return 0;
            }

            else
            {
                printf("입고수량");
                scanf("%d", &amount);
                *buyamount += amount;
                totalstk[id - 1] += amount;
            }
            j=0;
        }
        else
        {
            printf("잘못된 선택입니다.\n 다시 시도하세요\n");
            j=1;
        }
    }
    return 0;
}


int outbound(int *totalstk,int *sellamount)
{
    int j = 1;
    while(j == 1)
    {
        printf("판매수량 입력 : 전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택하세요. ");
        int choice;
        int amount = 0;
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("전체 상품 판매수량 입력 : ");
            scanf("%d", &amount);
            for (int i = 0; i < type; i++)
            {
                totalstk[i] -= amount;
                sellamount[i] += amount;
            }
            j=0;
        }
        else if (choice == 2)
        {
            printf("상품ID:");
            int id;
            scanf("%d", &id);
            printf("판매수량");
            scanf("%d", &amount);
            if(id < 1 || id > type)
            {
                printf("잘못된 상품ID입니다.\n 1~%d 사이의 값을 입력하세요.\n", type);
                return 0;
            }
            else
            {
                totalstk[id - 1] -= amount;
                sellamount[id - 1] += amount;
            }
            j=0;
        }
        else
        {
            printf("잘못된 선택입니다.\n 다시 시도하세요\n");
            j=1;
        }
    }
    return 0;
}


int lowlevelwarning(int *totalstk, char name[type][100])
{
    for(int i = 0; i < type; i++)
    {
        if(totalstk[i] <= 2)
        {
            printf("상품ID %d:상품명:%s 재고부족(%d)\n", i + 1, name[i], totalstk[i]);
        }
    }
    return 0;
}


void stockstatus(int *totalstk,int *sellamount,int buyamount,char name[type][100])
{
    int max = 0;
    int min = 0;
    int totalSales = 0;
    printf("재고수량:\n");
    for(int i = 0; i < type; i++)
    {
        printf("%d\t", totalstk[i]);
    }
    printf("\n");
    for(int i = 0; i < type; i++)
    {
        if(sellamount[i] > sellamount[max])
        {
            max = i;
        }
        if(sellamount[i] < sellamount[min])
        {
            min = i;
        }
        totalSales += sellamount[i];
    }
    float rate = 0;
    if(totalSales > 0)
    {
        rate = (float)totalSales / (float)buyamount * 100;
    }
    else
    {
        rate = 0;
    }
    printf("\n총 판매량 : %d(판매율 : %.2f%%)\n", totalSales, rate);
    if(min==max)
    {
        printf("모든 상품의 판매량이 같습니다.\n");
        return;
    }
    printf("가장 많이 판매된 상품 : ID %d, 상품명:%s 판매량 %d\n", max + 1, name[max], sellamount[max]);
    printf("가장 적게 판매된 상품 : ID %d, 상품명:%s 판매량 %d\n", min + 1, name[min], sellamount[min]);
    lowlevelwarning(totalstk, name);

}
/*
재고수량 : 3 3 2 0 5
총 판매량 : 16 (판매율 55.17%)
가장 많이 판매된 상품 : ID 1, 판매량 5
가장 적게 판매된 상품 : ID 3, 판매량 1
상품 ID 3 : 재고부족(2)
상품 ID 4 : 재고부족(0)
원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 상품현황. 4. 종료)
*/
void stockname(int *totalstk, char name[][100])
{
    for(int i = 0; i < type; i++)
    {
        printf("상품ID %d 상품명 입력 : ", i + 1);
        scanf("%99s", name[i]);
    }
}
/*
원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 상품현황. 4. 상품명 입력, 5. 종료)
4 << 상품명입력 메뉴 실행
(출력) ID 1 상품명 : (입력)상품명1
(출력) ID 2 상품명 : (입력)상품명2
(출력) ID 3 상품명 : (입력)상품명3
(출력) ID 4 상품명 : (입력)상품명4
(출력) ID 5 상품명 : (입력)상품명5 
*/
int main()
{
    int totalstock[type] = {0,};
    int *totalstk = totalstock;
    int totalSales = 0;
    int buyamount = 0;
    int *pbuyamount = &buyamount;
    int sellamount[type] = {0,};
    char name[type][100] = {

        {"test1"},
        {"test2"},
        {"test3"},
        {"test4"},
        {"test5"}
    };
    int i = 1;
    while(i == 1)
    {
        int menu;
        printf("원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 상품현황. 4. 상품명 입력, 5. 종료) ");
        scanf("%d",&menu);
        switch(menu)
        {
            case 1:
                inbound(totalstk,pbuyamount);
                break;
            case 2:
                outbound(totalstk,sellamount);
                break;
            case 3:
                stockstatus(totalstk,sellamount,buyamount,name);
                break;
            case 4:
                stockname(totalstk, name);
                break;
            case 5:
                i = 0;
                break;
            default:
                printf("잘못된 메뉴입니다. 다시 입력해 주세요\n");
        }

    }
}