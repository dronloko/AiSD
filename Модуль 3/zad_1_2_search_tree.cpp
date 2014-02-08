// Copyright 2013 <DronLoko>

#include <iostream>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::stack;

// Узел бинарного дерева поиска
struct Node {
    int Key;
    Node *Left;
    Node *Right;

    // Инициализация полей структуры по умолчанию
    Node(int key, Node *left, Node *right) : Key(key), Left(left), Right(right) {}
};

// Добавление узла c ключом key в дерево поиска
// При вызове указывается ссылка на корень дерева поиска
void insert_Node(Node *&node, int key) {
    if ( node == NULL ) {  // На этом месте есть узел?
        node = new Node(key, NULL, NULL);
    } else {
        if ( node->Key <= key ) {  // Добавить в правое поддерево?
            insert_Node(node->Right, key);
        } else {
            insert_Node(node->Left, key);  // Добавить в левое поддерево
        }
    }
}

// Выводит ключи всех узлов бинарного дерева поиска в порядке pre-order (сверху вниз)
void PreOrder(Node *root) {
    stack <Node*> st;               // Стек для запоминания вершин
    st.push(root);                  // Кладём в стек корень дерева
    while ( !st.empty() ) {         // Пока в стеке есть узлы
        Node* node = st.top();      // Берём верхний узел
        cout << node->Key << " ";   // Печатаем его ключ
        st.pop();                   // Достаём из стека верхний элемент, чтобы не 
        if ( node->Right != NULL )  // Если есть правый ребёнок - помещаем его в стек
            st.push(node->Right);
        if ( node->Left != NULL ) { // Если есть левый ребёнок - помещаем его в стек
            st.push(node->Left);
        }
    }
}

int main() {
    int n;  // Количество будущих узлов в дереве
    cin >> n;

    Node *root = NULL;  // Бинарное дерево поиска для обработки

    for ( int i = 0; i < n; ++i ) {
        int key;  // Ключ вводимого узла
        cin >> key;        insert_Node(root, key);  // Добавление узла в дерево
    

    PreOrder(root);  // Вывод всех вершин в порядке pre-order
    cout << endl;  // Переход на новую строку в конце программы для удобства

    return 0; // Успех!
}

