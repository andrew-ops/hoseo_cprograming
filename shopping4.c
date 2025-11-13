#include<stdio.h>
#include<string.h>
#include<string.h>

#define type 5

struct gift{
    int id[type];
    char name[type][99];
    int stk[type];
    int ibamt[type];
    int totalibamt;
    int obamt[type];
    int available[type];
    int price[type];
    int totalsellprice[type];
};

struct gift g = {0, };

void inbound(void);
int sameid(void);
void editgiftinfo(void);

void outbound();

void eachstat();

int low_lv_warn();
void allstat();

void save();
void load();

int main(){
    int num = 0,z = 0;
    while (z == 0){
        printf("원하는 메뉴를 선택하세요. 1.입고 2.출고 3.개별현황 4.전체현황 5.저장 6.불러오기 7.제품정보 변경 8.종료 \n");
        scanf("%d",&num);
        
        switch (num){
        case 1:
            inbound();
            z = 0;
            break;
        case 2:
            outbound();
            z = 0;
            break;
        case 3:
            eachstat();
            z = 0;
            break;
        case 4:
            allstat();
            z = 0;
            break;
        case 5:
            save();
            z = 0;
            break;
        case 6:
            load();
            z = 0;
            break;
        case 7:
            editgiftinfo();
            z = 0;
            break;
        case 8:
            z = 1;
            break;
        default:
            printf("잘못된 입력입니다. 다시 입력해 주세요\n");
            z = 0;
            break;

        }
        
    }
}

int sameid(void){
    int id = 0;
    printf("상품 ID: ");
    scanf("%d",&id);
    for(int i = 0; i<=type;i++){
        if(g.id[i]==id) return i;
    }
    return -(id+1);
}

void inbound(void){
    int ibamt = 0;
    int same = sameid();
    if(same <0)
    {
        for(int i = 0; i<=type;i++)
        {
            if(g.available[i] == 0)
            {
                g.id[i]=-(same+1);
                g.available[i]=1;
                same=i;
                break;
            }
        }
        if(same<0){
            printf("더 이상 물품을 추가할 수 없습니다.\n");
            return;
        }
        printf("상품명");
        scanf("%s", g.name[same]);/*이미 있는 아이디 경우 상품명 &상품가격 물어보지 않게*/ 
        printf("입고량");
        scanf("%d", &ibamt);
        printf("판매가격");
        scanf("%d", &g.price[same]);
    }
    else{
        printf("입고량");
        scanf("%d",&ibamt);
    }
    g.ibamt[same]+=ibamt;
    g.totalibamt+=ibamt;
    g.stk[same]+=ibamt;
}
void editgiftinfo(void){
    int same;
    same = sameid();
    if(same < 0){
        printf("잘못된 입력입니다. 존재하는 ID를 입력해 주세요\n");
    }
    else{
        printf("상품명");
        scanf("%s", g.name[same]);
        printf("판매가격");
        scanf("%d", &g.price[same]);
    }
}

void outbound(){
    int same,obamt;
    same = sameid();
    if(same < 0){
        printf("잘못된 입력입니다. 존재하는 ID를 입력해 주세요\n");
    }
    else{
        printf("판매량");
        scanf("%d",&obamt);
        g.stk[same]-=obamt;
        g.obamt[same]+=obamt;
        g.totalsellprice[same]+=(g.price[same]*obamt);
    }
}

void eachstat(){//상품 ID(일련번호), 상품명, 상품가격, 입고량, 판매량, 총판매금액
    int same;
    same=sameid();
    if(same < 0){
        printf("잘못된 입력입니다. 존재하는 ID를 입력해 주세요 \n");
    }
    else    printf("상품 ID:%d \n상품명:%s \n상품가격:%d \n입고량:%d \n판매량:%d \n총 판매금액:%d \n",g.id[same],g.name[same],g.price[same],g.ibamt[same],g.obamt[same],g.totalsellprice[same]);
}

int low_lv_warn(){
    for(int i = 0; i < type; i++)
    {
        if(g.stk[i] <= 2)
        {
            printf("상품ID %d:상품명:%s 재고부족(%d)\n", g.id[i], g.name[i],g.stk[i]);
        }
    }
    return 0;
}

void allstat(){
    int max = 0,min = 0,totalSales = 0,totalib;
    float rate = 0;
    printf("재고수량:\n");
    for(int i = 0; i < type; i++){
        printf("%d %d개 \n",i+1, g.stk[i]);
        totalSales += g.obamt[i];
    }
    printf("\n");
    for(int i = 0; i < type; i++){
        if(g.obamt[i] > g.obamt[max]){
            max = i;
        }
        if(g.obamt[i] < g.obamt[min]){
            min = i;
        }

    }

    if(totalSales > 0){
        rate = ((float)totalSales / (float)g.totalibamt)* 100.0;
    }
    else{
        rate = 0;
    }
    printf("\n총 판매량 : %d(판매율 : %.2f%%)\n", totalSales, rate);//100%판매율이 -0.00%로 뜸 문제 있음 이거
    if(min==max){
        printf("모든 상품의 판매량이 같습니다.\n");
        return;
    }
    printf("가장 많이 판매된 상품 : ID %d, 상품명:%s 판매량 %d\n", g.id[max], g.name[max], g.obamt[max]);
    printf("가장 적게 판매된 상품 : ID %d, 상품명:%s 판매량 %d\n", g.id[min], g.name[min], g.obamt[min]);
    low_lv_warn();
}
void save(){
    FILE *fp = NULL;
    fp = fopen("gift.dat","wb");
    if(fp == NULL){
        printf("파일 열기 오류\n");
        return;
    }
    fwrite(&g, sizeof(struct gift), 1, fp);
    printf("저장 완료\n");
    fclose(fp);

}
void load(){
    FILE *fp = NULL;
    fp = fopen("gift.dat","rb");
    if(fp == NULL){
        printf("파일 열기 오류\n");
        return;
    }
    printf("불러오기 완료\n");
    fread(&g, sizeof(struct gift), 1, fp);
    fclose(fp);
}