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
    double medicine_bill;
    printf("Enter medicine bill: Rs. ");
    scanf("%lf", &medicine_bill);
    double medicine_charge = medicine_bill + (medicine_bill * 0.05);
    return medicine_charge;
}

double calculateFinalBill(double roomCharges, double medicine_charge, int days){
    double total = roomCharges + medicine_charge;
    double finalBill;
    if(days >= 7){
        finalBill = total - (total * 0.08);
    }
    else{
        finalBill = total;
    }
    return finalBill;
}

double checkSeniorCitizen(double finalBill){
    char seniorCheck;
    double finalAmount = finalBill;
    
    printf("Is the patient a senior citizen? (y/n): ");
    scanf(" %c", &seniorCheck);
    
    if(seniorCheck == 'y' || seniorCheck == 'Y'){
        finalAmount = finalBill - 1000;
        if(finalAmount < 0){
            finalAmount = 0;
        }
    }
    else if(seniorCheck == 'n' || seniorCheck == 'N'){
        finalAmount = finalBill;
    }
    else{
        printf("Invalid input! Assuming not a senior citizen.\n");
        finalAmount = finalBill;
    }
    return finalAmount;
}

void printBill(int roomType, int days, double roomCharges, double medicineCharge, double finalBill){
    printf("\n====== HOSPITAL BILL ======\n");
    switch(roomType){
        case 1: printf("Room Type     : General Ward\n"); break;
        case 2: printf("Room Type     : Semi Private\n"); break;
        case 3: printf("Room Type     : Private\n"); break;
    }
    printf("Days Stayed   : %d\n", days);
    printf("Room Charges  : Rs. %.2f\n", roomCharges);
    printf("Medicine Charge: Rs. %.2f\n", medicineCharge);
    printf("Final Bill    : Rs. %.2f\n", finalBill);
    printf("===========================\n");
}

int main(){
    char choice;
    int patientCount = 0;
    
    printf("=== Welcome to City Care Hospital Billing System ===\n");
    
    do{
        patientCount++;
        printf("\n*** Patient #%d ***\n", patientCount);
        
        displayCharges();
        int roomType = getRoomType();
        int days = getDays();
        double roomCharges = calculateRoomCharges(roomType, days);
        double medicineCharge = calculateMedicineCharges();
        double finalBill = calculateFinalBill(roomCharges, medicineCharge, days);
        finalBill = checkSeniorCitizen(finalBill);
        printBill(roomType, days, roomCharges, medicineCharge, finalBill);
        
        printf("\nAdd another patient? (y/n): ");
        scanf(" %c", &choice);
        
    } while(choice == 'y' || choice == 'Y');
    
    printf("\n=== Total patients processed: %d ===\n", patientCount);
    printf("Thank you for using our billing system!\n");
}


