#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#define MAX_DIGITS 256

#include <stdint.h>


typedef struct Color{
  char red;
  char green;
  char blue;
}Color;

typedef struct Position{
  int x;
  int y;
}Position;

int out_of_range_pixel(Position pos);
unsigned char * get_video_start();
void paint_pixel(Position pos, Color color);
void paint_background();
void print_character_with_data(char c,Position pos,Color color);
void print_string_with_data(char * string,Position pos,Color color);
void print_number_with_data(uint64_t  number,int base,Position pos,Color color);
void print_double_with_data(float number,Position pos,Color color);
void set();
void print_double(float number);
void print_integer(int number);
void print_hexa(uint64_t  number);
void print_string(char* string);
void print_character(char c);
int getX();
int getY();
void move_line();
void print_digit(int number, int r, int g, int b, int * xpos, int * ypos);

#endif //VIDEODRIVER_H
