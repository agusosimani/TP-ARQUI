#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <stdint.h>

extern void systemCall(uint64_t edi, uint64_t esi, uint64_t edx, uint64_t ecx);

void sys_print_string(char* string);

#endif