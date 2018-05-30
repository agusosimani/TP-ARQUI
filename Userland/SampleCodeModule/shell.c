#include <shell.h>
#include <library.h>

static int running;
static char buffer[MAX_SIZE];

void shell() {

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

    //if el comando es time..
    //display_time();

    //if el comando es test
    //chequeo argumento
    //test(0);
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
