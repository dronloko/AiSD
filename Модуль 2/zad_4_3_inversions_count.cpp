// Copyright 2013 <DronLoko>

#include <vector>
#include <cstdio>
#include <stdint.h>

// Выполнить слияние массива a, содержащего a_len элементов,
// и массива b, содержащего b_len элементов. Результат записать в массив c.
// Вернуть количество инверсий.
int64_t merge(int *a, int a_len, int *b, int b_len, int *c, int64_t& counter) {
    int i = 0;
    int j = 0;
    while (i < a_len && j < b_len) {
        if (a[i] <= b[j]) {
            c[i + j] = a[i];
            ++i;
        } else {
            counter += a_len - i;
            c[i + j] = b[j];
            ++j;
        }
    }
    for ( j ; j < b_len; ++j )
        c[i + j] = b[j];
    for ( i ; i < a_len; ++i )
        c[i + j] = a[i];
    return counter;
}

// Отсортировать массив A, содержащий n элементов и вернуть количество инверсий в нём
int64_t MergeSort(int *data, int n, int64_t& counter) {
    if ( n < 2 ) return counter;  // Сортировка не нужна
    // Сортируем левую половину и считаем количество инверсий в ней
    counter = MergeSort(data, n/2, counter);
    // Сортируем правую половину и считаем количество инверсий в ней
    counter = MergeSort(data + n/2, n - n/2, counter);
    int *buffer = new int[n];  //Сюда запишем результат слияния
    counter = merge(data, n/2, data + n/2, n - n/2, buffer, counter);  // Слияние половин
    // Копирование результата слияния в исходный массив:
    for ( int i = 0; i < n; ++i )
        data[i] = buffer[i];
    delete[] buffer;  // Удаляем временный буфер
    return counter;
}

int main() {
    std::vector<int> data;
    int number = 0;
    // Организуем ввод массива
    while ( scanf("%d", &number) == 1 )
        data.push_back(number);
    int n = data.size();  // Размер массива data
    int64_t counter = 0;  // Счётчик для количества инверсий
    counter = MergeSort(&data[0], n, counter);  // Количество инверсий в массиве data
    printf("%ld\n", counter);
    return 0;  // Успех!
}

