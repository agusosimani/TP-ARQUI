#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#define MAX_DIGITS 256

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
void print_character(char c,Position pos,Color color);
void print_string(char * string,Position pos,Color color);
void print_integer(int number,int base,Position pos,Color color);
void print_double(float number,Position pos,Color color);
void set();


// funciones para escribir y leer de video


#endif //VIDEODRIVER_H
