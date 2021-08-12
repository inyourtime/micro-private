#include "adc_setup.h"

unsigned int sensorValue, adcChannel;
char dataBuffer[16];
int cmdInput;

void setup(void) {
  sensorValue = 0;
  DDRB = 0x80; // Port B7 as output
  PORTB &= ~(0x80); // clear Port B7
  adcChannel = 1;
  adcSetup(adcChannel); // setup ADC use AD1
  Serial.begin(38400); // start Serial port
  Serial.println("Program begins");
}

void loop() {
  if(Serial.available()){
    cmdInput = Serial.read();
    if(cmdInput >= '0' && cmdInput <= '9'){
      adcChannel = cmdInput - '0'; // convert to number
    }
    else if(cmdInput >= 'A' && cmdInput <= 'F'){
      adcChannel = cmdInput - 'A' + 10; // convert to number
    }
    else {
      adcChannel = 16; // force error
    }
    if(adcChangeChannel(adcChannel)){
      if((ADCSRA & 0x40) == 0){ // if has not start conversion
        ADCSRA |= 0x40; // set ADSC to start conversion
      }
      else{
        Serial.println("Err: ADC change channel");
      }
    }
  }

  if((ADCSRA & 0x10) != 0){ // finish conversion
    sensorValue = ADC; // read ADC result 
    ADCSRA |= 0x10; // clear flag
    sprintf(dataBuffer,"Data: %4d\n",sensorValue); // write data to buffer
    Serial.print(dataBuffer); // output to serial monitor
  }
}
