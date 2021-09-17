#include <PinChangeInterrupt.h>

#include "Timer1CTC.h"

#define DEBUG 0

#if DEBUG == 1
#define debug(x)   Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

#define TRAFFIC_OFF()    PORTB = 0xF0
#define TRAFFIC_GREEN()  PORTB = ~(0x10)
#define TRAFFIC_YELLOW() PORTB = ~(0x20)
#define TRAFFIC_RED()    PORTB = ~(0x40)
#define _7SEGMENTS_OFF() PORTC = 0xFF

#define STATE_IDLE        1
#define STATE_COUNT_GREEN 2
#define STATE_WAIT_YELLOW 3
#define STATE_COUNT_RED   4
#define STATE_RESET       5

Timer1CTC timer1;

uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
                      0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
                    };
                    
volatile uint8_t count;
volatile uint8_t state;
volatile bool timerFlag;
volatile bool resetFlag;

void setup() {
  Serial.begin(38400);
  DDRB = 0xF0;
  TRAFFIC_GREEN();
//  DDRA = 0xFF;
//  PORTA = 0xFF;
  DDRK = 0;
  PORTK = 0xFF;
  DDRC = 0xFF;
  count = 0;
  _7SEGMENTS_OFF();
  state = STATE_IDLE;
  timerFlag = false;
  resetFlag = false;

  cli();
  attachInterrupt(digitalPinToInterrupt(3), _reset, FALLING);
//  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(A8), countDown, FALLING);
  timer1.initialize(500);
  timer1.attachInterrupt(count1sec);
//  TIMSK1 |= 1<<OCIE1A;
//  timer1.start();
  sei();
  
  Serial.println("Program begin");
  Serial.println(OCR1A);
//  Serial.println(F_CPU);
}

void loop() {
  switch (state) {
    case STATE_IDLE:
      if ((PINK & 0x1) == 0) {
        state = STATE_COUNT_GREEN;
        count = 5;
        PORTC = digit[count];
        timer1.start();
      }
    break;
    case STATE_COUNT_GREEN:
      if (timerFlag) {
        timerFlag = false;
        PORTC = digit[count];
      }
      if (count == 0) {
        count = 3;
        delay(300);
        TRAFFIC_YELLOW();
        state = STATE_WAIT_YELLOW;
        timer1.restart();
      }
    break;
    case STATE_WAIT_YELLOW:
      if (timerFlag) {
        timerFlag = false;
      }
      if (count == 0) {
        count = 9;
        TRAFFIC_RED();
        PORTC = digit[count];
        state = STATE_COUNT_RED;
      }
    break;
    case STATE_COUNT_RED:
      if (timerFlag) {
        timerFlag = false;
        PORTC = digit[count];
      }
      if (count == 0) {
        delay(300);
        TRAFFIC_GREEN();
        _7SEGMENTS_OFF();
        state = STATE_IDLE;
        timer1.stop();
      }
    break;
    case STATE_RESET:
      if (resetFlag) {
        resetFlag = false;
        PORTB = 0xFF;
        _7SEGMENTS_OFF();
        delay(500);
        PORTC = 0x00;
        PORTB = 0x0F;
        delay(500);
        TRAFFIC_GREEN();
        _7SEGMENTS_OFF();
        state = STATE_IDLE;
      }
    break;
  }
}

void countUp() {
  count = (count + 1) % 10;
  PORTC = digit[count];
}

void _reset() {
  state = STATE_RESET;
  resetFlag = true;
  timer1.stop();
}

void count1sec() {
  timerFlag = true;
  count -= 1;
}

//ISR (TIMER1_COMPA_vect)
//{
//  timerFlag = true;
//  count -= 1;
//}
