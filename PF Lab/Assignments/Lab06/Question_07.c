#include<stdio.h>

int main(){
    int original;
    int number;
    int reversed=0;
    int digit;

    printf("Enter number: \n");
    scanf("%d",&number);

    original=number;

    while(number!=0){
        digit=number%10;
        reversed=reversed*10+digit;
        number=number/10;
    }
    printf("Reversed : %d\n",reversed);

    if(reversed==original){
        printf("Pallindrome confirmed\n");
    }
    else{
        printf("Not a Pallindrome\n");
    }
}