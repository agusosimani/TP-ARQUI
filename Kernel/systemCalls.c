#include <videoDriver.h>
#include <keyboardDriver.h>
#include <time.h>
#include <systemCalls.h>

void systemCallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx) {
    switch (rdi) {
        case 0:
            print_string((char*)rsi);
            break;
        case 1:
            print_integer(rsi);
            break;
        case 2:
            print_character((char)rsi);
            break;
        case 3:
            display_time(rsi);
            break;
        case 4:
            paint_background();
            break;
        case 5:
            get_character((char*)rsi);
            break;
    }
}
