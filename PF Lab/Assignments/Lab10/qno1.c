#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *fp;
    int item_num,quantity,stock,id;
    char name[50];
    float price;
    float total_bill=0.0;
    fp = fopen("items.txt","wb");
    if(fp==NULL){
        return 1;
    }
    fprintf(fp, "%-4d %-20s %9.2f %5d\n",1,"Rice",250.00,40);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 2, "Sugar", 160.00, 25);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 3, "Milk", 220.00, 30);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 4, "CookingOil", 560.00, 12);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 5, "Tea", 450.00, 18);
    fclose(fp);
    fp = fopen("items.txt","rb+");
    if(fp==NULL){
        return 1;
    }
    while(1){
        printf("item no: ");
        scanf("%d",&item_num);
        if(item_num==0){
            break;
        }
        printf("Quantity: ");
        scanf("%d",&quantity);
        fseek(fp,(item_num-1)*42,SEEK_SET);
        fscanf(fp,"%d %s %f %d",&id,name,&price,&stock);
        if(quantity<=stock){
            printf("%s %d x %.2f = %.2f\n", name, quantity, price, quantity * price);
            total_bill+=quantity*price;
            stock=stock-quantity;
            fseek(fp,(item_num-1)*42,SEEK_SET);
            fprintf(fp,"%-4d %-20s %9.2f %5d\n",id,name,price,stock);
        }
        else{
            printf("Only %d %s in stock\n", stock, name);
        }
    }
    printf("Total bill: %.2f\n",total_bill);
    fclose(fp);
}
