/*
============================================================================
 Name        : edinica.c
 Author      : Andrey Polyansky
 Version     : 1.0
 Copyright   : All rights reserved
 Description : Quest 1
 ============================================================================
 */
#include<stdio.h>
int number_ones(int n) {
    int k = 0;
    if (n == 0) return 0;
    while (n != 0) {
        if (n%2 == 1)
        k++;
        n/ = 2;
    }
  return k;
}
int main() {
    int n = 0;
    scanf("%d", &n);
    int k = number_ones(n);
    printf("%d\n", k);
  return 0;
}

