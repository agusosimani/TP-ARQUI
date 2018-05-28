#include <library.h>

//ESTAN LAS DE EJEMPLO.. DESPUES SOLO HAY QUE PONER LAS QUE VAMOS A USAR

void sys_print_string(char* string) {
    systemCall(0,string,0,0);
}

void sys_print_integer(int num) {
    systemCall(1,num,0,0);
    return 900;
}