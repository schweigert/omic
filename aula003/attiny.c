// TinkerCad

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  DDRB = 0b00000011;
}


#define PORT0_H PORTB = 0b00000001
#define PORT0_D PORTB = 0b00000000


// Para ler:
// PINB

// the loop routine runs over and over again forever:
void loop() {

  PORT0_H;
  _delay_ms(1000);
  PORT0_D;
  _delay_ms(1000);
}
