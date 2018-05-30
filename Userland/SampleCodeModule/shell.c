#include <shell.h>
#include <library.h>

void shell() {
    sys_print_string("Write a command");
    put_char('>');
    put_char(' ');

    //if el comando es time..
    display_time();

    //if el comando es test
    //chequeo argumento
    //test(0);
}

void display_time() {

    sys_clear();
    sys_print_string("Press 'c' to change color of the digital clock");
    put_char(' ');
    put_char(' ');
    sys_print_string("Press 'q' to quit");

    int running = 1;
    int color = 0;

    while(running) {
        sys_display_time(color);

        char* c;
        get_char(c);

        if (*c == 'c') {
            color++;

        } else if (*c == 'q') {
            running = 0;
        }
    }
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