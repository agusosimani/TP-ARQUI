#include <shell.h>
#include <library.h>

typedef struct Command {
    char name[MAX_NAME];
    char description[MAX_DESCRIPTION];
    void (*function)(void);
} Command;

int colors[8][3] = {{0,0,0},{66,134,244},{244,66,244},{66,244,92},{170,66,244},{244,75,66},{235,244,66},{78,66,244}};
static int running;
static Command commands[COMMANDS] = {
        {"help","Displays help instructions",help},
        {"test opcode","Test invalid opcode exception",test_opcode},
        {"test zero","Test division by zero exception",test_zero},
        {"time","Displays time",display_time},
        {"clear","Clears screen",clear},
        {"exit","Terminates shell",exit}
};

void shell() {

    set_font_color(0,0,0);
    printf("Shell initialized\nValid commands:");
    help();
    put_char('\n');

    running = 1;
    while (running) {
        static char buffer[MAX_SIZE];
        set_font_color(0,0,0);
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
    for (int i=0; i<COMMANDS; i++) {
        if (strcmp(commands[i].name,buffer) == 0) {
            set_font_color(27,107,124);
            commands[i].function();
            return;
        }
    }
    set_font_color(244,21,21);
    printf("\nInvalid command. Insert help to see valid commands\n");
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
}

void test_zero() {
    set_font_color(244,21,21);
    zero();
}
