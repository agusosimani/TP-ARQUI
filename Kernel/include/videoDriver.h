#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MAX_DIGITS 40
#define ROW_LIMIT 25
#define BG_R 255
#define BG_G 140
#define BG_B 250
#define color_red 0
#define color_green 0
#define color_blue 0


// funciones para escribir y leer de video
int boundedPixel(int x, int y);
void paintPixel(int x, int y, char R, char G, char B);
unsigned char * getVideoPix();
void paintBackGround();
void paintCharSpace(int current_x, int current_y, char B, char G, char R);


#endif //VIDEODRIVER_H
