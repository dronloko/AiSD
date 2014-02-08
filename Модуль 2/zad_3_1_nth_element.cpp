#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cstdio>

// Нахождение "медианы трёх" массива а. Функция возвращает индекс соответствующего элемента
inline int mediana3 (int *a, int r) {
    if(a[0] >= a[r/2]) {
        if(a[0] >= a[r]) {
            if(a[r/2] >= a[r])
                return r/2;
            else
                return r;
        } else
           return 0;
    } else {
        if(a[0] >= a[r])
            return 0;
        else {
            if(a[r/2] >= a[r])
                return r;
            else
                return r/2;
        }
    }
}

int partition(int *a, int r, int k) {
    int temp = a[k];
    a[k] = a[r];
    a[r] = temp;

    int i = 0;
    int j = 0;

    while (j < r) {
        if (a[j] == a[r]) {
            if (j % 2 == 0) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                ++i;
                ++j;
            } else {
             ++j;
            }
        } else {
            if (a[j] <= a[r]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                ++i;
                ++j;
            } else {
                ++j;
            }
        }
    }

    temp = a[i];
    a[i] = a[r];
    a[r] = temp;

    return i;
}

// Нерекурсивное нахождение k-ой порядковой статистики массива а
// Проход по массиву осуществляется от начала к концу, а опорный элемент - "медиана трёх".
int kStat(int *a, int n, int k) {
    int down_pos = -1, up_pos = n, pos = 0;
    srand(5);
    while (true) {
        pos = down_pos + 1 + partition(a + down_pos + 1, up_pos - down_pos - 1, mediana3(a + down_pos + 1, up_pos - down_pos - 1));
        // (rand()%(up_pos - down_pos - 1)));
        if (pos > k) up_pos = pos;
        else if (pos < k) down_pos = pos;
             else break;
    }
    return a[pos];
}

int main() {

    int n = 0;
    scanf("%d", &n);
    int k = 0;
    scanf("%d", &k);
    
    int *a = new int[n];
    int number = 0;
    
    // srand(time(NULL))    ;
    
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    
    int pos =  kStat(a, n - 1, k);  // k-ая порядковая статистика массива а

    printf("%d\n", pos);
    
    delete[] a;
    
    return 0;
}

