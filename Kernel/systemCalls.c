#include <videoDriver.h>
#include <time.h>
#include <systemCalls.h>

void systemCallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx) {
    print_string("entre");
    print_integer(rdi);
    print_integer((int)rsi);
    switch (rdi) {
        case 0:
            //print_string((char*)rsi);
            break;
        case 1:
            print_integer((int)rsi);
            break;
        case 2:
            break;
    }
}