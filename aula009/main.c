/*
 */



#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"

#include "serial.h"

#define F_CPU 16000000UL



#define LED PD6

#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)



/*
float T,x;
uint16_t a; //(inteiro de 16 bits sem sinal, ver no mikroC se unsigned long tem 16bits)

a = adc_read();
x = (float)((float)a*5)/1023;

//Boa de -12,0 a 40,0 graus
if(x < 3.7)
	T = 1.6559*pow(x,3)-10.899*pow(x,2)+41.651*x-36.683;
else
	T = 10.214*pow(x,2) - 47.597*x + 88.389;


//T é o valor de temperatura, float.

//a função pow():
*/



int main(void)
{
    set_output(DDRD, LED);
    DDRC = 0;
    adc_init();

    ser_init();

    while (1) {
        ser_putc('H');
        ser_putc('A');
        ser_putc('!');
        int speed = adc_read(0);

        output_high(PORTD, LED);
        _delay_ms(speed/2);
        output_low(PORTD, LED);
        _delay_ms(speed/2);
        /*
        if (adc_read(0) > 512)
            output_high(PORTD, LED);
        else
            output_low(PORTD, LED);
        */
    }

    return 0;
}
