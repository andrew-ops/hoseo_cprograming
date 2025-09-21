/*
쇼핑몰 재고 관리 #1의 입력 요구사항은 그대로 진행한다. 상품 개
수, 상품 별 입고수량 입력, 상품 별 판매수량 입력
2. 아래의 항목을 출력한다.
- 모든 상품의 재고 수량 출력
- 전체 판매량 계산 : 모든 상품의 판매량을 합산하여 출력
- 전체 판매율 계산 : (판매수량/입고수량)*100 출력
- 최대 판매량 및 최소 판매량 상품 출력 : ID와 판매량 출력
- 재고 부족 경고 : 특정 상품의 재고 수량이 2 이하일 때 경고 출력
*/


#include<stdio.h>

int input(int *pib,int *pob,int type)
{
    for(int i=0;i<type;i++)//ib input
    {
        scanf("%d",&pib[i]);
    }
    for(int i=0;i<type;i++)//ob input
    {
        scanf("%d",&pob[i]);
    }
}

int remainstock(int *pib,int *pob,int type)
{
    for(int i=0;i<type;i++)
    {
        printf("%d ",*(pib+i)-*(pob+i));
    }
    return 0;
}

int totalsell(int *pib,int *pob,int type)
{
    int total_ib = 0;

    for(int i = 0; i < type; i++)
    {
        total_ib = total_ib + *(pib + i);
    }

    int total_ob = 0;
    for(int i = 0; i < type; i++)
    {
        total_ob = total_ob + *(pob + i);
    }
    //판매율 (판매수량/입고수량)*100
    float rate = 0;
    if(total_ob > 0)
    {
        rate = (float)total_ob / (float)total_ib * 100;
    }
    else
    {
        rate = 0;
    }
    printf("\n전체 판매량 : %d, 전체 판매율 : %.2f%%\n", total_ob, rate);
    }

int mostsell(int *pib,int *pob,int type)
{
    int max = *(pob + 0);
    int index = 0;
    for(int i = 1; i < type; i++)
    {
        if(max < *(pob + i))
        {
            max = *(pob + i);
            index = i;
        }
    }
    printf("최대 판매량 상품ID : %d, 판매량 : %d\n", index + 1, max);
    return index + 1;
}

int lesssell(int *pib,int *pob,int type)
{
    int min = *(pob + 0);
    int index = 0;
    for(int i = 1; i < type; i++)
    {
        if(min > *(pob + i))
        {
            min = *(pob + i);
            index = i;
        }
    }
    printf("최소 판매량 상품ID : %d, 판매량 : %d\n", index + 1, min);
    return index + 1;
}
int lowlevelwarning(int *pib,int *pob,int type)
{
    for(int i = 0; i < type; i++)
    {
        if((*(pib + i) - *(pob + i)) <= 2)
        {
            printf("상품ID %d 재고부족(%d)\n", i + 1, *(pib + i) - *(pob + i));
        }
    }
    return 0;
}
int main()
{
    int type;
    scanf("%d",&type);
    if(type<1 || type>100)
    {
        printf("Invalid Input");
        return 0;
    }
    int ib[type],ob[type];//ib=inbound ob=outbound
    int *pib=ib;
    int *pob=ob;
    input(pib,pob,type);
    remainstock(pib,pob,type);
    totalsell(pib,pob,type);
    mostsell(pib,pob,type);
    lesssell(pib,pob,type);
    lowlevelwarning(pib,pob,type);


}