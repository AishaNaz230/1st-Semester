#include<stdio.h>
#define SIZE 3

int main(){
    int data[SIZE][SIZE];
    int key[SIZE][SIZE];
    int i,j;
    int encrypted[SIZE][SIZE];
    int max,max_row,max_col;

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("data[%d][%d] ",i+1,j+1);
            scanf("%d",&data[i][j]);
        }
        printf("\n");
    }
     for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("%d ",data[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("key[%d][%d] ",i+1,j+1);
            scanf("%d",&key[i][j]);
        }
        printf("\n");
    }
     for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("%d ",key[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            encrypted[i][j] = (data[i][j]* key[i][j]) +(i + j);
        }
        printf("\n");
    }
     for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("%d ",encrypted[i][j]);
        }
        printf("\n");
    }
     max=encrypted[0][0];
     max_row=0;
     max_col=0;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(encrypted[i][j]>max){
                max=encrypted[i][j];
                max_row=i;
                max_col=j;
            }
        }
    }
    printf("Max encrypted=%d, Max row= %d, max column= %d",max,max_row+1,max_col+1);
}