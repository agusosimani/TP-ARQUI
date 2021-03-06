#include <font.h>
#include <videoDriver.h>
#include <videoModeInfo.h>
#include <stdint.h>
#include <time.h>

static unsigned char ** start_video_position = (unsigned char**)0x0005C28;
static int x_resolution;
static int y_resolution;


Color background_color={176,224,230};
Color font_color={0,0,0};

Position screen_position={0,768-CHAR_HEIGHT*2};
Position write_position={0,768-CHAR_HEIGHT};

void set(){
	x_resolution = get_x_resolution();
	y_resolution = get_y_resolution();
}

int getX(){
	return screen_position.x;
}

int getY(){
	return screen_position.y;
}

int out_of_range_pixel(Position pos) {
	return (pos.x >= 0) && (pos.x <= x_resolution) && (pos.y >= 0) && (pos.y <= y_resolution);
}

unsigned char * get_video_start(){
	return *start_video_position;
}

void paint_pixel(Position pos, Color color) {
	if (!out_of_range_pixel(pos))
		return;

	unsigned char * pixel_address;
	pixel_address = get_video_start() +3*(pos.x + pos.y*x_resolution);
	*pixel_address = color.blue;
	*(pixel_address+1) = color.green;
	*(pixel_address+2) = color.red;
}


void move_line(){
	write_position.x=0;
	write_position.y=768-CHAR_HEIGHT;
	Color pixel_color;
	unsigned char * pixel_address;
	for(int x=0 ;x<x_resolution;x++){
		for(int y=screen_position.y;y<y_resolution;y++){
			Position aux={x,y};
			pixel_address = get_video_start() + 3*(x + y*x_resolution);
			pixel_color.blue=*(pixel_address);
			pixel_color.green=*(pixel_address+1);
			pixel_color.red=*(pixel_address+2);
			aux.y-=CHAR_HEIGHT;
			paint_pixel(aux,pixel_color);
		}
	}
	screen_position.y-=CHAR_HEIGHT;
	screen_position.x=0;

	//clear last renglon
	for(int x=0;x<x_resolution;x++){
		for(int y=y_resolution-CHAR_HEIGHT;y<y_resolution;y++){
			Position aux={x,y};
			paint_pixel(aux,background_color);
		}
	}
}

void paint_background(){
	set();
	for(int i=0; i<x_resolution; i++){
		for(int j=0; j<y_resolution; j++){
			Position pos={i,j};
			paint_pixel(pos,background_color);
		}
	}
	Position aux = {0,768-CHAR_HEIGHT*2};
    screen_position = aux;
    Position aux2 = {0,768-CHAR_HEIGHT};
    write_position= aux2;
}

void print_character(char c){
	print_character_with_data(c,write_position,font_color);
    if(c!=10){
        screen_position.x+=CHAR_WIDTH;
        write_position.x+=CHAR_WIDTH;
    }
}


void backspace(){
	write_position.x-=CHAR_WIDTH;
	print_character(' ');
	write_position.x-=CHAR_WIDTH*2;
}

void print_character_with_data(char c,Position pos,Color color){
	if(c==8){
		backspace();
	}
	else if(c==10){
		move_line();
	}
	else{
		unsigned char * character=pixel_map(c);
		Position aux;
		for(aux.y=0;aux.y<CHAR_HEIGHT;aux.y++){
			for(aux.x=0;aux.x<CHAR_WIDTH;aux.x++){
				unsigned char character_aux=character[aux.y];
				character_aux >>= 8-aux.x;
				Position pos_aux={pos.x+aux.x,pos.y+aux.y}; //le sumo el actual en y para no pisar lineas ya escritas
				if(character_aux%2==1){
					paint_pixel(pos_aux,color);
				}
				else{
					paint_pixel(pos_aux,background_color);
				}
			}
		}
		pos.x+=CHAR_WIDTH;
	}
}

int strlen(char * string){
	int i=0;
	while(string[i]!=0){
		i++;
	}
	return i;
	}

void print_string_with_data(char * string,Position pos,Color color){//al terminar un string,hace un enter automatico
	int lenght=strlen(string);
	for(int i=0;i<lenght;i++){
		print_character_with_data(string[i],pos,color);
		pos.x+=CHAR_WIDTH;//corro la x acual de la pantalla
	}
	write_position.x += lenght*CHAR_WIDTH;
	write_position.y=768-CHAR_HEIGHT;
}

