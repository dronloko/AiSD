/*
============================================================================
 Name        : Common elements.c
 Author      : Andrey Polyansky
 Version     : 1.0
 Copyright   : All rights reserved
 Description : Quest 3
 ============================================================================
*/
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
int Count(int na, int *a, int nb, int *b) {
    int i = 0;
    int j = 0;
    int count = 0;
    while (i < na && j < nb) {
        if (a[i] < b[j]) i++;
        else if (b[j] < a[i]) j++;
        else if (a[i] == b[j]) {
            i++;
            j++;
            count++;
        }
    }
    return count;
}
int main() {
    int NA = 0;
    int count = 0;
    cin >> NA;
    int* a = new int[NA];
    for (int i = 0; i < NA; i++) {
        cin >> a[i];
    }
    int NB = 0;
    cin >> NB;
    int* b = new int[NB];
    for (int i = 0; i < NB; i++) {
        cin >> b[i];
    }
    count = Count(NA, a, NB, b);
    cout << count << endl;
    delete[] a;
    delete[] b;
    return 0;
}
