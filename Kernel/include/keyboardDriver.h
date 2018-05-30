
#ifndef _KEYBOARDDRIVER_H
#define _KEYBOARDDRIVER_H

#define BUFFERSIZE 10

void keyboard_handler();
void put_character(char character);
void get_char(char * character);
extern int scan_key();
extern int keyboard_wait();


#endif