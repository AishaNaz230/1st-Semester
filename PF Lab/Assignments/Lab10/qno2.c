#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *fp;
    int rollNum,leaveLec,lec,r;
    char name[50];
    float percentage;
    
    fp = fopen("attendance.txt","wb");
    if(fp==NULL){
        return 1;
    }
    fprintf(fp, "%-3d %-15s %3d\n", 1, "Ayesha", 18);
    fprintf(fp, "%-3d %-15s %3d\n", 2, "Bilal", 14);
    fprintf(fp, "%-3d %-15s %3d\n", 3, "Hamza", 20);
    fprintf(fp, "%-3d %-15s %3d\n", 4, "Sana", 12);
    fprintf(fp, "%-3d %-15s %3d\n", 5, "Zainab", 16);
    
    fclose(fp);
    fp = fopen("attendance.txt","rb+");
    if(fp==NULL){
        return 1;
    }
    printf("Roll no:");
    scanf("%d",&rollNum);
    fseek(fp,(rollNum-1)*24,SEEK_SET);
    fscanf(fp,"%d %s %d",&r,name,&lec);
    percentage=(lec/20.0)*100.0;
    printf("%s: %d / 20 (%.1f%%)", name, lec, percentage);
    if (percentage < 75.0) {
        printf(" Short attendance");
    }
    printf("\n");
    printf("Roll number for leave: ");
    scanf("%d", &rollNum);
    printf("Lectures: ");
    scanf("%d", &leaveLec);
    fseek(fp, (rollNum - 1) * 24, SEEK_SET);
    fscanf(fp, "%d %s %d", &r, name, &lec);
    lec=lec+leaveLec;
    fseek(fp,(rollNum-1)*24,SEEK_SET);
    fprintf(fp, "%-3d %-15s %3d\n", r, name, lec);
    percentage=(lec/20.0)*100.0;
    printf("%s:now %d / 20 (%.1f%%)\n", name, lec, percentage); 
    fseek(fp,-24,SEEK_END);
    fscanf(fp,"%d %s %d\n",&r,name,&lec);
    printf("Last record: %d %s %d\n", r, name, lec);
    fclose(fp);
}
