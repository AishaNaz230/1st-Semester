#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    int room, nights, r, n, i;
    char status, name[21], searchName[21];
    char guests[10][21]; 
    int rooms[10];       
    float rate=8000.00, bill;

    fp=fopen("hotel.txt", "wb");
    if (fp==NULL) {
        return 1;
    }
    for(i=101;i<=110;i++){
        fprintf(fp,"%3d %c %-20s %2d %8.2f\n", i,'F',"-",0,rate);
    }
    fclose(fp);
    fp=fopen("hotel.txt","rb+");
    if(fp==NULL){
        return 1;
    }
    for(int check=0;check<2;check++){
    printf("Check-in room: ");
    scanf("%d",&room);
    printf("Name: ");
    scanf("%s",name);
    printf("Nights: ");
    scanf("%d",&nights);

    fseek(fp,(room - 101) * 39,SEEK_SET);
    fscanf(fp,"%d %c %s %d %f",&r,&status,name,&n,&rate);

    if(status=='F') {
        fseek(fp,(room - 101) * 39, SEEK_SET); 
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'B', name, nights, rate);
        printf("Room %d booked\n", room);
    } else{
        printf("Room already booked\n");
    }
}
    rewind(fp); 
    for(i= 0;i<10;i++) {
        fscanf(fp,"%d %c %s %d %f",&rooms[i],&status,guests[i],&n,&rate);
    }

    printf("Search name: ");
    scanf("%s",searchName);
    
    int found = 0;
    for(i=0;i<10;i++){
        if(strcmp(guests[i],searchName)==0) {
            printf("%s is in room %d\n", searchName,rooms[i]);
            found=1;
            break;
        }
    }
    if(!found){
        printf("Guest not found.\n");
    }
    printf("Check-out room: ");
    scanf("%d",&room);
    fseek(fp,(room - 101) * 39, SEEK_SET);
    fscanf(fp,"%d %c %s %d %f",&r, &status, name, &nights, &rate);
    bill=nights * rate;
    printf("Bill:%d x %.2f = %.2f\n", nights, rate, bill);
    fseek(fp, (room - 101) * 39, SEEK_SET);
    fprintf(fp,"%3d %c %-20s %2d %8.2f\n", room, 'F', "-", 0, rate);
    fclose(fp);
}