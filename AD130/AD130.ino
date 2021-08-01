#include "adc_setup.h"

#define VAR_RESISTOR 0
#define LDR 1

#define SW_RED 0xE
#define SW_YELLOW 0xD
#define SW_GREEN 0xB
#define SW_BLUE 0x7

unsigned int sensorValue, adcChannel;
char dataBuffer[16];
int state;

void setup() {
  PORTK |= 0x0F;
  DDRK &= ~(0x0F);

  state = 1;
  sensorValue = 0;
  adcChannel = VAR_RESISTOR;
  adcSetup(adcChannel);
  Serial.begin(38400);
  Serial.println("Program begins");
}

void loop() {
  switch (state) {
    case 1:
      if ((PINK & 0xF) == SW_RED) {
        state = 2;
      } else if ((PINK & 0xF) == SW_YELLOW) {
        state = 3;
      }
      break;
    case 2:
      adcChannel = VAR_RESISTOR;
      Serial.println("Reading ADC Channel 0");
      state = 4;
      break;
    case 3:
      adcChannel = LDR;
      Serial.println("Reading ADC Channel 1");
      state = 4;
      break;
    case 4:
      if (adcChangeChannel(adcChannel)) {
        adcStartConversion();
      }
      state = 5;
      break;
    case 5:
      if (adcConversionDone()) {
        state = 6;
      }
      break;
    case 6:
      sensorValue = adcReadData();
      sprintf(dataBuffer, "Data: %4d\n", sensorValue);
      Serial.print(dataBuffer);
      state = 4;
      delay(1000);
      if ((PINK & 0xF) == SW_RED) {
        state = 2;
      } else if ((PINK & 0xF) == SW_YELLOW) {
        state = 3;
      } else if ((PINK & 0xF) == SW_GREEN || (PINK & 0xFF) == SW_BLUE) {
        state = 1;
        Serial.println("Stop reading");
      }
      break;
  }
}
