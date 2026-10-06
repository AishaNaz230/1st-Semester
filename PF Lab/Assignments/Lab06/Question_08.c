#include<stdio.h>

int main(){
    int seat[15]={1,0,1,0,0,1,1,0,1,0,0,1,0,1,0};
    int i;
    int booking=0;
    int empty=0;
    int first=-1;
    int last=-1;
    int count=0;

    for(i=0;i<15;i++){
       if(seat[i]==1){
        booking=booking+1;
       }
       else{
        empty=empty+1;
       }
    }
    printf("booked seats: %d\n",booking);
    printf("empty seats: %d\n",empty);

    for(i=0;i<15;i++){
        if(seat[i]==0){
            if(first==-1){
                first=i+1;
            }
            last=i+1;
        }
    }
    if(first!=-1){
        printf("first available seats: %d\n",first);
        printf("last available seats: %d\n",last);
    }
    else{
        printf("No seats available\n");
    }
    for(i=0;i<15&&count<3;i++){
        if(seat[i]==0){
            seat[i]=1;
            count++;
        }
    }
    printf("Final seating plan chart\n");

    for(i=0;i<15;i++){
        printf("Seats %d : %d\n",i+1,seat[i]);
    }

}