#include<stdio.h>

int main(){
    int stock[10];
    int minimum[10];
    int i;
    int reorder;
    int largest_reorder=0;
    int largest_product=0;
    int total_reorder=0;

    printf("Enter stock quantity for 10 products\n");

    for(i=0;i<10;i++){
        printf("product %d ",i+1);
        scanf("%d",&stock[i]);
    }

    printf("Enter minimum quantity for 10 products\n");

    for(i=0;i<10;i++){
        printf("product %d ",i+1);
        scanf("%d",&minimum[i]);
    }
    printf("The products that need reordering \n");

    for(i=0;i<10;i++){
        if(stock[i]<minimum[i]){
            reorder=minimum[i]-stock[i];
            printf("product %d: order %d units\n",i+1,reorder);
            total_reorder=total_reorder+reorder;
        
        if(reorder>largest_reorder){
            largest_reorder=reorder;
            largest_product=i;
        }
    }
    }
    printf("Largest reorder: product %d\n",largest_product+1);
    printf("Largest reorder quantity : %d units\n",largest_reorder);
    printf("Total reorder quantity : %d units\n",total_reorder);
}