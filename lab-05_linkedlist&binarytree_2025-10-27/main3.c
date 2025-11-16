#include <stdio.h>
#include <stdlib.h>

struct BTree {
    struct BTree *left;
    struct BTree *right;
    int val;
};

typedef struct BTree Btree;

Btree *first = 0;

//считает количество узлов ниже аргумента
int count_nodes(Btree *t) {
    if (!t) return 0; //если узла нет, возвращает ноль
    return 1 + count_nodes(t->left) + count_nodes(t->right); //если есть узел, возвращает 1(сам узел) + количество узлов слева и справа также рекурсивно
}

//балансировка узла по количеству узлов в левом и правом поддереве
Btree* rebalance_tree(Btree* t) {
    int left = count_nodes(t->left); //считает количество элементов в левом поддереве
    int right = count_nodes(t->right); //тоже самое для правого

    if (left > right + 1) { //если в левом первес
        /*
        1. новым корнем становится first -> left
        2. сохраняем правый узел first -> left
        3. изначальный корень становится справа
        4. к новому старому узлу добавляем сохранённый правый узел НО влево (тк изначально он был левее/меньше корня)

        память здесь освобождать не нужно, тк мы только указатели создаем(они сами очистятся*), а не узлы и память не выделяем динамически
        */
        Btree *new_root = t->left;
        Btree *orphan = new_root->right;

        new_root->right = t;
        t->left = orphan;
        t = new_root;
    }
    else if (right > left + 1) { //перевес в правом
        //обратно процессу для левого перевеса
        Btree *new_root = t->right;
        Btree *orphan = new_root->left;

        new_root->left = t;
        t->right = orphan;
        t = new_root;
    }
    //возвращаем НОВЫЙ корень дерева/поддерева
    return t;
}

//рекурсивная вставка с балансировкой
Btree* insert_rec(Btree* t, int n) {
    /*
    БАЗОВЫЙ СЛУЧАЙ: если мы дошли по указателям до нуля(в этом месте нет узла) или вставляем первый элемент, тогда(И ТОЛЬКО ЗДЕСЬ) создаем новый узел с нашим значением и возвращаем на него указатель

    1. спускаемся по дереву, пока не найдём 0 (или уже созданный элемент).
    2. после того как новый узел создан (наш базовый случай), рекурсия поднимается обратно по стеку вызовов.
    3. На каждом уровне проверяем баланс через rebalance_tree(t) и возвращаем корень поддерева после возможного вращения(это нужно для баланса ПОДДЕРЕВЬЕВ, не только относительно корня).
     */
    if (!t) {
        Btree *new_node = malloc(sizeof(Btree));
        new_node->val = n;
        new_node->left = new_node->right = 0;
        return new_node;
    }

    if (n < t->val)
        t->left = insert_rec(t->left, n);
    else if (n > t->val)
        t->right = insert_rec(t->right, n);
    else {
        printf("%d ELEMENT ALREADY EXISTS\n", n);
        return t; // чтобы выходить из рекурсии и ничего не изменить
    }

    return rebalance_tree(t);
}

//обертка для вставки(тк вставка возвращает в рекурсии корень поддерева, последнее, что она вернёт - ГЛАВНЫЙ корень, уже после балансировки)
void insert(int n) {
    first = insert_rec(first, n);
}

//самое простое, что смог найти в интеренете
// Вывод дерева уровневым обходом
void PrintTree(Btree *root, int depth) {
    if (root == NULL)
        return;

    // Сначала печатаем правое поддерево
    PrintTree(root->right, depth + 1);

    // Печатаем отступы
    for (int i = 0; i < depth; i++)
        printf("      ");

    // Печатаем значение
    printf("%d\n", root->val);

    // Печатаем левое поддерево
    PrintTree(root->left, depth + 1);
}

int main() {
    int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = sizeof(values)/sizeof(values[0]);

    for (int i = 0; i < n; i++)
        insert(values[i]);

    printf("Final Tree:\n");
    PrintTree(first,0);

    return 0;
}
