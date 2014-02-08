/*
============================================================================
 Name        : Sistema schislenia.c
 Author      : Andrey Polyansky
 Version     : 1.0
 Copyright   : All rights reserved
 Description : Quest 2
 ============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
void change_system(int number, int base) {
    int i = 0, symbols = 0, num = number;
    char *result;
    int tmp = 0;
    if (base != 1)
        for (symbols = 0; num != 0; symbols++) {
            num = num/base;
        } else {
            symbols = number;
          }
    result = (char*)malloc(symbols*sizeof(char));
    if (base == 1) {
        for (int j = 0; j < symbols; j++) {
            printf("1");
        }
        printf("\n");
        free(result);
        return;
    } else {
        for (i = 0; i < symbols; i++) {
            tmp = number % base;
            if (tmp <= 9) result[i] = tmp + 48;
            else
                result[i] = tmp + 55;
            number = number/base;
        }
        for (i = symbols-1; i >= 0; i--) {
            printf("%c", result[i]);
        }
        printf("\n");
        free(result);
    }
}
int main(void) {
    int base = 0, number = 0;
    scanf("%d %d", &number, &base);
    if (base > 0 && base <= 36 && number >= 1)
        change_system(number, base);
    else
        return -1;
return 0;
}

