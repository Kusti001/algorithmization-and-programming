#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BTree {
    struct BTree *left;
    struct BTree *right;
    int val;
};

typedef struct BTree Btree;

Btree *first = 0;

void insert(int n) {
    Btree *new_node = (Btree *) malloc(sizeof(Btree));
    new_node->left = new_node->right = NULL;
    new_node->val = n;

    if (!first) {
        first = new_node;
        return;
    }

    Btree *t = first;
    while (1) {
        if (n < t->val) {
            if (t->left) {
                t = t->left;
            } else {
                t->left = new_node;
                return;
            }
        } else if (n > t->val) {
            if (t->right) {
                t = t->right;
            } else {
                t->right = new_node;
                return;
            }
        } else {
            printf("%d ЭЛЕМЕНТ УЖЕ СУЩЕСТВУЕТ\n", n);
            free(new_node);
            return;
        }
    }
}

// рекурсивная функция для подсчета листков
int count_nodes(Btree *t) {
    if (!t) return 0;
    return 1 + count_nodes(t->left) + count_nodes(t->right);
}

int is_balanced(Btree *t) {
    int right = count_nodes(t->right) ;
    int left = count_nodes(t->left) ;
    if (left == right || left == right + 1 || left == right - 1) {
        printf("tree is balanced\n");
        return 0;
    }
    if (left > right) {
        printf("left path is bigger\n");
        return -1;
    }
    printf("right path is bigger\n");
    return 1;
}

void free_tree(Btree *t) {
    if (!t) return;
    free_tree(t->left);
    free_tree(t->right);
    free(t);
}

void btree_to_array(Btree *node, int *arr, int *index) {
    // рекурсивно записываем в массив все значения листьев
    if (!node) return; // если пришли в нулевой указатель (вышли из дерева)
    //cначала идем максимально влево, потом вправо и тд
    btree_to_array(node->left, arr, index);
    arr[(*index)++] = node->val; //пришли максимально влево
    btree_to_array(node->right, arr, index); //идем в правые части и записываем их
    //идя таким образом мы расставим по возрастанию все значения и будет легче найти медиану
}

Btree* build_balanced(int *arr, int start, int end) {
    if (start > end) return 0;
    int mid = start + (end - start) / 2; //находим индекс медианы - будущей новой вершины дерева
    // создаем НОВУЮ ВЕРШИНУ
    Btree *node = (Btree*)malloc(sizeof(Btree));
    node->val = arr[mid];
    // рекурсивно выбираем СЛЕДУЮЩИЕ вершины, как в бинарном поиске, деля диапазон значений пополам и всегда выбирая медиану
    // это гарантирует нам равномерное распределение
    node->left = build_balanced(arr, start, mid - 1);
    node->right = build_balanced(arr, mid + 1, end);

    return node; // возвращаем новую вершину
}

void rebalance_tree() {
    int n = count_nodes(first);
    if (n == 0) return;
    // выделяем место в памяти для хранения ВСЕХ значений листьев
    int *arr = (int*)malloc(n * sizeof(int)); //указатель на этот массив
    int index = 0;
    btree_to_array(first, arr, &index);

    free_tree(first);  // Удаляем старое

    first = build_balanced(arr, 0, n - 1);  // Вершина нового сбалансированного дерева
    free(arr); // освобождаем из памяти массив со значениями вершин
}

//void balance(Btree *t) {
//    int balance = is_balanced(t);
//    if (balance == 0) {
//        printf("tree is balanced\n");
//    }
//    if (balance == -1) {
//        do {
//            Btree * tmp = first;
//            first = first->left;
//            tmp->right = first;
//
//
//
//            balance = is_balanced(t);
//        }while (balance != 0);
//    }
//}
//


// Вариант 2 - С стрелочками
void print_tree_with_arrows(Btree *node, int depth, int is_left) {
    if (!node) return;

    // Рекурсия для правого поддерева
    print_tree_with_arrows(node->right, depth + 1, 0);

    // Отступы и стрелка
    for (int i = 0; i < depth - 1; i++) {
        printf("   ");
    }
    if (depth > 0) {
        printf(is_left ? "" : "");
    }

    printf("%d\n", node->val);

    // Рекурсия для левого поддерева
    print_tree_with_arrows(node->left, depth + 1, 1);
}

// Вариант 3 - Самый читаемый (горизонтальный)
void print_tree_pretty(Btree *node, int level) {
    if (!node) return;

    // Увеличиваем отступ
    int indent = level * 4;

    // Сначала правое поддерево
    print_tree_pretty(node->right, level + 1);

    // Текущий узел с отступом
    for (int i = 0; i < indent; i++) {
        printf(" ");
    }
    printf("%d\n", node->val);

    // Затем левое поддерево
    print_tree_pretty(node->left, level + 1);
}

int main() {
    insert(50);
    insert(30);
    insert(70);
    insert(1000);
    insert(200);
    insert(130);

    insert(100);
    insert(40);
    insert(60);
    insert(80);
    insert(111);

    printf("=== ДО БАЛАНСИРОВКИ ===\n");
    print_tree_pretty(first, 0);
    is_balanced(first);

    rebalance_tree();

    printf("\n=== ПОСЛЕ БАЛАНСИРОВКИ ===\n");
    print_tree_pretty(first, 0);
    is_balanced(first);

    free_tree(first);
    return 0;
}


/*НА ПЯТЕРКУ
 *генерируем двоичное дерево
 *struct BTree{
 *struct Btree * left;
 *struct Btree * right;
 *int val;
 *}.
 *
 *1.Вставка в нужном месте по 1 элементу (проверить, если ли элемент)
 *2.Баланс дерева (слева и справа количество элементов равно или отличается на 1) прогуглить балансировку (не по уровням!!!)
 * ПОВОРОТ ДЕРЕВА без рекурсии!!!
 */
