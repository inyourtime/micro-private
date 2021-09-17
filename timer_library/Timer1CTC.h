/*
 * Timer1 with CTC mode 4 (TOP is OCR1A)
 */

#ifndef Timer1CTC_H
#define Timer1CTC_H

#include "Arduino.h"
#include <avr/io.h>

#define TIMER1_RESOLUTION 65535UL

class Timer1CTC {
  public:
    /******************************
     * Configuration *
     *****************************/
    Timer1CTC() {}
    void initialize(unsigned long milliseconds = 1000) { // Setup timer mode and period
      TCCR1A = 0;
      TCCR1B = 0;
      TCCR1B |= 0x08;
      setPeriod(milliseconds);
    }
    void setPeriod(unsigned long milliseconds = 1000) { // Setup period
      const unsigned long cycles = F_CPU/1000 * milliseconds;
      if (cycles < TIMER1_RESOLUTION) {
        clockSelectBits = 0x01;
        period = cycles - 1;
      } else if (cycles < TIMER1_RESOLUTION * 8) {
        clockSelectBits = 0x02;
        period = (cycles / 8) - 1;
      } else if (cycles < TIMER1_RESOLUTION * 64) {
        clockSelectBits = 0x03;
        period = (cycles / 64) - 1;
      } else if (cycles < TIMER1_RESOLUTION * 256) {
        clockSelectBits = 0x04;
        period = (cycles / 256) - 1;
      } else if (cycles < TIMER1_RESOLUTION * 1024) {
        clockSelectBits = 0x05;
        period = (cycles / 1024) - 1;
      } else {
        clockSelectBits = 0x05;
        period = TIMER1_RESOLUTION - 1;
      }
      OCR1A = period;
    }
    
    /******************************
     * Run Control *
     *****************************/
    void start() {
      TCNT1 = 0;
      resume();
    }
    void stop() {
      TCCR1B &= ~(0x07);
    }
    void restart() {
      start();
    }
    void resume() {
      TCCR1B |= clockSelectBits;
    }

    /******************************
     * Interrupt Function *
     *****************************/
    void attachInterrupt(void (*isr)()) {
      isrCallback = isr;
      TIMSK1 |= 1<<OCIE1A;
    }
    void detachInterrupt() {
      TIMSK1 = 0;
    }
    static void (*isrCallback)();
    static void isrDefaultUnused();
  
  private:
    uint16_t period;
    uint8_t clockSelectBits;
};

//extern Timer1 timer1;

#endif
