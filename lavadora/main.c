/*
 */

#define LED_H PIN_D6_H
#define LED_L PIN_D6_L

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"
#include "mypins.h"


FILE mystdout = FDEV_SETUP_STREAM(USART_putchar, USART_getchar, _FDEV_SETUP_RW);

int main(void)
{



    /*
    char i;

    DDRB = 0b11111111;
    DDRC = 0b11111111;
    DDRD = 0b11111110;
    ///             ^--- RX como entrada

    USART_init(9600);
    stdout = stdin = &mystdout;

    i=240;

    while (1) {
        // turn on the LED for 200ms
        LED_H;
        printf("Good <=]\r\n");
        _delay_ms(200);
        // now turn off the LED for another 200ms
        LED_L;
        printf("Bad >=| and counting: %d\r\n",i);
        _delay_ms(200);
        // now start over
        i++;
    }


    */


    DDRB = 0b11111111;
    DDRC = 0b11111111;
    DDRD = 0b11111010;

    USART_init(9600);
    stdout = stdin = &mystdout;

    int status = 0, newstatus = 0;
    int count = 0;
    while(1){

        newstatus = PIN_D2_R;
        if(status != newstatus){
            count++;
            status = newstatus;
            count %= 3;
        }

        switch(count){
        case 0:
            PIN_D5_H;
            PIN_D6_L;
            PIN_D7_L;
            break;
        case 1:
            PIN_D5_L;
            PIN_D6_H;
            PIN_D7_L;
            break;
        case 2:
            PIN_D5_L;
            PIN_D6_L;
            PIN_D7_H;
            break;
        default:
            count = 0;
        }

    }

    return 0;
}

