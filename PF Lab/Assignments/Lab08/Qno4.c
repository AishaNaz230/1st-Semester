#include <stdio.h>
#include <stdlib.h>

void displayFareRules(){
    printf("\n----- Taxi Fare Rules -----\n");
    printf("Base Fare: Rs. 150\n");
    printf("First 10 km: Rs. 60 per km\n");
    printf("After 10 km: Rs. 45 per km\n");
    printf("Waiting: First 5 minutes free, then Rs. 10/min\n");
    printf("Night Charge: 25%% extra from 10 PM to 6 AM\n");
    printf("---------------------------\n");
}

double getDistance(){
    double distance;
    while(1){
        printf("Enter distance (0 to 200 km): ");
        scanf("%lf", &distance);
        if(distance > 0 && distance <= 200){
            break;
        }
        printf("Invalid! Please enter between 0 to 200.\n");
    }
    return distance;
}

int getWaitingTime(){
    int waitingTime;
    while(1){
        printf("Enter waiting time (0 to 120 minutes): ");
        scanf("%d", &waitingTime);
        if(waitingTime >= 0 && waitingTime <= 120){
            break;
        }
        printf("Invalid! Please enter between 0 to 120.\n");
    }
    return waitingTime;
}

double calculateDistanceCharge(double distance){
    if(distance <= 10)
        return distance * 60;
    else
        return 10 * 60 + (distance - 10) * 45;
}

double calculateWaitingCharge(int waitingTime){
    if(waitingTime <= 5)
        return 0;
    else
        return (waitingTime - 5) * 10;
}

double addNightCharge(double fare){
    int hour;
    while(1){
        printf("Enter hour of trip (0 to 23): ");
        scanf("%d", &hour);
        if(hour >= 0 && hour <= 23){
            break;
        }
        printf("Invalid! Please enter between 0 to 23.\n");
    }
    
    if(hour >= 22 || hour < 6){
        fare = fare * 1.25;
    }
    return fare;
}

void printReceipt(double distance, int waitingTime, double finalFare){
    printf("\n----- Trip Receipt -----\n");
    printf("Distance      : %.2f km\n", distance);
    printf("Waiting Time  : %d minutes\n", waitingTime);
    printf("Final Fare    : Rs. %.2f\n", finalFare);
    printf("------------------------\n");
}

int main(){
    double totalEarnings = 0.0;
    double highestFare = 0.0;
    
    for(int i = 1; i <= 3; i++){
        printf("\n*** Trip %d ***\n", i);
        
        displayFareRules();
        double distance = getDistance();
        int waitingTime = getWaitingTime();
        
        double distanceCharge = calculateDistanceCharge(distance);
        double waitingCharge = calculateWaitingCharge(waitingTime);
        double fare = 150 + distanceCharge + waitingCharge;
        double finalFare = addNightCharge(fare);
        
        printReceipt(distance, waitingTime, finalFare);
        
        totalEarnings += finalFare;
        
        if(finalFare > highestFare){
            highestFare = finalFare;
        }
    }
    
    printf("\n*** Total earnings: Rs. %.2f ***\n", totalEarnings);
    printf("*** Highest fare of the day: Rs. %.2f ***\n", highestFare);
    
    return 0;
}