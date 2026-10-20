#include<stdio.h>

#define SIZE 3

int main(){
    float temp[SIZE][SIZE][SIZE];
    float layer_avg[SIZE] = {0};
    float sum;
    int i, j, k;
    int hot_layer = 0;
    float max_avg;
    float max_temp;
    int max_X = 0, max_Y = 0, max_Z = 0;

    printf("coordinates range: x(1-3), y(1-3), z(1-3)\n");
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            for(k=0;k<SIZE;k++){
                printf("Temp at point [%d][%d][%d] (x,y,z)",i+1,j+1,k+1);
                scanf("%f",&temp[i][j][k]);
            }
        }
    }
    for(k=0;k<SIZE;k++){
        printf("layer %d(z=%d)\n",k+1,k+1);
        printf("      y=1  y=2  y=3\n");
        for(i=0;i<SIZE;i++){
            printf("   x=%d",i+1);
           for(j=0;j<SIZE;j++){
               printf("%5.1f",temp[i][j][k]);
            }
           printf("\n");
        }
    }
    for(k=0;k<SIZE;k++){
        sum=0;
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                sum=sum+temp[i][j][k];
            }
        }
        layer_avg[k]=sum/9.0;
        printf("Layer %d(z=%d): Avg=%.2f\n",k+1,k+1,layer_avg[k]);
    }
    hot_layer=0;
    max_avg=layer_avg[0];
    for(k=1;k<SIZE;k++){
        if(layer_avg[k]>max_avg){
            max_avg=layer_avg[k];
            hot_layer=k;
        }
    }
    printf("Layer %d with average temp of %.2f\n",hot_layer+1,max_avg);

    max_temp=temp[0][0][0];
    max_X=0;
    max_Y=0;
    max_Z=0;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            for(k=0;k<SIZE;k++){
                if(temp[i][j][k]>max_temp){
                    max_temp=temp[i][j][k];
                    max_X=i;
                    max_Y=j;
                    max_Z=k;
                }
            }
        } 
    }
    for(k=0;k<SIZE;k++){
        printf("Layer %d: %.2f \n",k+1,layer_avg[k]);
    } 
    printf("Layer %d:(average: %.2f) \n",hot_layer+1,max_avg);   
    
    printf("Temprature = %.2f\n",max_temp);
    printf("Location : x=%d, y=%d, z=%d\n",max_X+1,max_Y+1,max_Z+1);
}     
