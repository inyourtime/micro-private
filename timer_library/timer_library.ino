#include <PinChangeInterrupt.h>

#include "Timer1.h"

#define DEBUG 0

#if DEBUG == 1
#define debug(x)   Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

Timer1 timer1(CTC);

void setup() {
  Serial.begin(38400);
  DDRB = 0xF0;
  PORTB = 0xF0;
  DDRA = 0xFF;
  PORTA = 0xFF;
  DDRK = 0;
  PORTK = 0xFF;

  cli();
  attachInterrupt(digitalPinToInterrupt(3), startBlink, FALLING);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(A8), stopBlink, FALLING);
  timer1.initialize(1024);
  OCR1A = 15624;
  TIMSK1 |= 1<<OCIE1A;
  timer1.start();
  sei();
  
  Serial.println("Program begin");
}

void loop() {
  if ((PINK & 0x2) == 0) {
    timer1.restart();
  }
}

void stopBlink() {
  debugln("this is PCINT");
  PORTA = 0xFF;
  timer1.stop();
}

void startBlink() {
  debugln("this is INT");
  timer1.restart();
}

ISR (TIMER1_COMPA_vect)
{
  debugln("this is timer int");
  PORTA ^= 0xFF;
}
