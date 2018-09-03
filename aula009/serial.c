#include "serial.h"
#include <avr/io.h>
// UART



void ser_init()
{

    unsigned int ubrr = MYUBRR;

    /*Configura o baud rate */
     UBRR0H = (unsigned char)(ubrr>>8);
     UBRR0L = (unsigned char)ubrr;
    /* Ativa o Recebedor e o Tranferidor */
     UCSR0B = (1<<RXEN0)|(1<<TXEN0);
     /* Configura com o padrão: 8bit, 1stop bit */
     UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}

void ser_putc(char c)
{
/* Espera por uma linha limpa para transmitir */
 while ( !( UCSR0A & (1<<UDRE0)) )
 ;
 /* Insere no buffer */
 UDR0 = c;

}
