#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct BTree {
    struct BTree *left;
    struct BTree *right;
    int val;
};

typedef struct BTree Btree;

Btree *first = 0;

// Считает количество узлов в поддереве
int count_nodes(Btree *t) {
    if (!t) return 0;
    return 1 + count_nodes(t->left) + count_nodes(t->right);
}

// Проверяет баланс относительно вершины
int check_balance(Btree *t) {
    if (!t) return 0;
    int left_count = count_nodes(t->left);
    int right_count = count_nodes(t->right);
    return left_count - right_count; // положительное = левая больше, отрицательное = правая больше
}

// Операция 1: Смещение центра вправо
// Текущий корень становится левым ребенком своего правого ребенка
Btree *shift_right(Btree *t) {
    if (!t || !t->right) return t;

    Btree *new_root = t->right;
    t->right = new_root->left;
    new_root->left = t;

    if (first == t) {
        first = new_root;
    }

    return new_root;
}

// Операция 1: Смещение центра влево
// Текущий корень становится правым ребенком своего левого ребенка
Btree *shift_left(Btree *t) {
    if (!t || !t->left) return t;

    Btree *new_root = t->left;
    t->left = new_root->right;
    new_root->right = t;

    if (first == t) {
        first = new_root;
    }

    return new_root;
}

// Операция 2: Распрямление правого клина
// Когда есть узел с меньшим значением слева от большего на правой ветке
Btree *straighten_right_cline(Btree *t) {
    if (!t || !t->right || !t->right->left) return t;

    // Сохраняем указатели
    Btree *A = t;
    Btree *B = t->right;
    Btree *C = t->right->left;

    // Перестраиваем связи
    A->right = C;
    B->left = C->right;
    C->right = B;

    return t;
}

// Операция 2: Распрямление левого клина
// Когда есть узел с большим значением справа от меньшего на левой ветке
Btree *straighten_left_cline(Btree *t) {
    if (!t || !t->left || !t->left->right) return t;

    // Сохраняем указатели
    Btree *A = t;
    Btree *B = t->left;
    Btree *C = t->left->right;

    // Перестраиваем связи
    A->left = C;
    B->right = C->left;
    C->left = B;

    return t;
}

Btree * find_parent(int n) {
    Btree *t = first;

    // Вставка в клин
    while (t) {
        if (n < t->val) {
            t = t->left;
        } else if (n > t->val) {
            t = t->right;
        } else {
            return t;
        }
    }
}
// Вставляет элемент в клин (все элементы меньше корня идут влево, больше - вправо)
Btree *insert(int n) {
    Btree *new_node = (Btree *)malloc(sizeof(Btree));
    new_node->left = new_node->right = NULL;
    new_node->val = n;

    Btree *t = first;
    Btree *parent = NULL;
    if (!t){return new_node;}
    // Вставка в клин
    while (t) {
        parent = t;
        if (n < t->val) {
            t = t->left;
        } else if (n > t->val) {
            t = t->right;
        } else {
            printf("%d Already exist\n", n);
            free(new_node);
            return first;
        }
    }

    if (n < parent->val) {
        parent->left = new_node;
        if (first ->val > parent->val) {
            find_parent(parent->val) -> right = new_node;
            parent->left = NULL;
            new_node->right = parent;
        }
    } else {
        parent->right = new_node;
        if (first ->val < parent->val) {
            find_parent(parent->val) -> left = new_node;
            parent->right = NULL;
            new_node->left = parent;
        }
    }
    return first;
}





// Функция для вычисления высоты дерева
int treeHeight(Btree *t) {
    if (!t) return 0;
    int leftHeight = treeHeight(t->left);
    int rightHeight = treeHeight(t->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
// Функция для заполнения массива значениями дерева
void fillTreeArray(Btree *t, char **arr, int row, int col, int height) {
    if (!t) return;

    // Вычисляем смещение для следующего уровня
    int offset = 1;
    for (int i = 0; i < height - 2; i++) {
        offset *= 2;
    }

    // Записываем значение узла
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", t->val);
    int len = 0;
    while (buffer[len] != '\0') len++;

    // Размещаем значение по центру
    int start = col - len/2;
    for (int i = 0; i < len; i++) {
        arr[row][start + i] = buffer[i];
    }

    // Рекурсивно заполняем левое и правое поддеревья
    if (t->left || t->right) {
        if (t->left) {
            arr[row + 1][col - offset/2] = '/';
            fillTreeArray(t->left, arr, row + 2, col - offset, height - 1);
        }
        if (t->right) {
            arr[row + 1][col + offset/2] = '\\';
            fillTreeArray(t->right, arr, row + 2, col + offset, height - 1);
        }
    }
}
// Альтернативный более простой, но понятный вывод
void PrintTreeSimple(Btree *t) {
    if (!t) {
        printf("NULL");
        return;
    }

    printf("%d", t->val);

    if (t->left || t->right) {
        printf(" (");
        if (t->left) {
            PrintTreeSimple(t->left);
        } else {
            printf("NULL");
        }
        printf(", ");
        if (t->right) {
            PrintTreeSimple(t->right);
        } else {
            printf("NULL");
        }
        printf(")");
    }
}
// Основная функция вывода дерева
void PrintTree(Btree *t) {
    if (!t) {
        printf("Дерево пустое\n");
        return;
    }

    int height = treeHeight(t);
    if (height > 8) {
        printf("Дерево слишком большое для графического вывода (высота = %d)\n", height);
        printf("Вывод в виде списка: ");
        PrintTreeSimple(t);
        printf("\n");
        return;
    }

    // Вычисляем ширину массива (примерно 4^height)
    int width = 1;
    for (int i = 0; i < height; i++) {
        width *= 2;
    }
    width *= 4;

    // Создаем массив для вывода
    char **arr = (char **)malloc((2 * height - 1) * sizeof(char *));
    for (int i = 0; i < 2 * height - 1; i++) {
        arr[i] = (char *)malloc(width * sizeof(char));
        for (int j = 0; j < width; j++) {
            arr[i][j] = ' ';
        }
        arr[i][width - 1] = '\0';
    }

    // Заполняем массив значениями дерева
    fillTreeArray(t, arr, 0, width / 2, height);

    // Выводим результат
    printf("\n");
    for (int i = 0; i < 2 * height - 1; i++) {
        // Находим последний не пробельный символ
        int last = width - 2;
        while (last >= 0 && arr[i][last] == ' ') {
            last--;
        }

        // Выводим строку до последнего не пробельного символа
        for (int j = 0; j <= last && j < width - 1; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");

        // Освобождаем память
        free(arr[i]);
    }
    free(arr);
    printf("\n");
}


int main() {
    int Ar[10] = {};
    int n = sizeof(Ar) / sizeof(Ar[0]);

    time_t curtime;
    time(&curtime);
    srand((unsigned int) curtime);

    for (int i = 0; i < n; i++) {
        Ar[i] = rand() % 100;
        printf("%d ",Ar[i]);
    }
    printf("\n");




    for (int i = 0; i < n; i++)
         first = insert(Ar[i]);

    printf("\nFinal Tree:\n");
    PrintTree(first);

    return 0;
}