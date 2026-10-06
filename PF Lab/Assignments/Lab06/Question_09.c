#include<stdio.h>

int main(){
    int transfers[10] = {5000, 50, 12000, 500000, 20, 8000, 25000, 300, 450000, 15000};
    int i;
    int largest;
    float average;
    int flagged=0;
    int normal_count=0;
    int sum=0;

    largest=transfers[0];

    for(i=0;i<10;i++){

        if(transfers[i]<100){
           printf("Transfer %d : Too small\n",i+1);
           flagged++;
        }
        else if(transfers[i]>200000){
            printf("Transfer %d : Too large\n",i+1);
            flagged++;
        }
        else{
            sum=sum+transfers[i];
            normal_count++;
        }
    
    if(transfers[i]>largest){
        largest=transfers[i];
    }
}
    average=(float)sum/normal_count;

    printf("Total flagged transfer:%d\n",flagged);
    printf("Average of normal transfers:%.2f\n",average);
    printf("Largest tranfer:%d",largest);
}