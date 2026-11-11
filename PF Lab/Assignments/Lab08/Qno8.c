#include <stdio.h>
#include <stdlib.h>

void displayStock(int *arr, int n);
int* updateStock(int *arr, int n);
int* insertItem(int *arr, int *n);
int* deleteItem(int *arr, int *n);
void sortStock(int *arr, int n);
void printTotalAndLowest(int *arr, int n);
void showMenu();

int main() {
    int n;
    int choice;
    
    while(1) {
        printf("Enter starting size (3 to 8): ");
        scanf("%d", &n);
        if(n >= 3 && n <= 8) {
            break;
        }
        printf("Invalid! Size must be between 3 and 8.\n");
    }
    
    int *stock = (int *)malloc(n * sizeof(int));
    if(stock == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("\nEnter stock values for %d items:\n", n);
    for(int i = 0; i < n; i++) {
        printf("Item %d stock: ", i + 1);
        scanf("%d", &stock[i]);
    }
    
    printTotalAndLowest(stock, n);
    
    do {
        showMenu();
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                displayStock(stock, n);
                break;
                
            case 2:
                stock = updateStock(stock, n);
                printTotalAndLowest(stock, n);
                break;
                
            case 3:
                stock = insertItem(stock, &n);
                printTotalAndLowest(stock, n);
                break;
                
            case 4:
                stock = deleteItem(stock, &n);
                if(stock != NULL) {
                    printTotalAndLowest(stock, n);
                }
                break;
                
            case 5:
                sortStock(stock, n);
                printf("\nStock sorted in ascending order.\n");
                displayStock(stock, n);
                printTotalAndLowest(stock, n);
                break;
                
            case 6:
                printf("\nExiting program...\n");
                break;
                
            default:
                printf("Invalid choice! Please enter 1-6.\n");
        }
        
    } while(choice != 6);
    
    free(stock);
    stock = NULL;
    printf("Memory has been successfully released.\n");
    
    return 0;
}

void showMenu() {
    printf("\n========== GROCERY SHOP MENU ==========\n");
    printf("1. Display stock\n");
    printf("2. Update stock of one item\n");
    printf("3. Insert a new item\n");
    printf("4. Delete an item\n");
    printf("5. Sort stock\n");
    printf("6. Exit\n");
    printf("========================================\n");
}

void displayStock(int *arr, int n) {
    printf("\n------ CURRENT STOCK ------\n");
    if(n == 0) {
        printf("No items in stock.\n");
        return;
    }
    for(int i = 0; i < n; i++) {
        printf("Item %d: %d\n", i + 1, *(arr + i));
    }
    printf("---------------------------\n");
}

int* updateStock(int *arr, int n) {
    int pos, newValue;
    
    while(1) {
        printf("Enter position to update (1 to %d): ", n);
        scanf("%d", &pos);
        if(pos >= 1 && pos <= n) {
            break;
        }
        printf("Invalid position! Please enter between 1 and %d.\n", n);
    }
    
    printf("Enter new stock value: ");
    scanf("%d", &newValue);
    
    *(arr + pos - 1) = newValue;
    printf("Item %d updated to %d.\n", pos, newValue);
    
    return arr;
}

int* insertItem(int *arr, int *n) {
    int pos, newValue;
    int oldN = *n;
    
    while(1) {
        printf("Enter position to insert (1 to %d): ", oldN + 1);
        scanf("%d", &pos);
        if(pos >= 1 && pos <= oldN + 1) {
            break;
        }
        printf("Invalid position! Please enter between 1 and %d.\n", oldN + 1);
    }
    
    printf("Enter new stock value: ");
    scanf("%d", &newValue);
    
    int *newArr = (int *)malloc((oldN + 1) * sizeof(int));
    if(newArr == NULL) {
        printf("Memory allocation failed!\n");
        return arr;
    }
    
    for(int i = 0; i < pos - 1; i++) {
        *(newArr + i) = *(arr + i);
    }
    
    *(newArr + pos - 1) = newValue;
    
    for(int i = pos; i < oldN; i++) {
        *(newArr + i) = *(arr + i - 1);
    }
    
    free(arr);
    
    *n = oldN + 1;
    
    printf("New item inserted at position %d.\n", pos);
    displayStock(newArr, *n);
    
    return newArr;
}

int* deleteItem(int *arr, int *n) {
    int pos;
    int oldN = *n;
    
    if(oldN == 0) {
        printf("No items to delete!\n");
        return arr;
    }
    
    while(1) {
        printf("Enter position to delete (1 to %d): ", oldN);
        scanf("%d", &pos);
        if(pos >= 1 && pos <= oldN) {
            break;
        }
        printf("Invalid position! Please enter between 1 and %d.\n", oldN);
    }
    
    int *newArr = (int *)malloc((oldN - 1) * sizeof(int));
    if(newArr == NULL) {
        printf("Memory allocation failed!\n");
        return arr;
    }
    
    int j = 0;
    for(int i = 0; i < oldN; i++) {
        if(i != pos - 1) {
            *(newArr + j) = *(arr + i);
            j++;
        }
    }
    
    free(arr);
    
    *n = oldN - 1;
    
    printf("Item at position %d deleted.\n", pos);
    displayStock(newArr, *n);
    
    return newArr;
}

void sortStock(int *arr, int n) {
    int temp;
    
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(*(arr + j) > *(arr + j + 1)) {
                temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

void printTotalAndLowest(int *arr, int n) {
    if(n == 0) {
        printf("\nNo items in stock.\n");
        return;
    }
    
    int total = 0;
    int lowest = *(arr + 0);
    int lowestPos = 1;
    
    for(int i = 0; i < n; i++) {
        total += *(arr + i);
        
        if(*(arr + i) < lowest) {
            lowest = *(arr + i);
            lowestPos = i + 1;
        }
    }
    
    printf("\n------ STOCK SUMMARY ------\n");
    printf("Total stock: %d\n", total);
    printf("Lowest stock: %d (Item %d)\n", lowest, lowestPos);
    printf("---------------------------\n");
}