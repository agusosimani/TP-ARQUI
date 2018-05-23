#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800



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


// funciones para escribir y leer de video


#endif //VIDEODRIVER_H
