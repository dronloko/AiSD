// Copyright 2013 <DronLoko>

#include <cstdio>
#include <algorithm>

using std::max;

// Узел бинарного дерева поиска
struct Node {
    int Key;
    Node *Left;
    Node *Right;

    // Конструктор по умолчанию для бинарного дерева поиска
    Node(int key, Node *left, Node *right):Key(key), Left(left), Right(right) {}
};

// Узел декартова дерева
struct CTreapNode {
    int Key;
    int Priority;
    CTreapNode* Left;
    CTreapNode* Right;
    
    // Конструктор по умолчанию для декартова дерева
    CTreapNode(int key, int priority) : Key(key), Priority(priority),
        Left(NULL), Right(NULL) {}
};

// Добавление узла c ключом key в бинарное дерево поиска
// При вызове указывается ссылка на корень дерева поиска
void Insert_search(Node *&node, int key) {
    if ( node == NULL ) {  // Дерево пустое?
        node = new Node(key, NULL, NULL);
    } else {
        if ( node->Key <= key ) {  // Добавить в правое поддерево?
            Insert_search(node->Right, key);
        } else {
            Insert_search(node->Left, key);  // Добавить в левое поддерево
        }
    }
}

// Слияние 2 разрезанных декартовых деревьев в одно декартово дерево
CTreapNode* Merge(CTreapNode *left, CTreapNode *right) {
    if ( left == 0 )
        return right;
    if ( right == 0 )
        return left;

    if ( left->Priority > right->Priority ) {
        left->Right = Merge(left->Right, right);
        return left;
    } else {
        right->Left = Merge(left, right->Left);
        return right;
    }
}

// Разрезание декартова дерева на 2 дерева по ключу
// В левом поддереве все ключи не больше key, а в правом - все больше key
void Split(CTreapNode *node, int key, CTreapNode *&left, CTreapNode *&right) {
    if ( node == NULL ) {
        left = right = NULL;
    } else {
        if ( node->Key <= key ) {
            Split(node->Right, key, node->Right, right);
            left = node;
        } else {
            Split(node->Left, key, left, node->Left);
            right = node;
        }
    }
}

// Добавление узла c ключом key и приоритетом priority в декартово дерево
// При вызове указывается ссылка на корень декартова дерева
CTreapNode* Insert_decart(CTreapNode *&root, int key, int priority) {
    if ( root == NULL ) {
        root = new CTreapNode(key, priority);
        return root;
    } else {
        CTreapNode *node = new CTreapNode(key, priority);
        CTreapNode *splitLeft = NULL;
        CTreapNode *splitRight = NULL;
        Split(root, key, splitLeft, splitRight);

        return Merge(Merge(splitLeft, node), splitRight);
    }
}

// Удаление узла декартова дерева c ключом key
CTreapNode* Delete_decart( CTreapNode* root, int key ) {
        CTreapNode* splitLeft = NULL;
        CTreapNode* splitRight = NULL;
        Split(root, key - 1, splitLeft, splitRight);
        CTreapNode* splitRightLeft = NULL;
        CTreapNode* splitRightRight = NULL;
        
        Split(splitRight, key, splitRightLeft, splitRightRight);
        delete splitRightLeft;
        
        return Merge(splitLeft, splitRightRight);
}


// Получение максимальной глубины дерева поиска
// При вызове указывается ссылка на корень дерева поиска
int get_Depth_search(Node *&node, int depth) {
    if ( node == NULL )  // На этом месте есть узел?
        return depth;
    // Берём максимальное из глубин левого и правого поддеревьев
    return max(get_Depth_search(node->Left, depth + 1),
               get_Depth_search(node->Right, depth + 1));
}

// Получение максимальной глубины декартова дерева
// При вызове указывается ссылка на корень декартова дерева
int get_Depth_decart(CTreapNode *&node, int depth) {
    if ( node == NULL )  // На этом месте есть узел?
        return depth;
    // Берём максимальное из глубин левого и правого поддеревьев
    return max(get_Depth_decart(node->Left, depth + 1),
               get_Depth_decart(node->Right, depth + 1));
}

int main() {
    int n = 0;  // Количество будущих узлов в деревьях
    scanf("%d", &n);

    Node *root_search = NULL;  // Корень дерева поиска
    CTreapNode *root_decart = NULL;  // Корень декартового дерева

    int key = 0;  // Ключ вводимого узла
    int priority = 0; // Приоритет вводимого узла

    for ( int i = 0; i < n; ++i ) {
        scanf("%d %d", &key, &priority);
        Insert_search(root_search, key);  // Вставляем в дерево поиска
        // Вставляем в декартово дерево
        root_decart = Insert_decart(root_decart, key, priority);
    }

    int depth_search = 0;  // Максимальная глубина дерева поиска
    int depth_decart = 0;  // Максимальная глубина декартова дерева

    // Находим максимальные глубины деревьев
    depth_search = get_Depth_search(root_search, depth_search);
    depth_decart = get_Depth_decart(root_decart, depth_decart);

    // Выводим на экран модуль их разности
    printf("%d\n", std::abs(depth_search - depth_decart));
    
    // Удаляем декартово дерево
    while ( root_decart != NULL )
    root_decart = Delete_decart( root_decart, root_decart->Key );

    return 0;  // Успех!
}

