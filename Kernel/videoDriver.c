#include <font.h>
#include <videoDriver.h>
#include <getData.h>

static unsigned char ** start_video_position = (unsigned char**)0x0005C28;
static int x_resolution;
static int y_resolution;


Color background_color={176,224,230};
Color font_color={0,0,0};
Position screen_position={0,768-CHAR_HEIGHT*2};

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

void enter(){
	//if(screen_position.y==y_resolution) no more SCREEN
	//subi la pantalla
	//sino move esa linea para arriba
	screen_position.x=0;
	screen_position.y-=CHAR_HEIGHT;
}

void move_line(){
	//print_string("entro");
	Color pixel_color;
	unsigned char * pixel_address;
	Position aux_move_pixel=screen_position;
	Position aux_get_pixel={0,0};
	aux_get_pixel.y+=CHAR_HEIGHT;
	for(;aux_get_pixel.x<x_resolution;aux_get_pixel.x++){
		for(;aux_get_pixel.y<y_resolution;aux_get_pixel.y++){
			pixel_address = get_video_start() + 3*(aux_get_pixel.x + aux_get_pixel.y*x_resolution);
			pixel_color.blue=*(pixel_address);
			pixel_color.green=*(pixel_address+1);
			pixel_color.red=*(pixel_address+2);
			paint_pixel(aux_move_pixel,pixel_color);
			print_character_with_data('h',aux_move_pixel,font_color);

			aux_move_pixel.y++;
			//aux_move_pixel.x++;

		}
	}
	//print_string_with_data("hi",aux_get_pixel,font_color);
	/*for(aux_get_pixel.x;aux_get_pixel.x<x_resolution;aux_get_pixel.x++){
		pixel_address = get_video_start() + 3*(aux_get_pixel.x + aux_get_pixel.y*x_resolution);
		pixel_color.blue=*(pixel_address);
		pixel_color.green=*(pixel_address+1);
		pixel_color.red=*(pixel_address+2);
		paint_pixel(aux_move_pixel,pixel_color);
		aux_move_pixel.x++;
	}
	Position aux_move_pixel1={0,0};*/

//	print_string_with_data("hi",aux_move_pixel1,font_color);



	//me posicionno un renglon mas arriba del ultimo escrito
	/*for(aux_get_pixel.y=screen_position.y;aux_get_pixel.y<=y_resolution-16;aux_get_pixel.y+=CHAR_HEIGHT){
		for( aux_get_pixel.x=screen_position.x;aux_get_pixel.x<x_resolution;aux_get_pixel.x++){
			print_string("entro for");
			pixel_address = get_video_start() + 3*(aux_get_pixel.x + aux_get_pixel.y*x_resolution);
			pixel_color.blue=*(pixel_address);
			pixel_color.green=*(pixel_address+1);
			pixel_color.red=*(pixel_address+2);
			paint_pixel(aux_move_pixel,pixel_color);

		}
		aux_move_pixel.x=0;
		aux_move_pixel.y+=16;
	}*/

}

void paint_background(){
	set();
	for(int i=0; i<x_resolution; i++){
		for(int j=0; j<y_resolution; j++){
			Position pos={i,j};
			paint_pixel(pos,background_color);
		}
	}
}

void print_character(char c){
	print_character_with_data(c,screen_position,font_color);
	screen_position.x+=CHAR_WIDTH;
}

void print_character_with_data(char c,Position pos,Color color){
	if(c==8){
		//delete();
	}
	else if(c==10){
		enter();
	}
	else{
		unsigned char * character=pixel_map(c);
		Position aux;
		for(aux.y=0;aux.y<CHAR_HEIGHT;aux.y++){
			for(aux.x=0;aux.x<CHAR_WIDTH;aux.x++){
				unsigned char character_aux=character[aux.y];
				character_aux >>= 8-aux.x;
				Position pos_aux={pos.x+aux.x,pos.y+aux.y};//le sumo el actual en y para no pisar lineas ya escritas
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
	enter();
}

void print_string(char* string){
	print_string_with_data(string,screen_position,font_color);
}

void swap(char* a,char* b){
	char aux=*a;
	*a=*b;
	*b=aux;
	return;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length-1 ;
    while (start < end)
    {
        swap((str+start), (str+end));
        start++;
        end--;
    }
}

char* int_to_string(int num, char* str,int base)
{
    int i = 0;
    int isNegative = 0;//no es negativo
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative==1)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

void print_number_with_data(int number,int base,Position pos,Color color){
	//paso number a char* y se lo paso a print_string
	char str[MAX_DIGITS];
	char* string_number=int_to_string(number,str,base);
	print_string_with_data(string_number,pos,color);
	return;
}

void print_integer(int number){
	print_number_with_data(number,10,screen_position,font_color);
}

int n_tu(int number, int count)
{
    int result = 1;
    while(count-- > 0)
        result *= number;

    return result;
}

/*** Convert float to string ***/
void float_to_string(float f, char r[])
{
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
	print_double_with_data(number,screen_position,font_color);
}