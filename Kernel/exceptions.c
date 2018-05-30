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
	print_string("Exception: division by zero");
	printRegisters(rsp);
}

void opcode(uint64_t * rsp) {
	print_string("Exception: invalid opcode");
	printRegisters(rsp);
}

void printRegisters(uint64_t * rsp) {
	for (int i = 0; i < REGISTERS; i++) {
		print_string(registers[i]);
		//print hexa
	}
}