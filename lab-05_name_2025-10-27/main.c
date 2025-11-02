#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h> //отладка маллок
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define free(p) _free_dbg(p,_NORMAL_BLOCK)
//#define malloc(p) _malloc_dbg(p,_NORMAL_BLOCK, __FILE__, __LINE__);


struct town {
    struct town *pNext;
    struct town *pPrev;
    char Name[]; //хитрость си, в с++ НЕЛЬЗЯ
}; //последнее поле может быть массивом с пустым размером

typedef struct town Town;
Town *pFirst =0, *pLast = 0;

Town *Create (const char* name) {
    size_t len = strlen(name);
    Town *po = (Town *)malloc(sizeof(Town)+len+1);
    if (po==0) return 0;
    strncpy_s(po->Name,len+1,name,len+1);
    return po;
}

void Destroy(Town *po) {
    if (po) free(po);
}

void AddToList(Town *po) {
    if (pLast) pLast ->pNext =po;
    po -> pPrev = pLast;
    pLast = po;
    po -> pNext = 0;
    if (pFirst==0) pFirst = po;

}

void DelFromList(Town * po){}

Town * SearchForTown(const char * name){}




void PrintAllTowns(void) {
    printf("All Towns:\n");
    Town *po = pFirst;
    while (po) {
        printf("Name: %s\n",po -> Name);
        po = po->pNext;
    }

}

void SortAllTowns(){} //по алфавиту







int main(void) {
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF(_CRTOBG_LEAK_CHECK_DF|_CRTDBG_CHECK_ALWAYS_DF));
    Town *po = 0;
    PrintAllTowns();
    po = Create("Saint-Petersburg"); if (po==0) return 1;;AddToList(po);
    //10 раз минимум, реализовать ввод через пользователя чтоби было классно
    po = Create("Beijing");
    PrintAllTowns();
    po = SearchForTown("Paris");
    DelFromList(po);
    Destroy(po);


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