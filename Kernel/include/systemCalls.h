#ifndef _SYSTEMCALLS_H
#define _SYSTEMCALLS_H

#include <stdint.h>

// Los argumentos se pasan de la siguiente forma:
//    Si el dato es INTEGER:
//        se van ocupando los registros rdi, rsi, rdx, rcx, r8 y r9 en orden
//
// Para devolver los valores:
//    Si el dato es INTEGER:
//        se utiliza rax y rdx


// First argument indicates which function should be called
// Remaining arguments will be passed as function parameters
void systemCallDispatcher(uint64_t id, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5);

void systemCallHandler(uint64_t id, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5);

void hour(int * h);

void minutes(int * m);

void seconds(int * s);

void x_res(int * x);

void y_res(int * y);

#endif //_SYSTEMCALLS_H