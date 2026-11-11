#include<stdio.h>

int main(){
    double costPrice;
    double sellPrice;
    double quantity;
    
    double *ptrCP = &costPrice;
    double *ptrSP = &sellPrice;
    double *ptrQty = &quantity;
    
    printf("Enter cost price: ");
    scanf("%lf", ptrCP);
    
    printf("Enter selling price: ");
    scanf("%lf", ptrSP);
    
    printf("Enter quantity: ");
    scanf("%lf", ptrQty);
    
    double totalCost;
    double totalSales;
    double profitLoss;
    
    double *ptrtotalCost = &totalCost;
    double *ptrtotalSales = &totalSales;
    double *ptrprofit = &profitLoss;
    
    *ptrtotalCost = (*ptrCP) * (*ptrQty);
    *ptrtotalSales = (*ptrSP) * (*ptrQty);
    *ptrprofit = (*ptrtotalSales) - (*ptrtotalCost);
    
    printf("\n------ RESULT ------\n");
    printf("Total Cost  : Rs. %.2f\n", *ptrtotalCost);
    printf("Total Sales : Rs. %.2f\n", *ptrtotalSales);
    
    if(*ptrprofit > 0){
        printf("Status: Profit\n");
    }
    else if(*ptrprofit < 0){
        printf("Status: Loss\n");
    }
    else{
        printf("Status: No profit no loss\n");
    }
    
    double profitPercent;
    double *ptrPercent = &profitPercent;
    
    if(*ptrtotalCost != 0){
        *ptrPercent = (*ptrprofit / *ptrtotalCost) * 100;
        printf("Profit/Loss : Rs. %.2f\n", *ptrprofit);
        printf("Percentage  : %.2f%%\n", *ptrPercent);
    }
    else{
        printf("Cannot calculate percentage\n");
    }
    
    double *ptrLarger;
    if(*ptrCP > *ptrSP){
        ptrLarger = ptrCP;
    }
    else{
        ptrLarger = ptrSP;
    }
    
    printf("\n------ LARGER VALUE ------\n");
    if(ptrLarger == ptrCP){
        printf("Larger is costPrice: %.2f\n", *ptrLarger);
    }
    else{
        printf("Larger is sellPrice: %.2f\n", *ptrLarger);
    }
    
    printf("\n------ ADDRESS TABLE ------\n");
    printf("\n--- Variables ---\n");
    printf("costPrice     %p\n", (void*)&costPrice);
    printf("sellPrice     %p\n", (void*)&sellPrice);
    printf("quantity      %p\n", (void*)&quantity);
    printf("totalCost     %p\n", (void*)&totalCost);
    printf("totalSales    %p\n", (void*)&totalSales);
    printf("profitLoss    %p\n", (void*)&profitLoss);
    printf("profitPercent %p\n", (void*)&profitPercent);
    
    printf("\n--- Pointers ---\n");
    printf("ptrCP         %p\n", (void*)ptrCP);
    printf("ptrSP         %p\n", (void*)ptrSP);
    printf("ptrQty        %p\n", (void*)ptrQty);
    printf("ptrtotalCost  %p\n", (void*)ptrtotalCost);
    printf("ptrtotalSales %p\n", (void*)ptrtotalSales);
    printf("ptrprofit     %p\n", (void*)ptrprofit);
    printf("ptrPercent    %p\n", (void*)ptrPercent);
    printf("ptrLarger     %p\n", (void*)ptrLarger);
    
    return 0;
}