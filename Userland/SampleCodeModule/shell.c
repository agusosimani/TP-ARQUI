#include <shell.h>
#include <library.h>

void shell() {
    sys_print_string("Write a command");
    sys_print_char('>');
    sys_print_char(' ');

    //if el comando es time..
    display_time();

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