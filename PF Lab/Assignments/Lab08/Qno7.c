#include <stdio.h>

int findMax(int *p, int n);
int findMin(int *p, int n);
double findAverage(int *p, int n);
int countAbove(int *p, int n, double avg);
void reverseArray(int *p, int n);
int searchMark(int *p, int n, int key);
void printArray(int *p, int n, char *message);
int countPass(int *p, int n);

int main() {
    int marks[10];
    
    for(int i = 0; i < 10; i++) {
        while(1) {
            printf("Enter marks for student %d (0-100): ", i + 1);
            scanf("%d", &marks[i]);
            if(marks[i] >= 0 && marks[i] <= 100) {
                break;
            }
            printf("Invalid! Marks must be between 0 and 100.\n");
        }
    }
    
    printArray(marks, 10, "Array before reversing");
    
    int highest = findMax(marks, 10);
    int lowest = findMin(marks, 10);
    double avg = findAverage(marks, 10);
    int aboveAvg = countAbove(marks, 10, avg);
    
    printf("\n------ CLASS REPORT ------\n");
    printf("Highest marks: %d\n", highest);
    printf("Lowest marks: %d\n", lowest);
    printf("Average marks: %.2f\n", avg);
    printf("Students above average: %d\n", aboveAvg);
    
    int key;
    printf("\nEnter a mark to search: ");
    scanf("%d", &key);
    int position = searchMark(marks, 10, key);
    
    if(position != -1) {
        printf("Mark %d found at position %d\n", key, position + 1);
    } else {
        printf("Mark %d not found in the class\n", key);
    }
    
    reverseArray(marks, 10);
    
    printArray(marks, 10, "Array after reversing");
    
    int passCount = countPass(marks, 10);
    printf("\n------ PASS COUNT ------\n");
    printf("Students who passed (40 or more): %d\n", passCount);
    
    return 0;
}

int findMax(int *p, int n) {
    int max = *p;
    for(int i = 1; i < n; i++) {
        if(*(p + i) > max) {
            max = *(p + i);
        }
    }
    return max;
}

int findMin(int *p, int n) {
    int min = *p;
    for(int i = 1; i < n; i++) {
        if(*(p + i) < min) {
            min = *(p + i);
        }
    }
    return min;
}

double findAverage(int *p, int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += *(p + i);
    }
    return (double)sum / n;
}

int countAbove(int *p, int n, double avg) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        if(*(p + i) > avg) {
            count++;
        }
    }
    return count;
}

void reverseArray(int *p, int n) {
    int *start = p;
    int *end = p + n - 1;
    int temp;
    
    while(start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}

int searchMark(int *p, int n, int key) {
    for(int i = 0; i < n; i++) {
        if(*(p + i) == key) {
            return i;
        }
    }
    return -1;
}

void printArray(int *p, int n, char *message) {
    printf("\n------ %s ------\n", message);
    for(int i = 0; i < n; i++) {
        printf("Student %d: %d\n", i + 1, *(p + i));
    }
}

int countPass(int *p, int n) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        if(*(p + i) >= 40) {
            count++;
        }
    }
    return count;
}