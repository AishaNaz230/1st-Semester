#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
    char password[5][10];
    int score;
    int i;
    int j;
    int strongest=0;
    int index=0;
    int below10=0;


    for(i=0;i<5;i++){
        printf("Enter passwords: %d \n",i+1);
        scanf("%9s",&password[i]);
        score=0;
        for(j=0;password[i][j]!='\0';j++){
            if(islower(password[i][j])){
                score=score+1;
            }
            else if(isupper(password[i][j])){
                score=score+2;
            }
            else if(isdigit(password[i][j])){
                score=score+3;
            }

        }
        if(strlen(password[i])>=8){
            score=score+5;
        }
    
        if(strstr(password[i],"123")!=NULL){
             score=score-3;
        }
        printf("%s=%d\n",password[i],score);
        
        if(score>strongest){
            strongest=score;
            index=i;
        }
        if(score<10){
            below10++;
        }
     }
     printf("Strongest password: %s\n",password[index]);
     printf("Strongest score: %d\n",strongest);
     printf("Password below 10: %d\n",below10);
    
}