#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    
    while(1) {
        printf("Enter number of days (1 to 10): ");
        scanf("%d", &n);
        if(n >= 1 && n <= 10) {
            break;
        }
        printf("Invalid! Please enter between 1 to 10.\n");
    }
    
    double *temp = (double *)malloc(n * sizeof(double));
    
    if(temp == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    for(int i = 0; i < n; i++) {
        while(1) {
            printf("Enter temperature for Day %d (-10 to 55): ", i + 1);
            scanf("%lf", &temp[i]);
            if(temp[i] >= -10 && temp[i] <= 55) {
                break;
            }
            printf("Invalid! Temperature must be between -10 and 55.\n");
        }
    }
    
    printf("\n------ TEMPERATURES ------\n");
    for(int i = 0; i < n; i++) {
        printf("Day %d: %.2f at address %p\n", i + 1, temp[i], (void*)&temp[i]);
    }
    
    double *ptr = temp;
    double hottest = *ptr;
    double coldest = *ptr;
    
    for(int i = 0; i < n; i++) {
        if(*ptr > hottest) {
            hottest = *ptr;
        }
        if(*ptr < coldest) {
            coldest = *ptr;
        }
        ptr++;
    }
    
    printf("\n------ EXTREMES ------\n");
    printf("Hottest temperature: %.2f\n", hottest);
    printf("Coldest temperature: %.2f\n", coldest);
    
    ptr = temp;
    int count = 0;
    
    for(int i = 0; i < n; i++) {
        if(*ptr > 40) {
            count++;
        }
        ptr++;
    }
    
    printf("\n------ HOT DAYS ------\n");
    printf("Days hotter than 40: %d\n", count);
    
    free(temp);
    temp = NULL;
    
    printf("\n------ MEMORY STATUS ------\n");
    printf("Memory has been successfully released.\n");
    
    return 0;
}