#include<stdio.h>
#define ROW 10
#define SEATS 4

int main(){
    int seats[ROW][SEATS]={0};
    int num_reservation,i=0,row,seat,r,s;
    int fully_booked_count=0;
    int fully_booked=0;
    int booked_row;
    printf("Enter number of seats you want to reserved");
    scanf("%d",&num_reservation);
    while(i<num_reservation){
    printf("\n--- Reservation %d ---\n", i + 1);
    printf("Enter on which row you want to seat (1 to 10)");
    scanf("%d",&row);
    if(row<1||row>10){
        printf("Invalid row number range");
        continue;
    }
    printf("Enter on which column you want to seat (1 to 4)");
    scanf("%d",&seat);
    if(seat<1||seat>4){
        printf("Invalid column number range");
        continue;
    }
    r=row-1;
    s=seat-1;

    if(seats[r][s]==1){
        printf("seats already booked");
        continue;
    }
    seats[r][s]=1;
    printf("seats reserved successfully");
    i++;
   }
   printf("      seat1  seat2  seat3  seat4\n");
   for(r=0;r<ROW;r++){
    printf("row%2d:   ",r+1);
    for(s=0;s<SEATS;s++){
        printf("  %d  ",seats[r][s]);
    }
    printf("\n");
   }
   printf("\nFully booked rows: ");
   for(r=0;r<ROW;r++){
    booked_row=0;
    for(s=0;s<SEATS;s++){
        if(seats[r][s]==1){
            booked_row++;
        }
    }
    if(booked_row==SEATS){
        fully_booked_count++;
        printf("%d",r+1);
        fully_booked=1;
    }
    
   }
   if(fully_booked==0){
        printf("none");
    }
   printf("\n");

   printf("Total number of fully booked rows: %d\n",fully_booked_count);

}