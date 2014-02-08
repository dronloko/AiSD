#include <iostream>
#include <vector>
#include <stdint.h>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

// Вычисляет количество "красивых" номеров
void Count_happy_numbers ( int length, int64_t& counter ) {
    if ( length == 1 ) {  // Номер состоит из 1 цифры?
        counter = 8;
        return;
    }
    // Массив для количества счастливых номеров длины i, начинающихся на k цифру, k = 0..9
    int64_t* current = new int64_t[10];
    // Массив для количества счастливых номеров длины i - 1, начинающихся на k цифру, k = 0..9
    int64_t* prev = new int64_t[10];
    
    for(int i = 1; i < 8; ++i ) {  // Начальная инициализация массивов
        current[i] = 1;  // C 1 до 7 "красивый" номер начинаться может
        prev[i] = 1;
    }
    
    // C 0 и 8 "красивый" номер по условию начинаться не может
    current[0] = 0;
    prev[0] = 0;
    current[8] = 0;
    prev[8] = 0;
    
    // А c 9 также может :)
    current[9] = 1;
    prev[9] = 1;
    
    // Вычисляем количество "красивых" номеров длины i, начинающихся на цифру k,
    // где k - индекс массива current
    for( int i = 1; i < length; ++i ) {
        current[1] = prev[6] + prev[8];
        current[2] = prev[7] + prev[9];
        current[3] = prev[4] + prev[8];
        current[4] = prev[3] + prev[9] + prev[0];
        current[6] = prev[1] + prev[7] + prev[0];
        current[7] = prev[2] + prev[6];
        current[8] = prev[1] + prev[3];
        current[9] = prev[2] + prev[4];
        current[0] = prev[4] + prev[6];
        
        //  Копируем каждый раз счётчики из current в prev для пересчёта их при следующей итерации цикла
        for( int k = 0; k < 10; ++k ) {
            prev[k] = current[k];
        }
    }
    
    //  Считаем количество "красивых" номеров
    counter = current[0] + current[1] + current[2] + current[3] + current[4] + current[6] + current[7] + current[8] + current[9];
    
}

int main() {
           
    int length = 0;
    std::cin >> length;
    int64_t counter = 0;
    Count_happy_numbers(length, counter);  // Считаем количество "красивых" номеров
    std::cout << counter << std::endl;  // Выводим на экран
    
    return 0;  // Успех!
}
