#include <shell.h>
#include <library.h>

void shell() {
    sys_print_string("Write a command");
    sys_print_char('>');
    sys_print_char(' ');

    //if el comando es time..
    //display_time();

    //if el comando es test
    //chequeo argumento
    //test(0);
}

void display_time() {

    sys_clear();
    sys_print_string("Press 'c' to change color of the digital clock");
    sys_print_char(' ');
    sys_print_char(' ');
    sys_print_string("Press 'q' to quit");

    int running = 1;
    int color = 0;

    while(running) {
        // detectar si toca la tecla c o q y cambair de color o poner running en 0
        sys_display_time(color);
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