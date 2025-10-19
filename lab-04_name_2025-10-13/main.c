/*
массив - карта 10х10
случайные препятствия
Ходить диагонально НЕЛЬЗЯ
случайные старт и финиш
Вывод - матрица с весами
Вывод - матрица с путём
примерно половина клеток непроходима

+ использовать веса, отличные от +1 (горки и тп) не только нули проходимые

-1 клетка непроходима
0 проходимая клетка
1 начало
-2 финиш


АЛГОРИТМ
I.
1. Найти клетку старт(1)
2. Всем проходимым клеткам вокруг устанавливаем2
3. Найти клетки с 2
4. Всем клеткам вокруг ставим 3
и тд
ПОВТОРЯЕМ, пока не дойдем до клетки финиша

II.
идём от финиша к старту, выбирая наименьшие значения вокруг



 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double wall_percent = 0.4;
int size = 10;
int start_x, start_y,end_x,end_y;

int Ar[10][10];
int dist[10][10];

void printArray(int Array[10][10]) {
 for (int i = 0; i < size; i++) {
  for (int j = 0; j < size; j++) {
   printf("%3d ", Array[i][j]);
  }
  printf("\n");
 }
 printf("----------------------------------------\n");
}

void createMap(void) {
 srand(time(NULL));
 //создание препятствий
 for (int x = 0; x < size; x++) {
  for (int y = 0; y < size; y++) {
   if ((double)rand() / RAND_MAX < wall_percent) {
    Ar[x][y] = -1;
   } else {
    //Ar[i][j] = rand() % 3 + 1;
   }
  }
 }

 //выбор старта
 while (1) {
  start_x = rand() % size;
  start_y = rand() % size;
  if (Ar[start_x][start_y] == 0) {
   Ar[start_x][start_y] = 1;
   break;
  }
 }

 //выбор финиша
 while (1) {
  time_t curtime;
  time(&curtime);
  srand((unsigned int) curtime);
  end_x = rand() % size;
  end_y = rand() % size;
  if (Ar[end_x][end_y] == 0) {
   Ar[end_x][end_y] = 2; // Финиш
   break;
  }
 }
}

void finddist(void) {
 // Инициализация dist: -1 для всех клеток (не посещено)
 for (int i = 0; i < size; i++) {
  for (int j = 0; j < size; j++) {
   dist[i][j] = -1;
  }
 }

 // Очередь для BFS
 int queue[100][2]; // Хранит пары {x, y}
 int front = 0, rear = 0;

 // Начало: старт
 dist[start_x][start_y] = 0; // Расстояние от старта = 0
 queue[rear][0] = start_x;
 queue[rear][1] = start_y;
 rear++;

 // Направления: вверх, вниз, влево, вправо
 int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

 while (front < rear) {
  // Извлекаем текущую клетку
  int curr_x = queue[front][0];
  int curr_y = queue[front][1];
  front++;

  // Если достигли финиша, можно остановиться
  if (Ar[curr_x][curr_y] == -2) {
   break;
  }

  // Проверяем соседей
  for (int d = 0; d < 4; d++) {
   int ni = curr_x + directions[d][0];
   int nj = curr_y + directions[d][1];

   // Проверяем: в границах, проходима, не посещена
   if (ni >= 0 && ni < size && nj >= 0 && nj < size &&
       Ar[ni][nj] != -1 && dist[ni][nj] == -1) {
    dist[ni][nj] = dist[curr_x][curr_y] + 1;
    queue[rear][0] = ni;
    queue[rear][1] = nj;
    rear++;
       }
  }
 }
}









int main(void) {
 printArray(Ar);

 createMap();
 //вывод заполненной карты
 printArray(Ar);


 finddist();
 printArray(dist);















 return 0;
}