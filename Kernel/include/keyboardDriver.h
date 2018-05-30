
#ifndef _KEYBOARDDRIVER_H
#define _KEYBOARDDRIVER_H

#define BUFFERSIZE 10

void keyboard_handler();
void put_character(char character);
extern int scan_key();


#endif