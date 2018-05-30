#ifndef _SHELL_H
#define _SHELL_H

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6
#define MAX_SIZE 512
#define MAX_NAME 20
#define MAX_DESCRIPTION 40
#define COMMANDS 4

void shell();
void get_command(char* buffer);
void process_command(char* buffer);
void display_time(int param);
void help();

extern void opcode();
extern void zero();

#endif