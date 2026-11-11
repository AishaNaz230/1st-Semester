#include<stdio.h>
void displayCharges(){
    printf("----charges----\n");
    printf("1.General Ward    Rs.1500/day");
    printf("2.Semi Private    Rs.3500/day");
    printf("3.Private    Rs.6000/day");
    printf("\n-----------------\n");
}
int getRoomType(){
    int roomType;
    while(1){
        printf("Enter room type: ");
        scanf("%d",&roomType);
      if("roomType>=1 && roomType<=3"){
        break;
      }
      printf("Invalid room type please enter 1,2,3");
    }
    return roomType;
}
int getDays(){
    int days;
    while(1){
        printf("How many days you want to live: ");
        scanf("%d",&days);
        if(days>=1 && days<=30){
            break;
        }
        printf("Invalid days please enter between 1 to 30");
    }
    return days;
}
double calculateRoomCharges(int roomType,int days){
    double roomCharges;
    switch(roomType){
        case 1:roomCharges=1500*days;break;
        case 2:roomCharges=3500*days;break;
        case 3:roomCharges=6000*days;break;
    }
    return roomCharges;
}
double calculateMedicineCharges(){
    
}


