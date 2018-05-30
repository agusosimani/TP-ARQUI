#include <library.h>
#include <stdint.h>

void sys_print_string(char* string) {
    systemCall(0,(uint64_t)string,0,0);
}

void sys_print_integer(int num) {
    systemCall(1,num,0,0);
}

void put_char(char c) {
    systemCall(2,(uint64_t)c,0,0);
}

void sys_display_time(int color) {
    systemCall(3,color,0,0);
}

void sys_clear() {
    systemCall(4,0,0,0);
}

void get_char(char* c) {
    systemCall(5,(uint64_t)c,0,0);
}

void beep() {
  systemCall(6,0,0,0);
}

//Compares 2 strings. Returns 0 if they are equal
int strcmp(char * s1, char * s2){
    while(*s1 && *s2 && *s1 == *s2){
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int strncmp(char * s, char * t, unsigned int n) {
    int i;
    for (i = 0; i < n-1 && s[i] != '\0' && t[i] != '\0' && s[i] == t[i]; i++)
        ;
    return s[i]-t[i];
}

//Returns true(!= 0) if start is an initial substring of str and 0 if not
int starts_with(char * str, char * start){
    while(*str != 0 && *start != 0){
        if(*(str++) != *(start++)){
            return 0;
        }
    }
    return *start == 0;
}

static char *convert(unsigned int num, int base){
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50];
    char *ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = Representation[num%base];
        num /= base;
    }while(num != 0);

    return(ptr);
}

void vprintf(char *fmt, va_list arg){

	char *traverse;
    int i;
    char *s;


    for(traverse = fmt; *traverse != '\0'; traverse++)
    {
        while( *traverse != '%' && *traverse != '\0')
        {
            put_char(*traverse);
            traverse++;
        }

        if(*traverse == 0)
        	break;

        traverse++;

        //Module 2: Fetching and executing arguments
        switch(*traverse)
        {
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        put_char(i);
                        break;

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i<0)
                        {
                            i = -i;
                            put_char('-');
                        }
                        sys_print_string(convert(i,10));
                        break;

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        sys_print_string(convert(i,8));
                        break;

            case 's': s = va_arg(arg,char *);       //Fetch string
                        sys_print_string(s);
                        break;

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        sys_print_string(convert(i,16));
                        break;
        }
    }
}

void printf(char* fmt, ...)
{
	  va_list arg;
    va_start(arg, fmt);

    vprintf(fmt, arg);

    //Cerrando la lista variable
    va_end(arg);

}
