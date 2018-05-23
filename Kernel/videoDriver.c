#include "font.h"
#include "videoDriver.h"

static unsigned char ** start_video_position = (unsigned char**)0x0005C28;

Color background_color={176,224,230};
Position screen_position={0,0};//CAMBIARLO PARA QUE Y ARRANQUE DE ABAJO CUANDO SEPAMOS SCREEN HEIGHT

int out_of_range_pixel(Position pos) {
	return (pos.x >= 0) && (pos.x <= SCREEN_WIDTH) && (pos.y >= 0) && (pos.y <= SCREEN_HEIGHT);
}

unsigned char * get_video_start(){
	return *start_video_position;
}

void paint_pixel(Position pos, Color color) {
	if (!out_of_range_pixel(pos))
		return;

	unsigned char * pixel_address;
	pixel_address = get_video_start() + 3*(pos.x + pos.y*SCREEN_WIDTH);
	*pixel_address = color.blue;
	*(pixel_address+1) = color.green;
	*(pixel_address+2) = color.red;
}

void paint_background(){
	for(int i=0; i<SCREEN_WIDTH; i++){
		for(int j=0; j<SCREEN_HEIGHT; j++){
			Position pos={i,j};
			paint_pixel(pos,background_color);
		}
	}
}

void print_character(char c,Position pos,Color color){
	if(c==8){
		//delete();
	}
	else if(c==10){
		//enter();
	}
	else{
		unsigned char * character=pixel_map(c);
		Position aux;
		for(aux.y=0;aux.y<CHAR_HEIGHT;aux.y++){
			for(aux.x=0;aux.x<CHAR_WIDTH;aux.x++){
				unsigned char character_aux=character[aux.y];
				character_aux >>= 8-aux.x;
				Position pos_aux={pos.x+aux.x,pos.y+aux.y+screen_position.y};//le sumo el actual en y para no pisar lineas ya escritas
				if(character_aux%2==1){
					paint_pixel(pos_aux,color);
				}
				else{
					paint_pixel(pos_aux,background_color);
				}
			}
		}
	}
}

void enter(){
	//if(screen_position.y==SCREEN_HEIGHT) no more SCREEN
	//subi la pantalla
	//sino
	screen_position.y+=CHAR_HEIGHT;


}

int strlen(char * string){
	int i=0;
	while(string[i]!=0){
		i++;
	}
	return i;
	}


void print_string(char * string,Position pos,Color color){//al terminar un string,hace un enter automatico
	int lenght=strlen(string);
	for(int i=0;i<lenght;i++){
		print_character(string[i],pos,color);
		pos.x+=CHAR_WIDTH;
	}
	enter();
}
