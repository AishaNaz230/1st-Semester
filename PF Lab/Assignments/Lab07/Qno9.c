#include<stdio.h>

int main(){
    int x,i,j,y;
    int d,s;
    int dailywage=500;
    int dep_total=0;
    int grand_total=0;
    printf("Enter number of departments in your company: ");
    scanf("%d",&x);
    for(i=0;i<3;i++){
        dep_total=0;
        printf("Enter number of employee in you department: ");
        scanf("%d",&y);
        for(j=0;j<y;j++){
            printf("Enter number of days you work: ");
            scanf("%d",&d);
            
            if(d>25){
                s=(dailywage*d)+2000;
            }
            else{
                s=dailywage*d;
            }
             printf("Department %d, Employee %d: Days Worked = %d, Salary = Rs. %d\n", i+1, j+1, d, s);
             dep_total=dep_total+s;
        }
        printf("Total Salary paid to Department %d: Rs. %d\n", i+1, dep_total);
        grand_total=grand_total+dep_total;
    }
    printf("Total salary slip : %d",grand_total);   
}