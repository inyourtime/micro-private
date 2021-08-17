#include <avr/io.h>
#include "timer1_setup.h"

void timer1SetupCTC() {
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 3124; // 20 Hz
//  OCR1B = 6249;  // 10 Hz
//  OCR1C = 3124; // 20 Hz
  TCNT1 = 0x0;
  TIFR1 = 0x2F;
  TIMSK1 = 0;
  TCCR1B |= 0x08;
//  TCCR1B |= 0x04; // 256
}

void timer1Start() {
  TCCR1B |= 0x04;
}

void timer1Stop() {
  TCCR1B &= ~(0x07);
  TCNT1 = 0x0;
  TIFR1 = 0x2;
}

void timer1SetupCTC2() {
  TCCR1A = 0; // clear all bits
  TCCR1B = 0; // clear all bits
  OCR1A = 31249; // target interrupt every 2 seconds
  OCR1B = 15624; // interrupt at 1 second from start
  OCR1C = 7812;  // interrupt at 0.5 second from start
  TCNT1 = 0x0; // reset counter
  TIFR1 = 0x2F; // clear all interrupt flags
  TIMSK1 = 0; // disable all interrupts call to MCU
  TCCR1B |= 0x08; // set WGM12 to CTC mode
  TCCR1B |= 0x05; // set CS12 and CS10 to divide clk by 1024
}

void timer3SetupCTC() {
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3 = 0x0;
  TIFR3 = 0x2F;
  TIMSK3 = 0;
  TCCR3B |= 0x80; // CTC mode
  TCCR3B &= ~(0x07); // timer stop
}

void myDelay500() { // delay 500 ms
  OCR3A = 31249;  // 2 Hz
  TCCR3B |= 0x04; // timer start and divide clk by 256
  while (!(TIFR3 & 0x2)) {};  // waiting 1000 ms
  TCCR3B &= ~(0x07);  // timer stop
  TCNT3 = 0x0;  // reset counter
  TIFR3 = 0x2;  // clear interrupt flag
}

void myDelay100() {  // delay 100 ms
  OCR3A = 6249; // 10 Hz
  TCCR3B |= 0x04; // timer start and divide clk by 256
  while (!(TIFR3 & 0x2)) {};  // waiting 100 ms
  TCCR3B &= ~(0x07);  // timer stop
  TCNT3 = 0x0;  // reset counter
  TIFR3 = 0x2;  // clear interrupt flag
}
