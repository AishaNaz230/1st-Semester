#include<stdio.h>
#define SIZE 3
int main(){
    int grid[SIZE][SIZE];
    int valid=1;
    int i,j,x,y;

    printf("Enter 3*3 sudoku grid: \n");
    printf("(use 0 for empty cells and (1-9) for filled cells)\n");

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("Enter cell[%d][%d]:",i+1,j+1);
            scanf("%d",&grid[i][j]);
        }
    }
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("%d  ",grid[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(grid[i][j]<0||grid[i][j]>9){
                valid=0;
                printf("Error:cell[%d][%d] contains %d outside valid range(0-9)\n",i+1,j+1,grid[i][j]);
            }
        }
    }
    for(i=0;i<SIZE&&valid;i++){
        for(j=0;j<SIZE&& valid;j++){ 
            if(grid[i][j]==0){
                continue;
            }  
            for(x=0;x<SIZE;x++){
                for(y=0;y<SIZE;y++){
                    if(i==x&&j==y){
                        continue;
                    }
                    if(grid[x][y]==0){
                        continue;
                    }
                    if(grid[i][j]==grid[x][y]){
                        valid=0;
                        printf("Error: number %d appered more than once\n",grid[i][j]);
                    }
                }
            } 
        }
    }
    if(valid){
        printf("Result: valid grid\n");
    }  
    else{
        printf("Result: invalid grid\n");
    }  
}