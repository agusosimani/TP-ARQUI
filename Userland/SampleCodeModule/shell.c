#include <shell.h>
#include <library.h>

typedef struct Command {
    char name[MAX_NAME];
    char description[MAX_DESCRIPTION];
    void (*function)(void);
} Command;

static int x_resolution;
static int y_resolution;
int colors[8][3] = {{0,0,0},{66,134,244},{244,66,244},{66,244,92},{170,66,244},{244,75,66},{235,244,66},{78,66,244}};
static int running;
static Command commands[COMMANDS] = {
        {"help","Displays help instructions",help},
        {"test opcode","Test invalid opcode exception",opcode},
        {"test zero","Test division by zero exception",zero},
        {"time","Displays time",display_time},
        {"clear","Clears screen",clear},
        {"exit","Terminates shell",exit}
};

void shell() {
    
    get_x_res(&x_resolution);
    get_y_res(&y_resolution);

//    int a = 4;
//    int b = 5;
//    put_digit(2,1,2,3,&a,&b);

    running = 1;
    while (running) {
        static char buffer[MAX_SIZE];
        printf("  > ");
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
            commands[i].function();
            return;
        }
    }
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

	int x_display = x_resolution/2 - 309;
	int y_display = y_resolution/2 -21;
	
	int r = colors[color][0];
	int g = colors[color][1];
	int b = colors[color][2];

	int left, right;

	//print hour
	right = hour%10;
	left = hour/10;
	put_digit(left,r,g,b,&x_display,&y_display);
	put_digit(right,r,g,b,&x_display,&y_display);
	put_digit(10,r,g,b,&x_display,&y_display); //colon

	//print minutes
	right = minutes%10;
	left = minutes/10;

	put_digit(left,r,g,b,&x_display,&y_display);
	put_digit(right,r,g,b,&x_display,&y_display);
	put_digit(10,r,g,b,&x_display,&y_display); //colon

	//print seconds
	right = seconds%10;
	left = seconds/10;

	put_digit(left,r,g,b,&x_display,&y_display);
	put_digit(right,r,g,b,&x_display,&y_display);
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
            //beep();

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
