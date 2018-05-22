#include "font.h"
#include "videoDriver.h"

static unsigned char ** start_video_position = (unsigned char**)0x0005C28;

Color background_color={255,70,0};

int out_of_range_pixel(int x, int y) {
	return (x >= 0) && (x <= SCREEN_WIDTH) && (y >= 0) && (y <= SCREEN_HEIGHT);
}

unsigned char * get_video_start(){
	return *start_video_position;
}

void paint_pixel(int x, int y, Color color) {
	if (!out_of_range_pixel(x, y))
		return;

	unsigned char * pixel_address;
	pixel_address = get_video_start() + 3*(x + y*SCREEN_WIDTH);
	*pixel_address = color.blue;
	*(pixel_address+1) = color.green;
	*(pixel_address+2) = color.red;
}

void paint_background(){
	for(int i=0; i<SCREEN_WIDTH; i++){
		for(int j=0; j<SCREEN_HEIGHT; j++){
			paint_pixel(i,j,background_color);
		}
	}
}

void print_character(int x,int y,char c,Color color){
	if(c==8){//retroseso
		//delete();
	}
	else if(c==10){
		//enter();
	}
	else{
		unsigned char * character=pixel_map(c);

		for(int y_aux=0;y_aux<CHAR_HEIGHT;y_aux++){
			for(int x_aux=0;x_aux<CHAR_WIDTH;x_aux++){
				char character_aux=character[y_aux];
				character_aux >>= 8-x_aux;

				if(character_aux%2==1){
					paint_pixel(x+x_aux,y+y_aux,color);
				}
				else{
					paint_pixel(x+x_aux,y+y_aux,background_color);
				}
			}
		}

	}

}
