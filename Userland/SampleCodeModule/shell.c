#include <shell.h>
#include <library.h>

static int running;
static char buffer[MAX_SIZE];

void shell() {


    //printf("\n");
    running = 1;
    while (running) {
        put_char('>');
        put_char(' ');
        get_command();
        process_command();
    }
}

void get_command() {
    char c;
    int i = 0;

    int enter = 1;
    while (enter) {
        get_char(&c);
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
    buffer[i] = 0;
}

void process_command() {

    if (buffer[0] == 0) {
        put_char('\n');
    } else if (strcmp(buffer,"help") == 0) {
        help();
    } else if (starts_with(buffer,"test") == 0) {
        if (strcmp(buffer+5,"opcode") == 0) {
            test(6);
        } else if (strcmp(buffer+5,"zero")) {
            test(0);
        } else {
            sys_print_string("Invalid parameter for test. Try test opcode or test zero");
        }
    } else if (strcmp(buffer,"clear") == 0) {
        sys_clear();
    } else if (strcmp(buffer,"time") == 0) {
        display_time();
    } else {
        sys_print_string("Invalid command, insert help to see valid commands");
    }
}

void help() {
    sys_print_string("help                - Displays help instructions");
    sys_print_string("test [command]      - Test exceptions. Command can be 'opcode' or 'zero'");
    sys_print_string("clear               - Clears screen");
    sys_print_string("time                - Displays time");
}

void display_time() {

    sys_clear();
    sys_print_string("Press 'c' to change color of the digital clock");
    sys_print_string("Press 'q' to quit");

    int display = 1;
    int color = 0;

    while(display) {
        sys_display_time(color);

        char* c = 0;
        get_char(c);

        if (*c == 'c') {
            color++;
            //beep();

        } else if (*c == 'q') {
            display = 0;
        }
    }
    sys_clear();
}

void test(int id) {
    switch(id) {
        case ZERO_EXCEPTION_ID:
            zero();
            break;
        case INVALID_OPCODE_EXCEPTION_ID:
            opcode();
            break;
    }
}
