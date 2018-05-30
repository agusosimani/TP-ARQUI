#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <stdint.h>

extern void systemCall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx);

void sys_print_string(char* string);
void sys_print_integer(int num);
void put_char(char c);
void sys_display_time(int color);
void sys_clear();
void get_char(char* c);

#endif