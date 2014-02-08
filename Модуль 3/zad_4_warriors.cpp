// Copyright 2013 <DronLoko>

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

// Узел АВЛ-дерева
struct CNode {
    int Key;
    int Height;
    int Number;
    CNode* Left;
    CNode* Right;

    CNode( int key ): Key( key ), Height( 1 ), Number( 1 ), Left( NULL ), Right( NULL ) {}
};

// Получение высоты узла node
int Height( CNode* node ) {
    return node ? node->Height : 0;
}

// Получение значения Number
int GetNumber( CNode* node ) {
    return node ? node->Number : 0;
}

// Установка значения высоты в поле структуры для вершины node
void FixHeight( CNode* node ) {
    node->Height = std::max( Height( node->Left ), Height( node->Right ) ) + 1;
}

// Установка значения поля структуры Number для вершины node
void FixNumber( CNode* node ) {
    node->Number = GetNumber( node->Left ) + GetNumber( node->Right ) + 1;
}

// Левый поворот
CNode* RotateLeft ( CNode* node ) {
    CNode* right = node->Right;
    node->Right = right->Left;
    right->Left = node;
    FixHeight( node );
    FixHeight( right );
    FixNumber( node );
    FixNumber( right );
    return right;
}

// Правый поворот
CNode* RotateRight( CNode* node ) {
    CNode* left = node->Left;
    node->Left = left->Right;
    left->Right = node;
    FixHeight( node );
    FixHeight( left );
    FixNumber( node );
    FixNumber( left );
    return left;
}

// Узнать баланс вершины
int GetBalance ( CNode* node ) {
    return Height(node->Right) - Height(node->Left);
}

// Восстановление баланса вершины node, если требуется
CNode* Balance ( CNode* node ) {
    if ( node == NULL ) return NULL;
    FixHeight( node );
    FixNumber( node );
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
CNode* Insert ( CNode* node, int key, int& position ) {
    if ( node == NULL ) {
        return new CNode( key );
    }
    if ( key > node->Key ) {
        node->Right = Insert( node->Right, key, position );
    } else {
        if ( key < node->Key ) {
            position += GetNumber( node->Right ) + 1;
            node->Left = Insert( node->Left, key, position );
        }
      }
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
CNode* Remove( CNode* node, int pos ) {
    if ( node == NULL || pos > GetNumber( node ) ) return NULL;
    int current_pos = GetNumber( node->Right ) + 1;
    if ( pos == current_pos ) {
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
    if ( pos < current_pos )
        node->Right = Remove( node->Right, pos );
    else
        node->Left = Remove( node->Left, pos - current_pos );
    return Balance( node );
}

void printTree( CNode* node ) {
    if ( node == NULL )
        return;
    printTree( node->Left );
    std::cout << node->Key << std::endl;
    printTree( node->Right );
}

int main() {
    CNode *root = NULL;
    
    int n = 0;
    int type = 0;
    int rost = 0;

    cin >> n;
    for( int i = 0; i < n; ++i ) {
        cin >> type >> rost;
        switch ( type ) {
            case 1: {
                int position = 0;
                root = Insert( root, rost, position );
                cout << position << endl;
                break;
            }
            case 2: {
                root = Remove( root, rost + 1 );
                break;
            }
            case 3: {
                printTree(root);
                break;
            }
            default: break;
        }
    }
    cout << endl;
    
    return 0;  // Успех!
}

