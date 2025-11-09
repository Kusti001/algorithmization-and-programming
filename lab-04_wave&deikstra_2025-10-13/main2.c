#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double wall_percent = 0.4;
int size = 10;
int start_x, start_y, end_x, end_y;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // направления: вверх, вниз, влево, вправо

int Ar[10][10];      // карта: -1 (стена), 0 (старт), 1 (финиш), 2-6 (проходимые клетки)
int dist[10][10];    // расстояния от старта
int path[10][10];

void printArray(int Array[10][10], int isPath) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (isPath) {
                // X для пути (2), S для старта (0) и F для финиша (1), 0 для всего остального
                if (Array[i][j] == 0) {
                    printf("%3c ", 'S');
                } else if (Array[i][j] == 1) {
                    printf("%3c ", 'F');
                } else if (Array[i][j] == 2) {
                    printf("%3c ", 'X');
                } else {
                    printf("%3d ", 0);
                }
            } else {
                // S для старта (0), F для финиша (1), веса остальных
                if (Array[i][j] == 0) {
                    printf("%3c ", 'S');
                } else if (Array[i][j] == 1) {
                    printf("%3c ", 'F');
                } else {
                    printf("%3d ", Array[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("----------------------------------------\n");
}

void createMap(void) {
    srand(time(NULL));
    // создание препятствий и весов
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if ((double)rand() / RAND_MAX < wall_percent) {
                Ar[x][y] = -1; // стена
            } else {
                Ar[x][y] = (rand() % 5) + 2; // веса 2, 3, 4, 5, 6
            }
        }
    }

    // выбор старта
    for (int i = 0; i < 1000; i++) {
        start_x = rand() % size;
        start_y = rand() % size;
        if (Ar[start_x][start_y] != -1) {
            Ar[start_x][start_y] = 0; // старт
            break;
        }
    }

    // выбор финиша
    for (int i = 0; i < 1000; i++) {
        end_x = rand() % size;
        end_y = rand() % size;
        if (Ar[end_x][end_y] != -1 && (end_x != start_x || end_y != start_y)) {
            Ar[end_x][end_y] = 1; // финиш
            break;
        }
    }
}

void finddist(void) {
    // заполнение dist
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            dist[i][j] = 999; // большое число вместо бесконечности
        }
    }
    dist[start_x][start_y] = 0; // расстояние до старта = 0

    // алгоритм Дейкстры
    while (dist[end_x][end_y] ==999) {
        // ищем непосещённую клетку с минимальным расстоянием
        int min_dist = 999;
        int min_x = -1, min_y = -1;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (path[i][j] != 3 && dist[i][j] < min_dist) {
                    min_dist = dist[i][j]; // на первой итерации минимальной клеткой будет старт, дальше он как МЁД будет разливаться + клетки с 999 он никогда не возьмёт из за их размера
                    min_x = i;
                    min_y = j;
                }
            }
        }

        // если не нашли клетку или дошли до финиша, выходим
        if (min_x == -1 || (min_x == end_x && min_y == end_y)) {
            break;
        }

        // отмечаем клетку как посещённую
        path[min_x][min_y] = 3;

        // проверяем соседей текущей клетки
        for (int d = 0; d < 4; d++) {
            int ni = min_x + directions[d][0];
            int nj = min_y + directions[d][1];

            // если сосед в границах и не стена
            if ((ni >= 0 && ni < size) && (nj >= 0 && nj < size) && Ar[ni][nj] != -1) {
                // вес клетки (2-6 или 0 для финиша)
                int weight;
                if (Ar[ni][nj] == 1) {
                    weight = 0;
                } else {
                    weight = Ar[ni][nj];
                }
                // обновляем расстояние, если нашли путь покороче
                if (dist[min_x][min_y] + weight < dist[ni][nj]) {
                    dist[ni][nj] = dist[min_x][min_y] + weight;
                }
            }
        }
    }
}

void findpath(void) {
    // заполняем path: стены (-1), старт (0), финиш (1), остальное 0
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (Ar[x][y] == 0) {
                path[x][y] = 0; // сохраняем старт
            } else if (Ar[x][y] == 1) {
                path[x][y] = 1; // сохраняем финиш
            } else {
                path[x][y] = -1; // все веса (2-6) и стены заменяем на 0
            }
        }
    }

    // идём от финиша к старту
    int current_x = end_x, current_y = end_y;
    while (current_x != start_x || current_y != start_y) { // пока не дошли до старта
        int found = 0; // маячок, если нашли путь дальше
        int next_x, next_y;
        int current_weight;
        if (Ar[current_x][current_y] == 1) {
            current_weight = 0;
        } else {
            current_weight = Ar[current_x][current_y];
        }

        // проверяем соседей
        for (int d = 0; d < 4; d++) {
            int ni = current_x + directions[d][0];
            int nj = current_y + directions[d][1];
            // ищем соседа, для которого dist[ni][nj] + current_weight = dist[current_x][current_y]
            if (((ni >= 0 && ni < size) && (nj >= 0 && nj < size)) && Ar[ni][nj] != -1) {
                if (dist[ni][nj] + current_weight == dist[current_x][current_y]) {
                    next_x = ni;
                    next_y = nj;
                    found = 1; // нашли соседа, обновляем маячок
                    break; // выбираем первого подходящего соседа (такой только один, тк маршрут тоже ОДИН*)
                }
            }
        }

        // если нашли подходящего соседа, переходим к нему
        if (found) {
            // если не финиш, и не старт
            if (path[next_x][next_y] != 0 && path[next_x][next_y] != 1) {
                path[next_x][next_y] = 2; // отмечаем клетку как часть пути
            }
            current_x = next_x;
            current_y = next_y;
        } else {
            break; // если не нашли подходящего соседа, выходим
        }
    }
}

int main(void) {
    createMap();
    printf("Map:\n");
    printArray(Ar, 0);

    if (Ar[start_x][start_y] != 0 || Ar[end_x][end_y] != 1) {
        printf("Finish or Start weren't created!\n");
        return -1;
    }

    finddist();
    printf("Distances:\n");
    printArray(dist, 0);

    // Проверяем, существует ли путь
    if (dist[end_x][end_y] == 999) {
        printf("There is no path from start to finish!\n");
    } else {
        findpath();
        printf("Path:\n");
        printArray(path, 1);
    }
    return 0;
}