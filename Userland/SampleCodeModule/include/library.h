#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <stdint.h>
#include <stdarg.h>

extern void systemCall(uint64_t id, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5);

void get_char(char* c);
void put_char(char c);
void clear();
void get_hour(int * h);
void get_minutes(int * m);
void get_seconds(int * s);
void beep();
void put_digit(int number, int r, int g, int b, int* x);

void printf(char* fmt, ...);
//Compares 2 strings. Returns 0 if they are equal
int strcmp(char * s1, char * s2);

#endif
