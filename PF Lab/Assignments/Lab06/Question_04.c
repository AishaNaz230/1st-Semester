#include<stdio.h>

int main(){
    int marks[15];
    int i;
    int total=0;
    int count=0;
    int highest;
    int lowest;
    int range;

    printf("Enter marks of students \n");

    for(i=0;i<15;i++){
        printf("student %d: \n",i+1);
        scanf("%d",&marks[i]);
    }

    for(i=0;i<15;i++){
        if(marks[i]+5>100){
            marks[i]=100;
        }
        else{
            marks[i]=marks[i]+5;
        }
        total=total+marks[i];

        if(marks[i]==100){
            count++;
        }
    }
    highest=marks[0];
    lowest=marks[0];
    for(i=0;i<15;i++){
    if(marks[i]>highest){
        highest=marks[i];
    }
    else if(marks[i]<lowest){
        lowest=marks[i];
    }
    }
    range=highest-lowest;

    for(i=0;i<15;i++){
        printf("student %d: %d\n",i+1,marks[i]);
    }
    printf("average=%.2f\n",(float)total/15);
    printf("student with exactly 100 marks = %d\n",count);
    printf("range=%d\n",range);
    
}