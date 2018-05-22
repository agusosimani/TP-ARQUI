#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800



typedef struct Color{
  char red;
  char green;
  char blue;
}Color;

int out_of_range_pixel(int x, int y);
unsigned char * get_video_start();
void paint_pixel(int x, int y,Color color);
void paint_background();
void print_character(int x,int y,char c,Color color);



// funciones para escribir y leer de video


#endif //VIDEODRIVER_H
