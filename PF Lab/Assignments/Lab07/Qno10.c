#include<stdio.h>

int main(){
    int x,y,t,i,j,n,k,marks;
    int total_marks=0;
    int class_total=0;
    int grand_total=0;
    float a;
    int is_fail;
    printf("Enter number of class in your school: ");
    scanf("%d",&x);

    for(i=0;i<x;i++){
        class_total=0;
        printf("Enter number of student in %d class: \n",i+1);
        scanf("%d",&y);
        for(j=0;j<y;j++){
            is_fail=0;
            total_marks=0;
            printf("Enter number of subjects for student %d: \n",j+1);
            scanf("%d",&n);
            for(k=0;k<n;k++){
                printf("Enter marks of subject %d: \n",k+1);
                scanf("%d",&marks);
                if(marks<40){
                    printf("You are Fail in %d subject\n",k+1);
                    is_fail=1;
                }
                
                total_marks=total_marks+marks;
            }
            a=(float)total_marks/n;
            printf("Average mark: %.2f\n",a);
            printf("Class : %d, Student : %d Total Marks: %d, Average : %.2f, Result :%s \n",i+1,j+1,total_marks,a,is_fail ? "Fail" : "Pass");
            class_total=class_total+total_marks;
        }
        printf("Total marks of Class %d: %d\n",i+1,class_total);
        grand_total=grand_total+class_total;
    }
    printf("Total marks across all class : %d\n",grand_total);
    
}