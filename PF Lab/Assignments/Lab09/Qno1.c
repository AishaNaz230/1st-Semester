#include<stdio.h>
#include<string.h>
int main(){
    char feedback[200];
    char update[300];
    printf("Enter costumer feedback\n");
    fgets(feedback,sizeof(feedback)stdin);
    feedback[strcspn(feedback,"\n")]='\0';
    int len=strlen(feedback);
    printf("Total characters:%d\n",len);
    if(strstr(feedback,"bad"!=NULL)){
        printf("Found:\"bad\"\n");
    }
     if(strstr(feedback,"good"!=NULL)){
        printf("Found:\"good\"\n");
    }
    char*pos=strstr(feedback,"bad");
    if(pos!=NULL){
        int index=pos-feedback;
        strncpy(update,feedback,index);
        update[index]='\0';
        strcat(update,"not good");
        strcat(update,feedback+index+3);
        printf("Updated review: %s\n",updated);
    }
    else{
        printf("\nNo \"bad\" found. Review: %s\n", feedback);
    }
}