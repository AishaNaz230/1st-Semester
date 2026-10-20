#include <stdio.h>

int main() {
    int i, j, k, n = 5;

    for (i = 1; i <= n; i++) {

        for (k = 1; k <= n - i; k++) printf("  ");
        for (j = 1; j <= i; j++)     printf("* ");

        printf(" | ");

        for (k = 1; k <= n - i; k++) printf("  ");
        for (j = 1; j <= i; j++)     printf("%d ", j);

        printf(" | ");

        for (k = 1; k <= n - i; k++) printf("  ");
        for (j = 1; j <= i; j++)     printf("%c ", 'A' + j - 1);

        printf("\n");
    }

    printf("\n\n");

    for (i = 1; i <= n; i++) {

        for (k = 1; k <= n - i; k++)       printf("  ");
        for (j = 1; j <= 2 * i - 1; j++)   printf("* ");
        for (k = 1; k <= n - i; k++)       printf("  ");

        printf(" | ");

        for (k = 1; k <= n - i; k++)       printf("  ");
        for (j = 1; j <= 2 * i - 1; j++)   printf("%d ", j);
        for (k = 1; k <= n - i; k++)       printf("  ");

        printf(" | ");

        for (k = 1; k <= n - i; k++)       printf("  ");
        for (j = 1; j <= 2 * i - 1; j++)   printf("%c ", 'A' + j - 1);
        for (k = 1; k <= n - i; k++)       printf("  ");

        printf("\n");
    }

    return 0;
}