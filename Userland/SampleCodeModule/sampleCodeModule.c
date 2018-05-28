#include <library.h>

int main() {
	char * string = "anda la syscall";
	sys_print_integer(string);
	sys_print_string(string);
	return 1;
}
