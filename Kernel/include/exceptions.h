#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <stdint.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6
#define REGISTERS 16

void exceptionDispatcher(int exception, uint64_t * rsp);
void zero_division(uint64_t * rsp);
void opcode(uint64_t * rsp);

void printRegisters(uint64_t * rsp);

static char* registers[] = {"RAX: ", " RBX: ", " RCX: ", " RDX: ", " RBP: ", "RDI: ", " RSI: ", " R8: "
        , " R9: ", " R10: ", "R11: ", " R12: ", " R13: ", " R14: ", " R15: ", " RIP: "};

#endif