#include <library.h>

void sys_print_string(char* string) {
    systemCall(0,string,0,0);
}

void sys_print_integer(int num) {
    systemCall(1,num,0,0);
}

void put_char(char c) {
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

//Compara 2 cadenas, devuelve 0 si son iguales
int strcmp(char * s1, char * s2){
    while(*s1 && *s2 && *s1 == *s2){
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int strncmp(char * s, char * t, unsigned int n) {
    int i;
    for (i = 0; i < n-1 && s[i] != '\0' && t[i] != '\0' && s[i] == t[i]; i++)
        ;
    return s[i]-t[i];
}

//Devuelve TRUE si start es subcadena inicial de str, FALSE (0)
//si esto no pasa
int starts_with(char * str, char * start){
    while(*str != 0 && *start != 0){
        if(*(str++) != *(start++)){
            return 0;
        }
    }
    return *start == 0;
}