void print_string(char* string){
	print_string_with_data(string,write_position,font_color);
}


int num_to_string(uint64_t  value, char* buffer,int base)	{
		char *p = buffer;
		char *p1, *p2;
		uint32_t digits = 0;

		//Calculate characters for each digit
		do
		{
			uint32_t remainder = value % base;
			*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
			digits++;
		}
		while (value /= base);

		// Terminate string in buffer.
		*p = 0;

		//Reverse string in buffer.
		p1 = buffer;
		p2 = p - 1;
		while (p1 < p2)
		{
			char tmp = *p1;
			*p1 = *p2;
			*p2 = tmp;
			p1++;
			p2--;
		}

		return digits;
	}

void print_number_with_data(uint64_t  number,int base,Position pos,Color color){
	//paso number a char* y se lo paso a print_string
	char str_number[MAX_DIGITS];
	num_to_string(number,str_number,base);
	print_string_with_data(str_number,pos,color);
	return;
}

void print_integer(int number){
	print_number_with_data(number,10,write_position,font_color);

}

void print_hexa(uint64_t  number){
	print_number_with_data(number,16,write_position,font_color);
}

int n_tu(int number, int count) {
    int result = 1;
    while(count-- > 0)
        result *= number;

    return result;
}

/*** Convert float to string ***/
void float_to_string(float f, char r[]) {
    long long int length, length2, i, number, position, sign;
    float number2;

    sign = -1;   // -1 == positive number
    if (f < 0)
    {
        sign = '-';
        f *= -1;
    }

    number2 = f;
    number = f;
    length = 0;  // Size of decimal part
    length2 = 0; // Size of tenth

    /* Calculate length2 tenth part */
    while( (number2 - (float)number) != 0.0 && !((number2 - (float)number) < 0.0) )
    {
         number2 = f * (n_tu(10.0, length2 + 1));
         number = number2;

         length2++;
    }

    /* Calculate length decimal part */
    for (length = (f > 1) ? 0 : 1; f > 1; length++)
        f /= 10;

    position = length;
    length = length + 1 + length2;
    number = number2;
    if (sign == '-')
    {
        length++;
        position++;
    }

    for (i = length; i >= 0 ; i--)
    {
        if (i == (length))
            r[i] = '\0';
        else if(i == (position))
            r[i] = '.';
        else if(sign == '-' && i == 0)
            r[i] = '-';
        else
        {
            r[i] = (number % 10) + '0';
            number /=10;
        }
    }
}


void print_double_with_data(float number,Position pos,Color color){
	char str[MAX_DIGITS];
	float_to_string(number,str);
	print_string_with_data(str,pos,color);

}

void print_double(float number){
	print_double_with_data(number,write_position,font_color);
}

//FUNCTION TO PRINT CLOCK

Position print_digit_struct(int number, Color color, Position position) {
    unsigned char * digit = clock_digits_map(number);
    Position posaux = position;
    unsigned char pixel;

    for (int y=0; y<CLOCK_DIGIT_HEIGHT; y++) {
        for (int j=0; j<8; j++) {
            pixel = digit[(y*8)+j];
            for (int x=0; x<8; x++) {
                Position to_write = {position.x + x, position.y + y};
                if (((pixel >> (8-x))%2)!=0) {
                    paint_pixel(to_write,color);
                } else {
                    paint_pixel(to_write,background_color);
                }
            }
            position.x += 8;
        }
        position.x = posaux.x;
    }
    posaux.x += (CLOCK_DIGIT_WIDTH+15);
    return posaux;
}

void print_digit(int number, int r, int g, int b, int * xpos) {
    Color color = {r,g,b};
    if (*xpos == 0) {
        *xpos = x_resolution/2 - 309;
    }
    Position position = {*xpos,y_resolution/2 -21};
    Position ret = print_digit_struct(number,color,position);
    *xpos = ret.x;
}

void set_font_color(int r, int g, int b) {
	font_color.red = r;
	font_color.green = g;
	font_color.blue = b;
}

void set_back_color(int r, int g, int b){
    background_color.red=r;
    background_color.green=g;
    background_color.blue=b;
}
