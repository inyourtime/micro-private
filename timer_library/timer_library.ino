#include "Timer1.h"

Timer1 timer1(CTC);

void setup() {
  Serial.begin(38400);
  DDRB = 0xF0;
  PORTB = 0xF0;
  DDRA = 0xFF;
  PORTA = 0xFF;

  cli();
  timer1.initialize(1024);
  OCR1A = 15624;
  TIMSK1 |= 1<<OCIE1A;
  timer1.start();
  sei();
  
  Serial.println("Program begin");
}

void loop() {
  if ((PINK & 0x1) == 0) {
    PORTA = 0xFF;
    timer1.stop();
  } else if ((PINK & 0x2) == 0) {
    timer1.restart();
  }
}

ISR (TIMER1_COMPA_vect)
{
  PORTA ^= 0xFF;
}
