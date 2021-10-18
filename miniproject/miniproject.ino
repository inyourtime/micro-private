#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "Timer3CTC.h"

#define STATE_IDLE           0
#define STATE_ENTER_PASSWORD 1
#define STATE_THINGS_DETECT  2
#define STATE_PASSWORD_CHECK 3
#define STATE_CAL_PRICE      4

#define SEV_SEG_DASH         0x40
#define LED_RED_ON           0xFE
#define LED_YELLOW_ON        0xFD
#define LED_GREEN_ON         0xFB
#define LED_ALL_ON           0xF0
#define LED_ALL_OFF          0xFF

LiquidCrystal_I2C lcd(0x27,16,2);
Timer3CTC timer7seg;


uint8_t digit[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

uint8_t _1stDigit;
uint8_t _2ndDigit;
uint8_t _3rdDigit;
uint8_t state;
uint16_t num;
uint16_t light;
bool idle, detect;
uint8_t passwordDigit[3];
uint8_t roundThings, totalThings;
const uint16_t myPassword = 123;
char dataBuffer[16];

void _7segmentSetup() {
  DDRA = 0xFF;
  DDRL = 0x0F;
  PORTA = 0;
  PORTL = 0b11111110;
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Program begins..");
  lcd.setCursor(0,1);
  lcd.print("Welcome to Cash");
  _7segmentSetup();
  DDRB = 0x0F;
  PORTB |= 0x0F;
  DDRK = 0;
  noInterrupts();
  timer7seg.initialize(5);
  timer7seg.attachInterrupt(disp7seg);
  attachInterrupt(digitalPinToInterrupt(2), IR_detect, FALLING);
  interrupts();
  num = 123;
  light = 0;
  roundThings = 0;
  totalThings = 0;
  idle = true;
  detect = false;
  state = STATE_IDLE;
  timer7seg.start();  
}

void loop() {
  switch (state) {
    case STATE_IDLE:
      PORTB = LED_RED_ON;
      light = analogRead(A7);
      delay(10);
//      splitDigit(passwordCombine(passwordDigit));
      if (light >= 700) {
        state = STATE_ENTER_PASSWORD;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter password");
        PORTB = LED_YELLOW_ON;
      }
    break;
    case STATE_ENTER_PASSWORD:
      lcd.setCursor(0,1);
      for (int i = 0; i < 3; i++) {
        passwordDigit[i] = readKeypadSingleDigit();
        delay(10);
        lcd.print("*");
      }
      state = STATE_PASSWORD_CHECK;
    break;
    case STATE_PASSWORD_CHECK:
      lcd.clear();
      lcd.setCursor(0,0);
      if (passwordCombine(passwordDigit) == myPassword) {
        state = STATE_THINGS_DETECT;
        PORTB = LED_GREEN_ON;
        detect = true;
        lcd.print("Entered");
        idle = false;
      } else {
        state = STATE_ENTER_PASSWORD;
        idle = true;
        lcd.print("Wrong!!! again");
      }
    break;
    case STATE_THINGS_DETECT:
      if ((PINK & 0x1) == 0) {
        state = STATE_CAL_PRICE;
        detect = false;
        lcd.clear();
        lcd.setCursor(0,0);
        sprintf(dataBuffer, "Things: %3d", roundThings);
        Serial.println(dataBuffer);
        lcd.print(dataBuffer);
        splitDigit(totalThings);
        PORTB = LED_YELLOW_ON;
      }
    break;
    case STATE_CAL_PRICE:
      uint16_t thingsPrice[roundThings];
      uint8_t thingPriceDigit[3];
      for (int thing = 0; thing < roundThings; thing++) {
        for (int i = 0; i < 3; i++) {
          thingPriceDigit[i] = readKeypadSingleDigit();
          lcd.setCursor(i,1);
          lcd.print(thingPriceDigit[i]);
        }
        while (PINK & 0x2) {}
        thingsPrice[thing] = passwordCombine(thingPriceDigit);
        Serial.println(thingsPrice[thing]);
      }
      state = STATE_THINGS_DETECT;
      detect = true;
      PORTB = LED_GREEN_ON;
      roundThings = 0;
    break;
  }
}

void IR_detect() {
  if (detect) {
    roundThings++;
    totalThings++;
    splitDigit(roundThings);
  }
}

void splitDigit(int _num) {
  _1stDigit = _num / 100;
  _2ndDigit = (_num % 100) / 10;
  _3rdDigit = (_num % 100) % 10;
}

void disp7seg() {
  if (~PORTL & 0b0100) {
    PORTL = 0b11111110;
    if (idle) PORTA = SEV_SEG_DASH;
    else PORTA = digit[_1stDigit];
  } else if (~PORTL & 0b0001) {
    PORTL = 0b11111101;
    if (idle) PORTA = SEV_SEG_DASH;
    else PORTA = digit[_2ndDigit];
  } else if (~PORTL & 0b0010) {
    PORTL = 0b11111011;
    if (idle) PORTA = SEV_SEG_DASH;
    else PORTA = digit[_3rdDigit];
  }
}

uint16_t passwordCombine(uint8_t num[3]) {
  return (num[0] * 100) + (num[1] * 10) + num[2];
}

uint16_t readKeypadSingleDigit(void) {
  uint8_t keypad;
  uint8_t password;
  uint8_t count;
  bool doneFlag = false;
  uint8_t index, index2;
  count = 0;
  while (doneFlag == false) {
    if (PIND & 0x80) { // wait for DV signal to go high
      keypad = PINC; // read 8-bit input
      doneFlag = true; // finish getting user input
      while (PIND & 0x80) {} // wait for DV signal to go low
    }
  }

  count = 0;
  // convert each keypad input to number
  for (index = 0; index <= 7; index++) {
    if (keypad & (1 << index)) {
      count++;
      password = index + 1;
    }
  }

  if (count > 1) {
    password = 0;
  }
  return (password);
}
