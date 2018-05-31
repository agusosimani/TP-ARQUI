#ifndef _SHELL_H
#define _SHELL_H

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6
#define MAX_SIZE 128
#define MAX_NAME 15
#define MAX_DESCRIPTION 40
#define COMMANDS 6

void shell();
void get_command(char* buffer);
void process_command(char* buffer);
void display_time();
void help();
void exit();

extern void opcode();
extern void zero();

#endif