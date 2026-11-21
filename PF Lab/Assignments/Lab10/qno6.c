#include <stdio.h>

void grow(int heights[],int n) {
    if(n==0){
     return;   
    }
    heights[n - 1]+=(int)(heights[n - 1] * 0.10);
    grow(heights,n - 1);
    printf("%d ",heights[n - 1]);
}

int tallest(int heights[],int n) {
    if (n==1){
       return 0;
    } 
    int pos=tallest(heights, n - 1);
    return(heights[n - 1] > heights[pos])?n-1 :pos;
}

int search(int heights[], int n, int target) {
    if (n==0){
        return -1;
        }
    if (heights[n - 1]==target) return n - 1;
    return search(heights,n-1,target);
}

int main() {
    int ids[6]={101, 102, 103, 104, 105, 106};
    int heights[6]={45, 120, 78, 200, 95, 150};
    int target,pos;

    printf("New heights: ");
    grow(heights,6);
    printf("\nTallest: tower %d (%d m)\n", ids[tallest(heights, 6)], heights[tallest(heights, 6)]);

    printf("Height to search: ");
    scanf("%d",&target);
    pos=search(heights,6,target);
    if(pos != -1){
        printf("Tower %d is %d m\n", ids[pos], heights[pos]);
    }
    else{
       printf("Not found.\n");
    } 
}