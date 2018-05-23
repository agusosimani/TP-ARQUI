#include "font.h"
#include "videoDriver.h"

static unsigned char ** start_video_position = (unsigned char**)0x0005C28;
static unsigned char * x_resolution = (unsigned char*)0x0005084;

unsigned  char* get_x_resolution(){
	return x_resolution;
}


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

void enter(){
	//if(screen_position.y==SCREEN_HEIGHT) no more SCREEN
	//subi la pantalla
	//sino
	screen_position.y+=CHAR_HEIGHT;
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
		enter();
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

void print_integer(int number,int base,Position pos,Color color){
	//paso number a char* y se lo paso a print_string
	char str[MAX_DIGITS];
	char* string_number=int_to_string(number,str,base);
	print_string(string_number,pos,color);
	return;
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


void print_double(float number,Position pos,Color color){
	char str[MAX_DIGITS];
	float_to_string(number,str);
	print_string(str,pos,color);
}
