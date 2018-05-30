#ifndef _SHELL_H
#define _SHELL_H

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6
#define MAX_SIZE 512

void shell();
void get_command();
void process_command();
void display_time();
void test(int id);
void help();

extern void opcode();
extern void zero();

#endif