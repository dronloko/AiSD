// Copyright 2013 <DronLoko>

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <algorithm>

// Узел АВЛ-дерева
struct CNode {
    int Key;
    int Height;
    CNode* Left;
    CNode* Right;

    CNode( int key ): Key( key ), Height( 1 ), Left( NULL ), Right( NULL ) {}
};

// Получение высоты узла node
int Height( CNode* node ) {
    return node ? node->Height : 0;
}

// Установка значения высоты в поле структуры для вершины node
void FixHeight( CNode* node ) {
    node->Height = std::max( Height( node->Left ), Height( node->Right ) ) + 1;
}

// Левый поворот
CNode* RotateLeft ( CNode* node ) {
    CNode* right = node->Right;
    node->Right = right->Left;
    right->Left = node;
    FixHeight( node );
    FixHeight( right );
    return right;
}

// Правый поворот
CNode* RotateRight( CNode* node ) {
    CNode* left = node->Left;
    node->Left = left->Right;
    left->Right = node;
    FixHeight( node );
    FixHeight( left );
    return left;
}

// Узнать баланс вершины
int GetBalance ( CNode* node ) {
    return Height(node->Right) - Height(node->Left);
}

// Восстановление баланса вершины node, если требуется
CNode* Balance ( CNode* node ) {
    FixHeight( node );
    int balance = GetBalance( node );
    if ( balance == -2 ) {
        if ( GetBalance( node->Left ) == 1 )
          node->Left = RotateLeft( node->Left );
      return RotateRight( node );
    }
    if ( balance == 2 ) {
        if ( GetBalance( node->Right ) == -1 )
            node->Right = RotateRight( node->Right );
        return RotateLeft( node );
    }
    return node;
}

// Вставка вершины c ключом key в АВЛ-дерево
CNode* Insert ( CNode* node, int key ) {
    if ( node == NULL ) {
        return new CNode( key );
    }
    if ( key < node->Key )
        node->Left = Insert( node->Left, key );
    else
        node->Right = Insert( node->Right, key );
    return Balance( node );
}

// Нахождение минимума в поддереве c корнем node
CNode* FindMin( CNode* node ) {
    if ( node->Left == NULL )
        return node;
    else
        return FindMin( node->Left);
}

// Удаление минимума в поддереве c корнем node
CNode* RemoveMin( CNode* node ) {
    if ( node->Left == NULL )
        return node->Right;
    node->Left = RemoveMin( node->Left );
    return Balance( node );
}

// Удаление узла c ключом key из АВЛ-дерева
CNode* Remove( CNode* node, int key ) {
    if ( node == NULL ) return NULL;
    if ( key < node->Key )
        node->Left = Remove( node->Left, key );
    else if ( key > node->Key ) {
            node->Right = Remove( node->Right, key );
         } else {
                CNode* left = node->Left;
                CNode* right = node->Right;
                delete node;
                if ( right == NULL )
                    return left;
                CNode* min = FindMin( right );
                min->Right = RemoveMin( right );
                min->Left = left;
                return Balance( min );
           }
    return Balance( node );
}

int main() {
    CNode *root = NULL;
    int command = 0;
    while( true ) {
        std::cin >> command;
        if ( std::cin.eof() ) {
            break;
        }
        if ( command >= 0 )
            root = Insert( root, command ); // Вставляем узел c ключом command
        else
            root = Remove( root, abs( command ) );  // Удаляем узел c ключом |command|
    }

    // Выводим высоту АВЛ-дерева c корнем root
    std::cout << Height( root ) << std::endl;

    return 0;  // Успех!
}

