/*
============================================================================
 Name        : Queque through stack (Очередь через стек)
 Author      : Andrey Polyansky
 Version     : 1.0
 Copyright   : All rights reserved
 Description : Quest 5
============================================================================
*/

#include <cstdio>
#include <cstdlib>

// Затолкнуть элемент elem в левый стек
void pushLeft(int *&Left_Stack, int *Left_Top, int *&Right_Stack, int elem, int *Buffer) {
    if ( (*(Left_Top) + 1) == *Buffer ) { // Если надо, выделить дополнительную память для обоих стеков
        (*Buffer) *= 2;
        Left_Stack = reinterpret_cast<int*>(realloc(Left_Stack, (*Buffer) * sizeof(int)));
        Right_Stack = reinterpret_cast<int*>(realloc(Right_Stack, (*Buffer) * sizeof(int)));
    }
    Left_Stack[++(*Left_Top)] = elem;
}

// Затолкнуть элемент elem в правый стек
void pushRight(int* Right_Stack, int *Right_Top, int elem) {
    Right_Stack[++(*Right_Top)] = elem;
}

// Достать элемент из левого стека
int popLeft(int* Left_Stack, int *Left_Top) {
    int tmp = Left_Stack[(*Left_Top)--];
    return tmp;
}

// Достать элемент из правого стека, работающего как очередь
int popRight(int* Left_Stack, int *Left_Top, int* Right_Stack, int *Right_Top) {
    if ( *Left_Top == -1 ) {  // Попытка достать элемент из пустого стека? Ошибка!
        free(Left_Stack);  // Очищаем память
        free(Right_Stack);
        exit(-1);
    }
    // Если в левом стеке есть элементы, производим перенос всех элементов в правый стек - получается очередь
    // После изъятия элемента из правого стека переносим обратно все элементы в левый стек, чтобы не нарушить последовательность
    else {
        if ( *Left_Top > -1 ) {
            while ( *Left_Top > -1 ) {
                pushRight(Right_Stack, Right_Top, popLeft(Left_Stack, Left_Top));
            }
            int tmp = Right_Stack[*Right_Top];
            for ( ; --(*Right_Top) > -1; ) {
                Left_Stack[++(*Left_Top)] = Right_Stack[*Right_Top];
            }
            return tmp;
        }
    }
}

int main(void) {

    int Buffer = 5;  // Первоначальный размер буфера каждого из стеков
    
    // Выделяем память в обоих стеках размером c первоначальный буфер
    int* Left_Stack  = reinterpret_cast<int*>(malloc(Buffer * sizeof(int)));
    int* Right_Stack = reinterpret_cast<int*>(malloc(Buffer * sizeof(int)));
    
    int Left_Top = -1;  // Количество элементов в левом стеке
    int Right_Top = -1;  // Количество элементов в правом стеке

    int n = 0; // Количество команд, которое будет введено в программе
    
    if ( scanf("%d", &n) != 1 ) {  // Неправильно введено количество команд - ошибка!
        free(Left_Stack);  // Очищаем память
        free(Right_Stack);
        return -1;
    }
    // Для каждой комманды считываем тип комманды и ожидаемое значение
    for ( size_t i = 0; i < n; ++i ) {
    
        int command = 0;  // Код команды
        int element = 0;  // Введённый c клавиатуры элемент для добавления (удаления)
        
        if ( scanf("%d %d", &command, &element) != 2 ) {  // Неправильно введена команда - ошибка!
            free(Left_Stack);  // Очищаем память
            free(Right_Stack);
            return -1;
        }
        
        switch ( command ) {  // Какая из комманд была введена?
            case 2: {  // Достать элемент из очереди (правого стека)
                int popped = popRight(Left_Stack, &Left_Top, Right_Stack, &Right_Top);  // Ожидаемое значение
                if ( popped != element ) {  // Введённое и ожидаемое значение совпали?
                    printf("NO\n");
                    free(Left_Stack);  // Очищаем память
                    free(Right_Stack);
                    exit(0);
                }
                break;
            }
            case 3: {  // Затолкнуть элемент в левый стек
                pushLeft(Left_Stack, &Left_Top, Right_Stack, element, &Buffer);
                break;
            }
        }
    }
    printf("YES\n");  // Все ожидаемые значения совпали
    
    free(Left_Stack); // Очищаем память
    free(Right_Stack);
    
    return 0;  // Успех!
}

