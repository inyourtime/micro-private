#include <avr/io.h>
#include "adc_setup.h"

void adcSetup(unsigned int ch) {
  // enable ADC, clear ADC interrupt flag,
  // setup ADC clock to CLK/128 to 125kHz
  ADCSRA = 0x97 ; // 0b10010111; // set ADEN, ADIF, ADPS2, ADPS1, ADPS0
  ADCSRB = 0; //
  //set REFS0 and MUX0 to use VCC as VREF
  ADMUX =  0x40; //0b01000000;
  if (ch < 8) {
    ADMUX |= ch;
  }
  else {
    ADCSRB |= 0x8; // set
    ADMUX |= (ch & 0x7); // use only last 3 bits
  }
}

int adcChangeChannel(unsigned int ch) {
  int output = 1; // return output
  if (ch > 15) {
    output = 0;
  }
  else if (ch < 8) {
    ADMUX &= ~(0x1F); // clear bit MUX4:0
    ADCSRB &= (0x47); // clear bit MUX5
    ADMUX |= ch;
  }
  else {
    ADCSRB |= 0x8; // set
    ADMUX &= ~(0x1F); // clear bit MUX4:0
    ADMUX |= (ch & 0x7); // use only last 3 bits
  }
  return (output); // return success/fail status
}

void adcStartConversion(void) {
  while (ADCSRA & 0x40) {};
  ADCSRA |= 0x40; // set ADSC to start conversion
}

int adcConversionDone(void) {
  int output = 0;
  if (ADCSRA & 0x10) {
    output = 1;
  }
  return (output);
}

unsigned int adcReadData(void) {
  unsigned int data = 0;
  while ((ADCSRA & 0x10) == 0) {}; // wait for conversion done
  ADCSRA |= 0x10; // clear flag
  data = ADC; // read ADC result
  return (data);
}
