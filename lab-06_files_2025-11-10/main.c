#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <_time.h>


int main(void) {
    FILE *file = fopen("good.txt", "r");
    if (file == NULL) {
        printf("File does not exist\n");
        return 1;
    }
    char buffer[100];
       while (fgets(buffer, sizeof(buffer), file)) { // если считалось норм число

           printf("%s\r", buffer);
           sleep(1);
       }


    return 0;
}


// start.txt -> final.txt
// thisIsVarName
// this_is_var_name

// реверс делать

// считаь посимвольно?