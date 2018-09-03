
/**
Ref: http://maxembedded.com/2011/06/the-adc-of-the-avr/
*/
#include <avr/io.h>
#include "adc.h"

void adc_init()
{
   // AREF = AVcc
    ADMUX = (1<<REFS0);

    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read( uint8_t ch )
{

  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing

  // start single convertion
  // writ
  ADCSRA |= (1<<ADSC);


  while(ADCSRA & (1<<ADSC));

  return (ADC);
}

