#include<stdio.h>

#define CLASS 2
#define STUDENT 3
#define SUBJECT 3

int main(){
    int marks[CLASS][STUDENT][SUBJECT];
    int student_total[CLASS][STUDENT];
    int class_topper[CLASS];
    int class_topper_marks[CLASS];
    int overall_topperClass = 0, overall_topperStudent = 0, overall_topperMarks = 0;
    int c, s, sub;

    for(c=0;c<CLASS;c++){
        printf("--Class %d---\n",c+1);
        for(s=0;s<STUDENT;s++){
            printf("---Student %d---\n",s+1);
            for(sub=0;sub<SUBJECT;sub++){
                printf("---Subject %d marks---\n",sub+1);
                scanf("%d",&marks[c][s][sub]);
            }
        }
    }
    printf("===Total marks per student===");
    for(c=0;c<CLASS;c++){
        printf("--Class %d---\n",c+1);
        for(s=0;s<STUDENT;s++){
            student_total[c][s]=0;
            for(sub=0;sub<SUBJECT;sub++){
                student_total[c][s]=student_total[c][s]+marks[c][s][sub];
            }
            printf("  Student %d: %d marks\n",s+1,student_total[c][s]);
        }    
    } 
    for(c=0;c<CLASS;c++){
        class_topper[c]=0;
        class_topper_marks[c]=student_total[c][0];
        for(s=1;s<STUDENT;s++){
            if(student_total[c][s]>class_topper_marks[c]){
                class_topper_marks[c]=student_total[c][s];
                class_topper[c]=s;
            }
        }
        printf("class %d topper: student %d with %d marks\n",c+1,class_topper[c]+1,class_topper_marks[c]);
    } 
    overall_topperClass=0;
    overall_topperMarks=class_topper_marks[0];
    overall_topperStudent=class_topper[0];

    for(c=1;c<CLASS;c++){
        if(class_topper_marks[c]>overall_topperMarks){
            overall_topperMarks=class_topper_marks[c];
            overall_topperClass=c;
            overall_topperStudent=class_topper[c];
        }
    }
    printf("===Final Result===\n");
    for(c=0;c<CLASS;c++){
        printf("Top performer of class %d: student %d with %d marks\n",c+1,class_topper[c]+1,class_topper_marks[c]);
    }
    printf("Qverall topper: student %d of class %d with %d marks\n",overall_topperStudent+1,overall_topperClass+1,overall_topperMarks);

}