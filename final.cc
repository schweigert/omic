// Jonathan de Oliveira Cardoso
// Marlon Henry Schweigert
// Mateus Seenem Tavares

// Dino Game for Arduino <3

// Módulo de Som
int pin_sound_input = A0;


long getSoundLevel()
{
  long sound_avr;

    sound_avr = 0;
    for(int i = 0; i < 128; i++){
      sound_avr += analogRead(pin_sound_input); 
    }
    sound_avr /= 128;
    Serial.print(sound_avr);
    Serial.print("\n");
}


void setup() {
  // Módulo de Som
  pinMode(pin_sound_input, INPUT); //Define o pino de sinal como Entrada  
  Serial.begin(9600);  
}

void loop() {
   Serial.print(getSoundLevel());
}


