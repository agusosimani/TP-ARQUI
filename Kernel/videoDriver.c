#include "font.h"
#include "videoDriver.h"

static unsigned char ** video_start = (unsigned char**)0x0005C28;
static unsigned int current_x = 0;
static unsigned int current_y = SCREEN_HEIGHT-16;


int boundedPixel(int x, int y) {
	return (x >= 0) && (x <= SCREEN_WIDTH) && (y >= 0) && (y <= SCREEN_HEIGHT);
}

unsigned char * getVideoPix(){
	return *video_start;
}

void paintPixel(int x, int y, char B, char G, char R) {
	if (!boundedPixel(x, y))
		return;

	unsigned char * pixel_address;
	pixel_address = getVideoPix() + 3*(x + y*SCREEN_WIDTH);
	*pixel_address = B;
	*(pixel_address+1) = G;
	*(pixel_address+2) = R;
}

void paintBackGround(){
	for(int i=0; i<SCREEN_WIDTH; i+=1){
		for(int j=0; j<SCREEN_HEIGHT; j+=1){
			paintPixel(i,j,BG_B,BG_G,BG_R);
		}
	}
}

void paintCharSpace(int current_x, int current_y, char B, char G, char R){
	for(int i=0; i<8; i++){
		for(int j=0; j<16; j++){
			paintPixel(current_x+i, current_y+j, B, G, R);
		}
	}
}
