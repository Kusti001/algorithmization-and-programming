#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_snake(const char *str) {
    int cnt = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '_') {
            cnt++;
        }
    }
    return cnt;
}

int is_camel(const char *str) {
    int cnt = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            cnt++;
        }
    }
    return cnt;
}

char *snake_to_camel(const char *buffer, const int sz) {
    char *new_buffer = malloc(sizeof(char) * (sz + 1 - is_snake(buffer)));
    int pos = 0;
    int flag = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (i == 0) {
            new_buffer[pos] = buffer[i];
            pos++;
        } else if (buffer[i] == '_') {
            flag = 1;
        } else if (flag == 1) {
            new_buffer[pos] = buffer[i] - 32;
            pos++;
            flag = 0;
        }
        else {
            new_buffer[pos] = buffer[i];
            pos++;
        }
    }
    new_buffer[pos] = '\0';
    return new_buffer;
}

char *camel_to_snake(const char *buffer, int sz) {
    char *new_buffer = malloc(sizeof(char) * (sz +1 + is_camel(buffer)));
    int pos = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
            new_buffer[pos] = '_';
            pos++;
            new_buffer[pos] = buffer[i] + 32;
            pos++;
        } else {
            new_buffer[pos] = buffer[i];
            pos++;
        }
    }
    new_buffer[pos] = '\0';
    return new_buffer;
}

void check_str(char *buffer, const int sz, FILE *end_file) {
    //начинается с цифры - ошибка
    if (buffer[0] >= '0' && buffer[0] <= '9') {
        fputs("ERROR\n", end_file);
        printf("%s - > ERROR (starts with num)\n",buffer);
        return;
    }
    //начинается с заглавной буквы - ошибка
    if (buffer[0] >= 'A' && buffer[0] <= 'Z') {
        fputs("ERROR\n", end_file);
        printf("%s - > ERROR (starts with capital letter)\n",buffer);
        return;
    }
    //если есть _
    if (is_snake(buffer)) {
        //если есть _ и заглавные буквы - ошибка
        if (is_camel(buffer)) {
            fputs("ERROR\n", end_file);
            printf("%s - > ERROR (two types of codestyle)\n",buffer);
            return;
        }
        char *result = snake_to_camel(buffer, sz);
        fputs(result, end_file);
        fputs("\n", end_file);
        printf("%s - > %s (snake_to_camel)\n", buffer, result);
        free(result);
        return;
    }

    if (is_camel(buffer)) {
        char *result = camel_to_snake(buffer, sz);
        fputs(result, end_file);
        fputs("\n", end_file);
        printf("%s - > %s (camel_to_snake)\n", buffer, result);
        free(result);
        return;
    }

    fputs(buffer, end_file);
    fputs("\n", end_file);
    printf("%s - > %s (nothing)\n", buffer, buffer);
}
int size = 0;
char * convert_str(char * buffer,FILE *start_file, FILE *end_file, const long start_pos, const long end_pose, const int len) {
    if (len > size) {
        size = len;
        buffer = realloc(buffer, size);
        if (buffer == NULL) {
            return NULL;
        }
    }

    fseek(start_file, start_pos, SEEK_SET);
    fread(buffer, sizeof(char), len, start_file);
    buffer[len] = '\0';

    check_str(buffer, len, end_file);

    fseek(start_file, end_pose, SEEK_SET);
    return buffer;
}

int main() {
    FILE *start_file = fopen("1.txt", "rb");
    FILE *end_file = fopen("2.txt", "w");

    if (!start_file) {
        printf("File 1.txt does not exist\n");
        return 1;
    }

    long start_pos = ftell(start_file);
    long end_pos;

    printf("file start:\n\n");

    int c;

    /*
    while ((c = fgetc(start_file)) != EOF) {
        // Печатаем ВСЕ символы понятно
        if (c == 10) {
            printf("\\n");
        } else if (c == 13) {
            printf("\\r");
        } else if (c >= 32 && c <= 126) {
            printf("%c", c);
        } else {
            printf("[%d]", c);
        }

        // Обрабатываем конец строки Windows (\r\n)
        if (c == '\n') {
            end_pos = ftell(start_file);
            printf(" start=%ld, end=%ld, length=%ld\n", start_pos, end_pos, end_pos - start_pos);
            start_pos = end_pos;
        }
    }
    end_pos = ftell(start_file);
    printf(" start=%ld, end=%ld, length=%ld\n",start_pos, end_pos, end_pos - start_pos);
*/
    char *buffer = malloc(sizeof(char) * (2));
    if (buffer == NULL) {
        return 1;
    }
    while ((c = fgetc(start_file)) != EOF) {
        if (c == '\n') {
            end_pos = ftell(start_file);
            buffer = convert_str(buffer,start_file, end_file, start_pos, end_pos, end_pos - start_pos - 1);
            start_pos = end_pos;
        }
    }
    end_pos = ftell(start_file);
    buffer = convert_str(buffer,start_file, end_file, start_pos, end_pos, end_pos - start_pos);

    free(buffer);
    printf("\nfile end");

    fclose(start_file);
    fclose(end_file);

    return 0;
}


/* 1.txt -> 2.txt
// thisIsVarName
// this_is_var_name

// реверс делать из cmcase в
ПРИМЕР
ThisISVar1 // this_is_var_2
var2 //var2
Var3 //error
123 //error
var99 //var99
a_b_c_d // aBCD




// считать посимвольно?


мысль - хранить указатель на начало строки и двигать его пока не дойдём до /n
*/
