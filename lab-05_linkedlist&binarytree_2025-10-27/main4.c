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

Btree FULL_REBALANCE(Btree * t) {

    if (!t) return 0; // если пришли в нулевой указатель (вышли из дерева)
    //cначала идем максимально влево, потом вправо и тд
    btree_to_array(node->left, arr, index);
    arr[(*index)++] = node->val; //пришли максимально влево
    btree_to_array(node->right, arr, index);




}
//рекурсивная вставка с балансировкой
Btree* insert_iter(Btree *root, int n) {
    Btree *parent = NULL;
    Btree *curr = root;

    // 1. Найти место для вставки
    while (curr != NULL) {
        parent = curr;
        if (n < curr->val)
            curr = curr->left;
        else if (n > curr->val)
            curr = curr->right;
        else {
            printf("%d ELEMENT ALREADY EXISTS\n", n);
            return root;
        }
    }

    // 2. Создать узел
    Btree *new_node = malloc(sizeof(Btree));
    new_node->val = n;
    new_node->left = new_node->right = NULL;

    // 3. Если дерево пустое
    if (parent == NULL)
        return new_node;

    // 4. Подвесить к родителю
    if (n < parent->val)
        parent->left = new_node;
    else
        parent->right = new_node;

    // 5. Однократная балансировка только РОДИТЕЛЯ
    return rebalance_tree(root);
}

//обертка для вставки(тк вставка возвращает в рекурсии корень поддерева, последнее, что она вернёт - ГЛАВНЫЙ корень, уже после балансировки)
void insert(int n) {
    first = insert_iter(first, n);
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
    //int values[] = {50, 30, 20, 35, 45};
    //int n = sizeof(values)/sizeof(values[0]);
//
    //for (int i = 0; i < n; i++)
    //    insert(values[i]);
//


    insert(50);
    insert(30);
    insert(70);
    insert(1000);
    insert(200);
    insert(130);

    printf("Final Tree:\n");
    PrintTree(first,0);

    return 0;
}
