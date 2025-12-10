#include <stdio.h>
#include <stdarg.h>

void display(char* format, ...){
    int d;
    double f;
    va_list factor;
    va_start(factor,format);
    for (char * c = format; *c; c++){
        if(*c!='%'){printf("%c",*c); continue;}
        switch(* ++c){
            case 'd': d = va_arg(factor, int);
                printf("%d",d);
                break;
            case 'f': f = va_arg(factor, double);
                printf("%.2f",f);
                break;
            default: printf("%c",*c);
        }
    }
    va_end(factor);
}

int main(void){
    display("Count:%d\trice:%f",24,68.4);


    printf("Count:%d\trice:%f",24,68.4);
    return 0;

}