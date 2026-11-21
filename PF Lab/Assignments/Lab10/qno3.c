#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char name[20], hottestName[20];
    float temp, newTemp, hottestTemp = -100.0;
    int cityNo, i;

    fp = fopen("temperature.txt", "wb");
    if (fp == NULL) {
        return 1;
    }
    fprintf(fp, "%-10s %5.1f\n", "Karachi", 32.5);
    fprintf(fp, "%-10s %5.1f\n", "Lahore", 30.1);
    fprintf(fp, "%-10s %5.1f\n", "Islamabad", 24.3);
    fprintf(fp, "%-10s %5.1f\n", "Quetta", 18.7);
    fprintf(fp, "%-10s %5.1f\n", "Peshawar", 28.9);
    fclose(fp);

    fp = fopen("temperature.txt", "rb+");
    if (fp == NULL) {
        return 1;
    }
    printf("City number: ");
    scanf("%d", &cityNo);
    fseek(fp, (cityNo - 1) * 17, SEEK_SET);
    fscanf(fp, "%s %f", name, &temp);
    printf("%s %.2f\n", name, temp);
    printf("City number to correct: ");
    scanf("%d", &cityNo);
    printf("New temperature: ");
    scanf("%f", &newTemp);
    fseek(fp, (cityNo - 1) * 17, SEEK_SET);
    fscanf(fp, "%s %f", name, &temp); 
    fseek(fp, (cityNo - 1) * 17, SEEK_SET);
    fprintf(fp, "%-10s %5.1f\n", name, newTemp);
    printf("%s updated to %.2f\n", name, newTemp);
    rewind(fp); 
    for (i = 0; i < 5; i++) {
        fscanf(fp, "%s %f", name, &temp);
        if (temp > hottestTemp) {
            hottestTemp = temp;
            strcpy(hottestName, name);
        }
    }
    printf("Hottest city: %s (%.1f)\n", hottestName, hottestTemp);
    fclose(fp);
}