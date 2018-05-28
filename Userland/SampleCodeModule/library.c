#include <library.h>

void sys_print_integer(int num) {
    systemCall(1,num,0,0);
}

void sys_print_string(char* string) {
    systemCall(0,string,0,0);
}