#include<stdio.h>

void displayRoutes(){
    printf("\n---- Bus Routes ----\n");
    printf("1. Karachi to Hyderabad  Rs. 800\n");
    printf("2. Karachi to Sukkur     Rs. 2200\n");
    printf("3. Karachi to Multan     Rs. 3500\n");
    printf("---------------------\n");
}

int getRouteNumber(){
    int routeNumb;
    while(1){
        printf("Enter route number (1-3): ");
        scanf("%d", &routeNumb);
        if(routeNumb >= 1 && routeNumb <= 3){
            break;
        }
        printf("Invalid input! Please enter 1, 2, or 3.\n");
    }
    return routeNumb;
}

int getNumberOfSeats(){
    int seatNumb;
    while(1){
        printf("Enter number of seats (1-6): ");
        scanf("%d", &seatNumb);
        if(seatNumb >= 1 && seatNumb <= 6){
            break;
        }
        printf("Invalid input! Please enter between 1 to 6.\n");
    }
    return seatNumb;
}

int getSeatFare(int routeNumb){
    int fare;
    switch(routeNumb){
        case 1: fare = 800;  break;
        case 2: fare = 2200; break;
        case 3: fare = 3500; break;
        default: fare = 0;
    }
    return fare;
}

int calculateTotalFare(int fare, int seatNumb){
    return fare * seatNumb;
}

double calculateFinalFare(int totalFare, char seatType){
    double finalFare;
    if(seatType == 'E' || seatType == 'e'){
        finalFare = totalFare;
    }
    else if(seatType == 'B' || seatType == 'b'){
        finalFare = totalFare + (totalFare * 0.30);
    }
    else{
        printf("Invalid seat type! Defaulting to Economy.\n");
        finalFare = totalFare;
    }
    return finalFare;
}

void printTicket(int routeNumb, int seatNumb, char seatType, double finalFare){
    printf("\n====== TICKET ======\n");
    switch(routeNumb){
        case 1: printf("Route     : Karachi to Hyderabad\n"); break;
        case 2: printf("Route     : Karachi to Sukkur\n"); break;
        case 3: printf("Route     : Karachi to Multan\n"); break;
    }
    printf("Seats     : %d\n", seatNumb);
    printf("Seat Type : %c\n", seatType);
    printf("Final Fare: Rs. %.2f\n", finalFare);
    printf("====================\n");
}

