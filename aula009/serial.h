#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void ser_init();
void ser_putc(char c);
void ser_wstr(char* str);
char ser_getc();
char ser_kbhit();

#endif // SERIAL_H_INCLUDED
