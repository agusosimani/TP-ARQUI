#ifndef _SHELL_H
#define _SHELL_H

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6
#define MAX_SIZE 128
#define MAX_NAME 15
#define MAX_DESCRIPTION 80
#define COMMANDS 7
#define EOF -1
#define MAX_WORD_LENGTH 124
#define MAX_WORDS 32
#define DR 0
#define DG 255
#define DB 255

void shell();
void get_command(char* buffer);
void process_command(char* buffer);
void display_time();
void help();
void exit();
void test_opcode();
void test_zero();
void font_color();
void back_color();

extern void opcode();
extern void zero();

#endif