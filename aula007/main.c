/*
 */



#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"

#define F_CPU 16000000UL



#define LED PD6

#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)


int main(void)
{
    set_output(DDRD, LED);
    DDRC = 0;
    adc_init();

    while (1) {
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
