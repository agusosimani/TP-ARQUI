#include <videoDriver.h>
#include <keyboardDriver.h>
#include <time.h>
#include <systemCalls.h>

void systemCallDispatcher(uint64_t id, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4, uint64_t param5) {
    switch (id) {
        case 0:
            get_character((char*)param1);
            break;
        case 1:
            print_character((char)param1);
            break;
        case 2:
            paint_background();
            break;
        case 3:
            hour((int*)param1);
            break;
        case 4:
            minutes((int*)param1);
            break;
        case 5:
            seconds((int*)param1);
            break;
        case 6:
            beep();
            break;
        case 7:
            print_digit(param1,param2,param3,param4,(int*)param5);
            break;
        case 8:
            set_font_color(param1,param2,param3);
            break;
    }
}

void hour(int * h) {
    *h = get_hour();
}

void minutes(int * m) {
    *m = get_minutes();
}

void seconds(int * s) {
    *s = get_seconds();
}

void x_res(int * x) {
    *x = getX();
}

void y_res(int * y) {
    *y = getY();
}
