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
void systemCallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx);

void systemCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx);

#endif //_SYSTEMCALLS_H