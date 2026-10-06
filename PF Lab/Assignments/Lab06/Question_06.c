#include<stdio.h>

int main(){
    int gen[10];
    int i;

    gen[0]=1;
    gen[1]=1;

    for(i=2;i<10;i++){
        gen[i]=gen[i-1]+gen[i-2];
    }
    for(i=0;i<10;i++){
        printf("Generation %d:%d\n",i+1,gen[i]);
    }

}