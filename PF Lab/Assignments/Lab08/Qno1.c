#include<stdio.h>
void displayPacks(){
    printf("-----Recharge Packs------\n");
    printf("1.Rs 100\n");
    printf("2.Rs 200\n");
    printf("3.Rs 500\n");
    printf("4.Rs 1000\n");
    printf("\n-------------------\n");    
}
int getPackChoice(){
    int choice;
    while(1){
        printf("Enter Pack number(1 to 4): ");
        scanf("%d",&choice);
        if(choice>=1 && choice<=4){
            break;
        }
        printf("Invalid choice number please enter correct\n");
    }
    return choice;
}
long long getMobileNumber(){
    long long mobile;
    while(1){
    printf("enter 11-digit mobile number : ");
    scanf("%lld",&mobile);
    if(mobile>=10000000000LL && mobile<=99999999999LL){
        break;
    }
    printf("Invalid choice number please enter 11 digit mobile number\n");
}
return mobile;
}
int packAmount(int packNum){
    int amount;
    switch(packNum){
        case 1:amount = 100;break;
        case 2:amount = 200;break;
        case 3:amount = 500;break;
        case 4:amount = 1000;break;
        default:amount=0;
    }
    return amount;
}
double calculateTax(int amount){
    return amount*0.15;
}
double calculateBonus(int amount){
    if(amount>=500){
        return amount*0.10;
    }
    return 0.0;
}
void printSlip(long long mobile,int amount,double tax,double totalBalance){
    printf("\n====Recharge Slip====\n");
    printf("Mobile Number : %lld\n",mobile);
    printf("Pack Amount : Rs %d\n",amount);
    printf("Tax (15%%) : Rs %.2f\n",tax);
    printf("Total Balance : Rs. %.2f\n",totalBalance);
    printf("=============================\n");
}
int main(){
    double totalSpent=0.0;
    for(int i=1;i<=3;i++){
       printf("Recharge %d of 3\n",i);
       displayPacks();
       int packNum=getPackChoice();
       long long mobile=getMobileNumber();
       int amount=packAmount(packNum);
       double tax=calculateTax(amount);
       double bonus=calculateBonus(amount);
       double totalBalance=amount+bonus;
       printSlip(mobile,amount,tax,totalBalance);
       totalSpent+=(amount + tax);
    }
    printf("Total money spent on 3 recharges : Rs %.2f\n",totalSpent);

}
