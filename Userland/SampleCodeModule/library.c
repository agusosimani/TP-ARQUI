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

//Compares 2 strings. Returns 0 if they are equal
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

//Returns true(!= 0) if start is an initial substring of str and 0 if not
int starts_with(char * str, char * start){
    while(*str != 0 && *start != 0){
        if(*(str++) != *(start++)){
            return 0;
        }
    }
    return *start == 0;
}