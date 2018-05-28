#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <idtLoader.h>
#include <videoDriver.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{

	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
		clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

int main()
{
        load_idt();
				paint_background();

        print_string("holasdfg");
        print_string("123");

		((EntryPoint)sampleCodeModuleAddress)();
		//print_string_with_data("hi",pos,font_color);

		/*print_character('m');
		print_character('a');
		enter();
		print_double(32.4);
		print_character('c');
		enter();
		print_character('a');
		print_string("123");
		print_string("mica");

		print_integer(-987);
		print_double(12.2345);
		print_integer(getX());

		print_integer(getY());*/

		//print_integer(x_resolution,10,pos,color);

	return 0;
}
