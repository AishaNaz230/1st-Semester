#include <stdio.h>
#include <string.h>

void readMarks(int *m1, int *m2, int *m3) {
    printf("Enter marks for subject 1 (0-100): ");
    while(1) {
        scanf("%d", m1);
        if(*m1 >= 0 && *m1 <= 100) break;
        printf("Invalid! Enter between 0-100: ");
    }
    
    printf("Enter marks for subject 2 (0-100): ");
    while(1) {
        scanf("%d", m2);
        if(*m2 >= 0 && *m2 <= 100) break;
        printf("Invalid! Enter between 0-100: ");
    }
    
    printf("Enter marks for subject 3 (0-100): ");
    while(1) {
        scanf("%d", m3);
        if(*m3 >= 0 && *m3 <= 100) break;
        printf("Invalid! Enter between 0-100: ");
    }
}
void calculateStats(int m1, int m2, int m3, int *total, double *average, int *highest, int *lowest) {
    *total = m1 + m2 + m3;
    *average = *total / 3.0;
    *highest = m1;
    if(m2 > *highest) *highest = m2;
    if(m3 > *highest) *highest = m3; 
    *lowest = m1;
    if(m2 < *lowest) *lowest = m2;
    if(m3 < *lowest) *lowest = m3;
}

void swapMarks(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void addGraceMarks(int *mark, int grace) {
    if(*mark >= 35 && *mark < 40) {
        int needed = 40 - *mark;
        if(needed <= grace) {
            *mark = 40;  
        }
    }
}

void findGrade(double avg, char *grade, char remarks[]) {
    if(avg >= 80) {
        *grade = 'A';
        strcpy(remarks, "Excellent");
    }
    else if(avg >= 60) {
        *grade = 'B';
        strcpy(remarks, "Good");
    }
    else if(avg >= 40) {
        *grade = 'C';
        strcpy(remarks, "Satisfactory");
    }
    else {
        *grade = 'F';
        strcpy(remarks, "Needs Improvement");
    }
}

void incrementByValue(int x) {
    x = x + 1;  }

void incrementByReference(int *x) {
    *x = *x + 1;
}
int main() {
    printf("===== STUDENT RESULT SYSTEM =====\n");
    printf("%-10s %-8s %-8s %-8s %-8s %-10s %-8s %s\n", 
           "Student", "M1", "M2", "M3", "Total", "Average", "Grade", "Remarks");
    printf("--------------------------------------------------------------\n");
    
    for(int i = 1; i <= 5; i++) {
        printf("\n--- Student %d ---\n", i);
        
        int m1, m2, m3;
        int total, highest, lowest;
        double average;
        char grade;
        char remarks[50];
        
        readMarks(&m1, &m2, &m3);
        calculateStats(m1, m2, m3, &total, &average, &highest, &lowest);
        
        printf("Before grace: M1=%d, M2=%d, M3=%d\n", m1, m2, m3);
        printf("Total: %d, Average: %.2f\n", total, average);
        printf("Highest: %d, Lowest: %d\n", highest, lowest);
        
        addGraceMarks(&m1, 5);
        addGraceMarks(&m2, 5);
        addGraceMarks(&m3, 5);
        printf("After grace: M1=%d, M2=%d, M3=%d\n", m1, m2, m3);
        
        calculateStats(m1, m2, m3, &total, &average, &highest, &lowest);
        
        if(m1 < m2) swapMarks(&m1, &m2);
        if(m1 < m3) swapMarks(&m1, &m3);
        if(m2 < m3) swapMarks(&m2, &m3);
        findGrade(average, &grade, remarks);
        printf("Student %-3d %-8d %-8d %-8d %-8d %-10.2f %-8c %s\n", 
               i, m1, m2, m3, total, average, grade, remarks);
    }
    
    printf("\n\n===== PASS BY VALUE vs PASS BY REFERENCE =====\n");
    int num = 10;
    printf("Original num = %d\n", num);
    incrementByValue(num);
    printf("After incrementByValue(num): num = %d\n", num);
    incrementByReference(&num);
    printf("After incrementByReference(&num): num = %d\n", num);
    
    return 0;
}

