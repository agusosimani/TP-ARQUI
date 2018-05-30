#include <library.h>

//ESTAN LAS DE EJEMPLO.. DESPUES SOLO HAY QUE PONER LAS QUE VAMOS A USAR

void sys_print_string(char* string) {
    systemCall(0,string,0,0);
}

void sys_print_integer(int num) {
    systemCall(1,num,0,0);
}

void sys_print_char(char c) {
    systemCall(2,c,0,0);
}

void sys_display_time(int color) {
    systemCall(3,color,0,0);
}

void sys_clear() {
    systemCall(4,0,0,0);
}

void get_char(char* c) {
    systemCall(5,c,0,0);
}