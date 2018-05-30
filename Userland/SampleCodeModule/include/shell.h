#ifndef _SHELL_H
#define _SHELL_H

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6

void shell();
void display_time();
void test_zero();
void test_opcode();

extern void opcode();
extern void zero();

#endif