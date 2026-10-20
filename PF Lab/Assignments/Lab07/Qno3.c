#include<stdio.h>

#define SALESMAN 4
#define PRODUCT 5

int main(){
    int sales[SALESMAN][PRODUCT];
    int salesman_total[SALESMAN];
    int products_total[PRODUCT];
    float final_amount[SALESMAN];
    int bonus_applied[SALESMAN];
    int i,j,max_product,max_sales;
    float bonus;

    printf("4 salesman x 5 products\n");

    for(i=0;i<SALESMAN;i++){
        printf("salesman: %d\n",i+1);
        for(j=0;j<PRODUCT;j++){
            printf("   sales of product %d: Rs ",j+1);
            scanf("%d",&sales[i][j]);
        }
    }
    for(i=0;i<SALESMAN;i++){
        salesman_total[i]=0;
        for(j=0;j<PRODUCT;j++){
            salesman_total[i]=salesman_total[i]+sales[i][j];
        }
        printf("salesman %d: Rs %d\n",i+1,salesman_total[i]);
    }
    for(j=0;j<PRODUCT;j++){
        products_total[j]=0;
        for(i=0;i<SALESMAN;i++){
             products_total[j]= products_total[j]+sales[i][j];
        }
        printf("products %d: Rs %d\n",j+1,products_total[j]);
    }
    max_product=0;
    max_sales=products_total[0];
    for(j=1;j<PRODUCT;j++){
        if(products_total[j]>max_sales){
            max_sales=products_total[j];
            max_product=j;
        }
    }
    printf("product %d with total sales of Rs.%d\n",max_product+1,max_sales);

    for(i=0;i<SALESMAN;i++){
        if(salesman_total[i]>10000){
            bonus=salesman_total[i]*0.10;
            final_amount[i]=salesman_total[i]+bonus;
            bonus_applied[i]=1;
            printf("Salesman %d: Bonus=Rs %.2f\n ",i+1,bonus);
        }
        else{
            final_amount[i]=salesman_total[i];
            bonus_applied[i]=0;
             printf("Salesman %d: NO Bonus (sales<=10000)\n ",i+1);
        }
    }
    printf("\n------SUMMARY------\n");
    printf("%15s %15s %15s %18s\n","salesman","total_sales","bonus","final_amount");

    for(i=0;i<SALESMAN;i++){
        printf("salesman %-5d %15d",i+1,salesman_total[i]);
        if(bonus_applied[i]){
            printf("%15s","10% applied");
        }
        else{
            printf("%15s","None");
        }
        printf("%18.2f\n",final_amount[i]);
    }
    for(j=0;j<PRODUCT;j++){
        printf("product %d:Rs. %d",j+1,products_total[j]);
        if(j==max_product){
            printf(" <...Most Expensive\n");
        }
        printf("\n");
    }
    printf("Most Expensive product : product %d(Rs %d)\n",max_product+1,max_sales);
}