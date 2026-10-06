#include<stdio.h>

int main(){
    int car[12]={10,20,15,30,25,12,28,22,8,16,28,14};
    float avg;
    int sum=0;
    int overloaded=0;
    int highest;
    int lowest;
    int difference;
    int i;

    for(i=0;i<12;i++){
        sum=sum+car[i];
    }
    avg=(float)sum/12.0;
    printf("The average is %.2f\n",avg);

    for(i=0;i<12;i++){
        if(car[i]>avg){
            overloaded++;
        }
    }
    
    highest=car[0];
    lowest=car[0];

    for(i=0;i<12;i++){
    if(car[i]>highest){
        highest=car[i];
    }
    else if(car[i]<lowest){
        lowest=car[i];
    }
    }
    difference=highest-lowest;

    printf("The difference is %d\n",difference);
    printf("The highest car is %d\n",highest);
    printf("The lowest car is %d\n",lowest);
    printf("The overloaded signal is %d\n",overloaded);

}