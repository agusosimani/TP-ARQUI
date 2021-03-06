#include <exceptions.h>
#include <videoDriver.h>

void exceptionDispatcher(int exception, uint64_t * rsp) {
	if (exception == ZERO_EXCEPTION_ID) {
		zero_division(rsp);
	} else if (exception == INVALID_OPCODE_EXCEPTION_ID) {
		opcode(rsp);
	}
}

void zero_division(uint64_t * rsp) {
	move_line();
	print_string("Exception: division by zero");
	move_line();
	printRegisters(rsp);
}

void opcode(uint64_t * rsp) {
    move_line();
	print_string("Exception: invalid opcode");
	move_line();
	printRegisters(rsp);
	move_line();
}

void printRegisters(uint64_t * rsp) {
	print_string("RSP: ");
	print_hexa(rsp);
	move_line();
	for (int i = 0; i < REGISTERS; i++) {
		print_string(registers[i]);
		print_string(" ");
		print_hexa(rsp[i]);
		move_line();
	}
}
