#include <keyboardDriver.h>
#include <videoDriver.h>

unsigned char regular_keyboard[128] =
        {
                0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
                '9', '0', '-', '=', '\b',	/* Backspace */
                '\t',			/* Tab */
                'q', 'w', 'e', 'r',	/* 19 */
                't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
                0,			/* 29   - Control */
                'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
                '\'', '`',   0,		/* Left shift */
                '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
                'm', ',', '.', '/',   0,				/* Right shift */
                '*',
                0,	/* Alt */
                ' ',	/* Space bar */
                0,	/* Caps lock */
                0,	/* 59 - F1 key ... > */
                0,   0,   0,   0,   0,   0,   0,   0,
                0,	/* < ... F10 */
                0,	/* 69 - Num lock*/
                0,	/* Scroll Lock */
                0,	/* Home key */
                0,	/* Up Arrow */
                0,	/* Page Up */
                '-',
                0,	/* Left Arrow */
                0,
                0,	/* Right Arrow */
                '+',
                0,	/* 79 - End key*/
                0,	/* Down Arrow */
                0,	/* Page Down */
                0,	/* Insert Key */
                0,	/* Delete Key */
                0,   0,   0,
                0,	/* F11 Key */
                0,	/* F12 Key */
                0,	/* All other keys are undefined */
        };

unsigned char shift_keyboard[128] =
        {
                0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
                '(', ')', '_', '+', 0,	/* Backspace */
                '\t',			/* Tab */
                'Q', 'W', 'E', 'R',	/* 19 */
                'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0,	/* Enter key */
                0,			/* 29   - Control */
                'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
                '\"', '`',   0,		/* Left shift */
                '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
                'M', '<', '>', '?',   0,				/* Right shift */
                '*',
                0,	/* Alt */
                ' ',	/* Space bar */
                0,	/* Caps lock */
                0,	/* 59 - F1 key ... > */
                0,   0,   0,   0,   0,   0,   0,   0,
                0,	/* < ... F10 */
                0,	/* 69 - Num lock*/
                0,	/* Scroll Lock */
                0,	/* Home key */
                0,	/* Up Arrow */
                0,	/* Page Up */
                '-',
                0,	/* Left Arrow */
                0,
                0,	/* Right Arrow */
                '+',
                0,	/* 79 - End key*/
                0,	/* Down Arrow */
                0,	/* Page Down */
                0,	/* Insert Key */
                0,	/* Delete Key */
                0,   0,   0,
                0,	/* F11 Key */
                0,	/* F12 Key */
                0,	/* All other keys are undefined */
        };

unsigned char capslock_keyboard[128] =
        {
                0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
                '9', '0', '-', '=', 0,	/* Backspace */
                '\t',			/* Tab */
                'Q', 'W', 'E', 'R',	/* 19 */
                'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', 0,	/* Enter key */
                0,			/* 29   - Control */
                'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',	/* 39 */
                '\'', '`',   0,		/* Left shift */
                '\\', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
                'M', ',', '.', '/',   0,				/* Right shift */
                '*',
                0,	/* Alt */
                ' ',	/* Space bar */
                0,	/* Caps lock */
                0,	/* 59 - F1 key ... > */
                0,   0,   0,   0,   0,   0,   0,   0,
                0,	/* < ... F10 */
                0,	/* 69 - Num lock*/
                0,	/* Scroll Lock */
                0,	/* Home key */
                0,	/* Up Arrow */
                0,	/* Page Up */
                '-',
                0,	/* Left Arrow */
                0,
                0,	/* Right Arrow */
                '+',
                0,	/* 79 - End key*/
                0,	/* Down Arrow */
                0,	/* Page Down */
                0,	/* Insert Key */
                0,	/* Delete Key */
                0,   0,   0,
                0,	/* F11 Key */
                0,	/* F12 Key */
                0,	/* All other keys are undefined */
        };

static char buffer[BUFFERSIZE];
static int w_index=0;
static int r_index=0;
static int ctrl_flag=0;
static int alt_flag=0;
static int capslock_flag=0;
static int shift_flag=0;
static int print_flag=0;
static int count=0;

void keyboard_handler(){
    unsigned char code = scan_key();

    if (code & 0x80) //bit 7 is set, a key was just released
    {
        if(code==182 || code==170){
            shift_flag=0;
        }
        if(code==157){
            ctrl_flag=0;
        }
        if(code==184){
            alt_flag=0;
        }
    }
    else
    {
        char character;
        if(code==42 || code==54){//shift
            shift_flag=1;
            print_flag=0;
        }
        if(code==58){//capslock
            capslock_flag=!capslock_flag;
        }
        if(code==29){//ctrl
            ctrl_flag=1;
            print_flag=0;
        }
        if(code==56){//alt
            alt_flag=1;
            print_flag=0;
        }

        if(shift_flag && !capslock_flag)
            character=shift_keyboard[code];
        else if(capslock_flag && !shift_flag)
            character=capslock_keyboard[code];
        else
            character=regular_keyboard[code];

        if(print_flag){
            put_character(character);
        }
        print_flag=1;
    }

}


void put_character(char character){
    buffer[w_index]=character;
    w_index=(w_index+1)%BUFFERSIZE;
    if(count==BUFFERSIZE){
        r_index=(r_index+1)%BUFFERSIZE;
    }
    else
        count++;
}

void get_character(char * character){
    if(count==0){
        *character=0;
        return;
    }
    *character=buffer[r_index];
    count--;
    r_index=(r_index+1)%BUFFERSIZE;
}