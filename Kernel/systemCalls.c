#include <videoDriver.h>
#include <time.h>
#include <systemCalls.h>

void systemCallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx) {
    //ESTAN PUESTAS COMO EJEMPLO.. HAY QUE AGREGAR LAS QUE VAMOS A USAR POSTA
    switch (rdi) {
        case 0:
            print_string((char*)rsi);
            break;
        case 1:
            print_integer(rsi);
            break;
        case 2:
            break;
    }
}
