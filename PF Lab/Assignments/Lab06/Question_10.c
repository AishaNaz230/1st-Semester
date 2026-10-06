#include<stdio.h>

int main(){
    int amount;
    int transaction=0;
    int total=0;

    while(1){
        printf("Enter withdrawl amount(0 to exit):\n");
        scanf("%d",&amount);

        if(amount==0){
            break;
        }
        printf("Transaction processed : %d\n",amount);

        transaction++;
        total=total+amount;
    }
    printf("ATM Session Ended\n");
    printf("Total transaction : %d\n",transaction);
    printf("Total amount withdraw : %d\n",total);

}