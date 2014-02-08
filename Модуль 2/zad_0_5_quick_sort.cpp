// Copyright 2013 <DronLoko>

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

// Вывод массива на экран
void print_data(const std::vector<int> &data) {
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i] << std::endl;
    }
}

// Быстрая сортировка массива data
// low - индекс первого элемента массива
// high - индекс последнего элемента массива
void qSort(int *data, int low, int high) {
    int i = low; // 
    int j = high;
    int x = data[(low+high)/2]; // Индекс опорного элемента - середина массива data
// Слева от опорного элемента все элементы меньше его, а справа - больше
    do {
        while (data[i] < x) ++i;  // Двигаемся вправо, пока a[i] < значения опорного элемента
        while (data[j] > x) --j;  // Двигаемся влево, пока a[j] > значения опорного элемента
        if (i <= j) {  // Если индекс i <= j - меняем значения соотв. элементов и идём дальше по массиву
            std::swap(data[i], data[j]);
            i++;
            j--;
        }
    } while (i <= j);  // Прогоняем цикл для всех элементов, у которых i <= j 
    if (low < j) qSort(data, low, j);  // Применяем рекурсивно быструю сортировку для левой части массива
    if (i < high) qSort(data, i, high);  // Применяем рекурсивно быструю сортировку для правой части массива
}

int main() {
    std::vector<int> data;  // Задаём вектор чисел типа integer
    int number = 0;  // Задаём и инициализируем переменную для ввода элемента массива
    while (true) {
// Если введено число, вставляем его в конец вектора, иначе - заканчиваем ввод
        if (scanf("%d", &number) == 1)  data.push_back(number);
            else
                break;
    };
    int n = data.size();  // Переменная для размера вектора
    qSort(&data[0], 0, n - 1);  // Сортируем вектор методом быстрой сортировки
    print_data(data);  // Выводим массив на экран
    return 0;  // Закончили успешно!
}

