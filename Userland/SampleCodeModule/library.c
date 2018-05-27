#include <library.h>

void sys_print_string(char* string) {
    systemCall(0,string,0,0);
}
