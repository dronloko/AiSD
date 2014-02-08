// Copyright 2013 <DronLoko>

#include <iostream>
#include <cstdio>

struct pair_t { // Структура, хранящая информацию о коодинатах точек
    int a;  // Координата х
    int b;  // Координата y
};

bool pairless(const pair_t &left, const pair_t &right) {        // Координата возрастает?
    if (left.a < right.a) return true;  // X1 < X2 => истина
    if ((left.a == right.a) && (left.b < right.b)) return true; // (X1 = Х2 && Y1 < Y2) => истина
    return false;   // иначе => ложь
}

//Сортировка вставками для пар точек на плоскости по возрастанию координаты
void insertion_sort(pair_t *a, int n, bool (*less)(const pair_t &, const pair_t &)) {
    for (int i = 1; i < n; ++i) {  // Выбираем элемент из неупорядоченной правой части
        pair_t tmp = a[i];  // запоминаем значение i элемента
        int j = i;  // заводим счётчик j внутреннего цикла
// ставим каждый i элемент на своё место:
// Пока элемент a[i] меньше каждого текущего значения элемента a[j-1], a[j] = a[j-1]
        for ( ;j > 0 && less(tmp, a[j-1]); --j ) {  
                a[j] = a[j-1];
        }
        a[j] = tmp; // Возвращаем a[j] верное значение - tmp
    }
}

int main() {
    int n = 0;  // Инициализация переменной под размер массива точек
    std::cin >> n;  // Ввод размера массива точек
    if (n < 1) return -1;  // Если размер введён неверно, выходим из программы
    pair_t *pairs = new pair_t[n];  // Заводим массив точек размера n
    for (int i = 0; i < n; i++) {  // Цикл для заполнения значений координат точек
        if (scanf("%d %d", &pairs[i].a, &pairs[i].b) != 2) return -1;
    }
    insertion_sort(pairs, n, pairless);  // Сортировка массива точек по возрастанию координаты
    for (int i = 0; i < n; ++i) {  // Вывод отсортированного массива на экран
        std::cout << pairs[i].a << " " << pairs[i].b << std::endl;
    }
    delete[] pairs;  // Освобождение памяти под массив точек
    return 0;  // Закончили успешно!
};
