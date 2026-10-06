#include<stdio.h>

int main(){
    int notes500[5]={5,10,12,8,6};
    int notes200[5]={20,15,10,8,14};
    int notes100[5]={30,25,35,40,20};
    int i;
    int totalnotes500=0;
    int totalnotes200=0;
    int totalnotes100=0;
    int totalmoney;
    int withdrawlamount;

    for(i=0;i<5;i++){
        totalnotes500=totalnotes500+notes500[i];
    }
    for(i=0;i<5;i++){
        totalnotes200=totalnotes200+notes200[i];
    }
    for(i=0;i<5;i++){
        totalnotes100=totalnotes100+notes100[i];
    }
    totalmoney=(totalnotes500*500)+(totalnotes200*200)+(totalnotes100*100);
    printf("Total money: %d\n",totalmoney);

    printf("Enter withdrawl amount ");
    scanf("%d",&withdrawlamount);

    if(withdrawlamount>totalmoney){
        printf("Insufficient Amount\n");
    }
    else if(withdrawlamount%100!=0){
        printf("Invalid Amount\n");
    }
    else{
        printf("Transection approved");
    }



}