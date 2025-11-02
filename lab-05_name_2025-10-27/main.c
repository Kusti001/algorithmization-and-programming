#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define free(p) _free_dbg(p,_NORMAL_BLOCK)
#define malloc(p) _malloc_dbg(p,_NORMAL_BLOCK, __FILE__, __LINE__);
#define _CRTDBG_MAP_ALLOC

struct town {
    struct town *pNext;
    struct town *pPrev;
    char Name[]; //хитрость си, в с++ НЕЛЬЗЯ
}; //последнее поле может быть массивом с пустым размером

typedef struct town Town;
Town *pFirst = 0, *pLast = 0;

Town *Create(const char *name) {
    size_t len = strlen(name);
    Town *po = (Town *) malloc(sizeof(Town)+len+1);
    if (po == 0) return 0;
    strncpy_s(po->Name, len + 1, name, len + 1);
    return po;
}

void Destroy(Town *po) {
    if (po)
        free(po);
}

void AddToList(Town *po) {
    if (pLast) pLast->pNext = po;
    po->pPrev = pLast;
    pLast = po;
    po->pNext = 0;
    if (pFirst == 0) pFirst = po;
}

void DelFromList(Town *po) {
    //если это первый город, то меняем pFirst
    if (po == pFirst) {
        //существует ли следующий
        if (po->pNext) {
            pFirst = po->pNext;
        }
        //если нет, просто удаляем город
    }
    //если это последний город, то меняем pLast
    else if (po == pLast) {
        //существует ли предыдущий? (первый != последний)
        if (po->pPrev) {
            pLast = po->pPrev;
            pLast->pNext = 0;
        }
        //если нет, просто удаляем город
    }
    //если город ТОЧНО не первый и не последний, у него есть два соседа (ide подчеркивает желтеньким, но я в себе уверен)
    else {
        po->pPrev->pNext = po->pNext;
        po->pNext->pPrev = po->pPrev;
    }
}

Town *SearchForTown(const char *name) {
    Town *po = pFirst;
    while (po) {
        //if (po->Name == name) return po;  так мы сравниваем адреса указателей на строки(массивы символов) в памяти.

        /* strcmp
        Отрицательное значение (< 0), если первая строка лексически меньше второй.
        Ноль (0), если строки равны.
        Положительное значение (> 0), если первая строка лексически больше второй.
        */
        if (strcmp(po->Name, name) == 0) return po; //здесь же сравниваем лексически
        po = po->pNext;
    }

    return 0;
}

void PrintAllTowns(void) {
    printf("All Towns:\n");
    Town *po = pFirst;
    while (po) {
        if (po->pNext != 0) {
            printf("%s -> ", po->Name);
        } else {
            printf("%s\n", po->Name);
        }
        po = po->pNext;
    }
}

void SwapTowns(Town *po1, Town *po2) {

    if (po1==0 || po2==0 || po1->pNext != po2) return; // Защита

    // обновляем предыдущий
    if (po1->pPrev) { //если есть предыдуший
        po1->pPrev->pNext = po2;
    } else {
        pFirst = po2; // po2 становится первым
    }

    // обновляем следующий po2
    if (po2->pNext) { //если после po2 есть узел
        po2->pNext->pPrev = po1;
    } else {
        pLast = po1; // po1 становится последним
    }

    // меняем связи между po1 и po2
    po2->pPrev = po1->pPrev;
    po1->pNext = po2->pNext;
    po2->pNext = po1;
    po1->pPrev = po2;
}

void SortAllTowns() {
    int was_changed = 1;
    while (was_changed) {
        was_changed = 0;
        Town *p1 = pFirst; // каждый проход начинаем с первого элемента, пузырькова сортировочка
        while (p1 && p1->pNext) {
            Town *p2 = p1->pNext;
            if (strcmp(p1->Name, p2->Name) > 0) {

                SwapTowns(p1, p2);
                was_changed = 1;
            }
            p1 = p1->pNext; // продвигаем всегда (после swap p1 теперь прежний p2)
        }
    }
}



int main(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
    Town *po = 0;
    PrintAllTowns();

    po = Create("Saint-Petersburg");
    if (po == 0) return 1;
    AddToList(po);

    //10 раз минимум, реализовать ввод через пользователя чтоби было классно

    po = Create("Beijing");
    if (po == 0) return 1;
    AddToList(po);

    PrintAllTowns();
    DelFromList(po);
    PrintAllTowns();
    //po = SearchForTown("Paris");
    Destroy(po);

    po = Create("Myski");
    if (po == 0) return 1;
    AddToList(po);

    po = Create("Kemerovo");
    if (po == 0) return 1;
    AddToList(po);

    po = Create("Anapa");
    if (po == 0) return 1;
    AddToList(po);

    po = Create("Moscow");
    if (po == 0) return 1;
    AddToList(po);

    po = Create("Tblilisi");
    if (po == 0) return 1;
    AddToList(po);

    PrintAllTowns();
    SortAllTowns();
    PrintAllTowns();

    po = SearchForTown("Myski");
    if (po == 0) return 1;
    DelFromList(po);
    Destroy(po);
    PrintAllTowns();
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
 *
 *
 *
 *
 *
 */
