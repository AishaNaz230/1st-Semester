#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char cat[20],tempCat[20];
    float amt, newAmt,total=0.0;
    int entryNum,i;

    fp=fopen("expenses.txt", "wb");
    if(fp==NULL){
        printf("File open nahi ho saki!\n");
        return 1;
    }
    fprintf(fp, "%-12s %9.2f\n", "Food", 1200.00);
    fprintf(fp, "%-12s %9.2f\n", "Transport", 500.00);
    fprintf(fp, "%-12s %9.2f\n", "Books", 850.00);
    fprintf(fp, "%-12s %9.2f\n", "Mobile", 300.00);
    fclose(fp);
    printf("Category: ");
    scanf("%s",cat);
    printf("Amount: ");
    scanf("%f",&amt);
    fp=fopen("expenses.txt", "ab"); 
    fprintf(fp, "%-12s %9.2f\n", cat, amt);
    fclose(fp);  
    fp=fopen("expenses.txt", "rb+"); 
    if(fp==NULL){
        printf("File open nahi ho saki!\n");
        return 1;
    }
    fseek(fp, -2 * 23, SEEK_END); 
    char cat1[20],cat2[20];
    float amt1,amt2;
    fscanf(fp, "%s %f", cat1, &amt1); 
    fscanf(fp, "%s %f", cat2, &amt2); 
    printf("Latest two: %s %.2f, %s %.2f\n", cat1, amt1, cat2, amt2);
    printf("Entry to fix: ");
    scanf("%d",&entryNum);
    printf("Correct amount: ");
    scanf("%f",&newAmt);
    fseek(fp, (entryNum - 1) * 23, SEEK_SET);
    fscanf(fp, "%s %f", tempCat, &amt); 
    fseek(fp, (entryNum - 1) * 23, SEEK_SET);
    fprintf(fp, "%-12s %9.2f\n", tempCat, newAmt);
    rewind(fp); 
    for(i=0;i<5;i++){ 
        fscanf(fp, "%s %f", tempCat, &amt);
        printf("%s %.2f\n", tempCat, amt);
        total+=amt;
    }
    printf("Total: %.2f\n", total);
    fclose(fp);
}