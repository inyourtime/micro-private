#include "timer1_setup.h"

#define STATE_IDLE 0
#define STATE_LED 1
#define STATE_RGB 2
#define STATE_ADC 3

#define RGB_ALL_OFF 0x07
#define RGB_ALL_ON ~(0x07)
#define LED_ALL_OFF 0xFF

#define SW_RED 0xE
#define SW_YELLOW 0xD
#define SW_GREEN 0xB

unsigned int counter;
unsigned int state;
unsigned int sensorValue;
char dataBuffer[30];

void adcSetup() {
  ADCSRA = 0x97;
  DIDR0 = 0x1;
  ADMUX = 0x40; // ADC channel 0
}

void setup() {
  Serial.begin(38400);
  DDRA = 0xFF;  // 8 led
  PORTA = LED_ALL_OFF;
  DDRC = 0x07;  // traffic light
  PORTC = RGB_ALL_OFF;
  PORTK = 0xFF;
  DDRK = 0; // switch

  timer1SetupCTC();
  timer3SetupCTC();
  adcSetup();

  counter = 0;
  state = STATE_IDLE;
  sensorValue = 0;
  Serial.println("Program begins");
}

void loop() {
  switch (state) {
    case STATE_IDLE:
      if ((PINK & 0xF) == SW_RED) {  
        state = STATE_LED;
        Serial.println("STATE: LED");
      } else if ((PINK & 0xF) == SW_YELLOW) { 
        state = STATE_RGB;
        Serial.println("STATE: RGB");
      } else if ((PINK & 0xF) == SW_GREEN) { 
        state = STATE_ADC;
        Serial.println("STATE: LDR");
        timer1Start();
      }
    break;
    case STATE_LED:
      _8LedPattern();
      counter++;
      if (counter == 5) {
        counter = 0;
        state = STATE_IDLE;
        PORTA = LED_ALL_OFF;
        Serial.println("STATE: IDLE");
      }
    break;
    case STATE_RGB:
      RGBPattern();
      counter++;
      if (counter == 5) {
        counter = 0;
        state = STATE_IDLE;
        PORTC = RGB_ALL_OFF;
        Serial.println("STATE: IDLE");
      }
    break;
    case STATE_ADC:
      if (TIFR1 & 0x2) {
        TIFR1 = 0x2;  // clear interrupt flag
        ADCSRA |= 0x40; // start conversion
        counter++;
      }
      if (ADCSRA & 0x10) {  // conversion done
//        Serial.println(ADC);
        sensorValue = sensorValue + ADC;
        ADCSRA |= 0x10; // clear flag
        if (counter == 4) {
          counter = 0;
          state = STATE_IDLE;
          sprintf(dataBuffer, "LDR average: %4d\n", sensorValue / 4);
          Serial.print(dataBuffer);
          sensorValue = 0;
          Serial.println("STATE: IDLE");
          timer1Stop(); 
        }
      }
    break;
  }
}

void _8LedPattern() {
  // your pattern
}

void RGBPattern() {
  // your pattern
}
