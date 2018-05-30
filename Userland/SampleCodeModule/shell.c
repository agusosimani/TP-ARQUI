#include <shell.h>
#include <library.h>


typedef struct Command {
    char name[MAX_NAME];
    char description[MAX_DESCRIPTION];
    void (*function)(void);
} Command;

static int running;
static Command commands[COMMANDS] = {
        {"help","Displays help instructions",help},
        {"test opcode","Test invalid opcode exception",opcode},
        {"test zero","Test division by zero exception",zero},
        {"time","Displays time",display_time},
        {"clear","Clears screen",sys_clear}
};

void shell() {

    char* c;
    printf("las olas y el viernto %c\n",'M');
    running = 1;
    while (running) {
        static char buffer[MAX_SIZE];
        put_char('>');
        put_char(' ');
        get_command(buffer);
        process_command(buffer);
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
    printf("\nInvalid command. Insert help to see valid commands");
}

void help() {
    for (int i=0; i<COMMANDS; i++) {
        printf("\n%s - %s",commands[i].name,commands[i].description);
    }
}

void display_time(int param) {

    sys_clear();
    printf("Press 'c' to change color of the digital clock\n");
    printf("Press 'q' to quit\n");

    int display = 1;
    int color = 0;

    while(display) {
        sys_display_time(color);

        char c;
        get_char(&c);

        if (c == 'c') {
            color++;
            //beep();

        } else if (c == 'q') {
            display = 0;
        }
    }
    sys_clear();
}
