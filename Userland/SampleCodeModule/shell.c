#include <shell.h>
#include <library.h>

typedef struct Command {
    char name[MAX_NAME];
    char description[MAX_DESCRIPTION];
    void (*function)(void);
    int num_params;
} Command;

int colors[8][3] = {{0,0,0},{66,134,244},{244,66,244},{66,244,92},{170,66,244},{244,75,66},{235,244,66},{78,66,244}};

int BR;
int BG;
int BB;
int FR;
int FB;
int FG;
static int running;
static Command commands[COMMANDS] = {
        {"help","Displays help instructions",help,1},
        {"test","Tests exceptions. Options: opcode, zero",test_opcode,2},
        {"time","Displays time",display_time,1},
        {"clear","Clears screen",clear,1},
        {"backColor","Changes background color. Options: red, blue, green",back_color,2},
        {"fontColor","Changes font color. Options: red, blue, green",font_color,2},
        {"exit","Terminates shell",exit,1}
};

void shell() {

    set_font_color(0,0,0);
    printf("Shell initialized\nValid commands:");
    help();
    put_char('\n');

    running = 1;
    while (running) {
        static char buffer[MAX_SIZE];
        // set_font_color(0,0,0);
        printf(" $> ");
        get_command(buffer);
        put_char('\n');
        process_command(buffer);
        put_char('\n');
    }
}

void get_command(char* buffer) {
    char c = 0;
    int i = 0;

    int enter = 1;
    while (enter) {
        get_char(&c);
        if (c != -1) {
            if (c == '\n') {
                enter = 0;
            } else if (c == '\b') {
                if (i > 0) {
                    i--;
                    put_char(c);
                }
            } else if (i < MAX_SIZE-1) {
                buffer[i++] = c;
                put_char(c);
            }
        }
    }
    buffer[i] = 0;
}

void process_command(char* buffer) {
    int wordLength = 0;
    int words = 0;
    char input[MAX_WORDS][MAX_WORD_LENGTH] = {{0}};
    char *aux = buffer;

    while (*aux != '\0' && wordLength < MAX_WORD_LENGTH) {
        if (*aux == ' ' || *aux == '\n') {
            input[words][wordLength] = '\0';
            wordLength = 0;
            words++;
        } else {
            input[words][wordLength] = *aux;
            wordLength++;
        }
        aux++;
    }

    for (int i = 0; i < COMMANDS; i++) {
        if (words == commands[i].num_params-1) {//el -1 es porque words (al guardarse en matriz)arranca en 0
            if (strcmp(commands[i].name, input[0]) == 0) {
                if (words == 1) {//en realidad tiene 2 words,pero el primero es 0
                    if (strcmp(input[0], "backColor") == 0) {
                        if (strcmp(input[1], "red") == 0) {
                            BR=255;
                            BB=0;
                            BG=0;
                        } else if (strcmp(input[1], "green") == 0) {
                            BR=0;
                            BB=0;
                            BG=255;
                        } else if (strcmp(input[1], "blue") == 0) {
                            BR=0;
                            BB=255;
                            BG=0;
                        } else {
                            set_font_color(244,21,21);
                            printf("\nWrong parameters for backColor\n");
                            font_color();
                            return ;
                        }
                    }
                    else if(strcmp(input[0],"fontColor")==0){
                        if (strcmp(input[1], "red") == 0) {
                            FR=200;
                            FG=0;
                            FB=0;

                        } else if (strcmp(input[1], "green") == 0) {
                            FR=0;
                            FG=200;
                            FB=0;

                        } else if (strcmp(input[1], "blue") == 0) {
                            FR=0;
                            FG=0;
                            FB=200;
                        } else {
                            set_font_color(244,21,21);
                            printf("\nWrong parameters for fontColor\n");
                            font_color();
                            return ;
                        }
                    }else if(strcmp(input[0],"test")==0){
                        if (strcmp(input[1], "opcode") == 0) {
                            test_opcode();
                            return;
                        } else if (strcmp(input[1], "zero") == 0) {
                            test_zero();
                            return;
                        } else{
                            set_font_color(244,21,21);
                            printf("\nWrong parameters for test\n");
                            font_color();
                            return ;
                        }
                    }
                    else{
                        set_font_color(244,21,21);
                        printf("\nInvalid command or too many arguments. Insert help to see valid commands\n");
                        font_color();
                    }
                }
                commands[i].function();
                return;
            }

        }
    }
    set_font_color(244,21,21);
    printf("\nInvalid command or too many arguments. Insert help to see valid commands\n");
    font_color();
}


void help() {
    for (int i=0; i<COMMANDS; i++) {
        put_char('\n');
        printf("%s",commands[i].name);
        printf("   -   %s",commands[i].description);
    }
    put_char('\n');
}

void print_time(int color) {
	int hour,minutes,seconds;
	get_hour(&hour);
	get_minutes(&minutes);
	get_seconds(&seconds);

	int x_position = 0;

	int r = colors[color][0];
	int g = colors[color][1];
	int b = colors[color][2];

	int left, right;

	//print hour
	right = hour%10;
	left = hour/10;
	put_digit(left,r,g,b,&x_position);
	put_digit(right,r,g,b,&x_position);
	put_digit(10,r,g,b,&x_position); //colon

	//print minutes
	right = minutes%10;
	left = minutes/10;

	put_digit(left,r,g,b,&x_position);
	put_digit(right,r,g,b,&x_position);
	put_digit(10,r,g,b,&x_position); //colon

	//print seconds
	right = seconds%10;
	left = seconds/10;

	put_digit(left,r,g,b,&x_position);
	put_digit(right,r,g,b,&x_position);
}

void display_time() {

    clear();
    printf("\nPress 'c' to change color of the digital clock");
    printf("\nPress 'q' to quit\n");

    int display = 1;
    int color = 0;

    while(display) {
        print_time(color%8);

        char c;
        get_char(&c);

        if (c == 'c') {
            color++;
            beepOn();
            int i=0;
            while( i!=10000000){
              i++;
            }
            beepOff();

        } else if (c == 'q') {
            display = 0;
        }
    }
    clear();
}

void exit() {
    running = 0;
    clear();
    printf(" See you soon");
}

void test_opcode() {
    set_font_color(244,21,21);
    opcode();
    font_color();
}

void test_zero() {
    set_font_color(244,21,21);
    zero();
    font_color();
}


void back_color(){
    set_back_color(BR,BG,BB);

}

void font_color(){
    set_font_color(FR,FG,FB);
}