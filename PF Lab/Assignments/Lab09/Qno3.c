#include <stdio.h>
#include <string.h>
int main() {
    char email[100];
    char domain[100];
    char *atPos;

    printf("Enter email address: ");
    scanf("%s",email);
    atPos=strchr(email, '@');
    if (atPos!=NULL) {
        strcpy(domain,atPos + 1); 
        printf("\nEmail:  %s\n",email);
        printf("Domain: %s\n",domain);
    } else {
        printf("Invalid email! No '@' found.\n");
    }
}