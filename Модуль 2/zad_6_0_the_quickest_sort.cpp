#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cstdio>

// Сортировка вставками для маленьких массивов
void insertion_sort(int *a, int low, int high) {
    for ( int i = low + 1; i <= high ; i++ ) {  // Выбираем элемент из неупорядоченной правой части
        int j = i;
        for ( ; j > low && a[j] < a[j - 1]; j-- ) {  // Вставляем этот элемент на своё место в левую часть
        	int tmp = a[j];
        	a[j] = a[j - 1];
        	a[j - 1] = tmp;
        }
    }
}

// Быстрая сортировка массива data
void qSort(int *data, int low, int high) {
    // Оптимизация концевой рекурсии - массив из менее 10 элементов проще отсортировать вставками
    if ( high - low < 9 ) {
        insertion_sort(data, low, high);
    } else {
        int i = low; 
        int j = high;
        // Взять средний элемент быстрее, чем считать медиану - оптимизация выбора опорного элемента
        int opora = data[(low + high)/2];
        int temp = 0;
        do {
            while ( data[i] < opora ) ++i;
            while ( data[j] > opora ) --j;
            if (i <= j) {
                // Менять 2 переменные через третью быстрее, чем использовать std::swap - оптимизация обмена переменных
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
                ++i;
                --j;
            }
        } while ( i <= j );
        if ( low < j )
            qSort( data, low, j );
        if ( i < high )
            qSort( data, i, high );
    }
}

int main() {
    std::vector<int> data;
    int number = 0;
    // scanf работает быстрее, чем cin - оптимизация ввода
    while ( scanf("%d", &number) == 1 )
        data.push_back( number );
    int n = data.size();
    qSort( &data[0], 0, n - 1 );
    // printf работает быстрее, чем cout - оптимизация вывода
    for ( int i = 9; i < n; i += 10 ) printf("%d\n", data[i]);
    return 0;  // Успех!
}

