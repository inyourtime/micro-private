#define STATE_IDLE 1
#define STATE_CHANGE_FREQ 7

#define IN_FREQ 11875
#define MIN_FREQ 15625/0.25
#define MAX_FREQ 15625/5
#define ADC_TIME 15625*0.2

#define MODE_TOGGLE 1
#define MODE_DIMMING 2

unsigned int state;
unsigned int freqOCR;
unsigned int dutyDimming;
unsigned int mode;


void adcSetup() {
  ADCSRA = 0x97;
  DIDR0 = 0x1;
  ADMUX = 0x40; // ADC channel 0
}

void timerADCSetup() {
  TCCR4A = 0;
  TCCR4B = 0;
  OCR4A = ADC_TIME; // every 1 s
  TCNT4 = 0x0;
  TIFR4 = 0x2F;
  TIMSK4 = 0;
  TCCR4B |= 0x08; // CTC mode
  TCCR4B |= 0x05; 
}

void timerDimmingSetup() {
  TCCR3A = 0;
  TCCR3B = 0;
  OCR3A = 992; // 3.125% duty cycle
  TCNT3 = 0x0;
  TIFR3 = 0x6;
  TIMSK3 = 0;
  TCCR3A = 0b00000011;  // 10 bit pwm 0b10000011
  TCCR3B = 0b00001000;  // divide 8 (Stop first)
}

void timerToggleSetup() {
  TCCR1A = 0;
  TCCR1B = 0;
  ICR1 = MIN_FREQ;
  OCR1A = MIN_FREQ / 2;
  OCR1B = MIN_FREQ / 2;
  TCNT1 = 0x0;
  TIFR1 = 0x6;
  TIMSK1 = 0;
  TCCR1A = 0b11110010;
  TCCR1B = 0b00011101; // divide 1024
}

void setup(void) {
  DDRB = 0b11110000; // set PB7:4 as
//  timer1SetupFastPWMMode5();
  PORTB = 0b11110000;
  DDRE = 0b00001000;
  PORTE = 0b00001000;
  
  timerToggleSetup();
  timerDimmingSetup();
  timerADCSetup();
  adcSetup();

//  stopTimerDimming();
  freqOCR = MIN_FREQ;
  dutyDimming = 992;
  mode = MODE_TOGGLE;
  state = STATE_IDLE;
  Serial.begin(38400);
  Serial.println("program begin");
}

void loop(void) {
  switch (state) {
    case STATE_IDLE:
      if ((PINK & 0x1) == 0) {
        Serial.println("Change Mode");
        changeMode(mode);
        delay(100);
      }
      if ((PINK & 0x2) == 0) {
        if (freqOCR == MAX_FREQ) break;
        freqOCR = freqOCR - IN_FREQ;
        state = STATE_CHANGE_FREQ;
        Serial.println("STATE_CHANGE_FREQ");
      }
      if ((PINK & 0x4) == 0) {
        if (freqOCR == MIN_FREQ) break;
        freqOCR = freqOCR + IN_FREQ;
        state = STATE_CHANGE_FREQ;
        Serial.println("STATE_CHANGE_FREQ");
      }
      if ((PINK & 0x8) == 0) {
        reset();
      }
      if (TIFR4 & 0x2) {
        TIFR4 = 0x2;
        ADCSRA |= 0x40;
      }
      if (ADCSRA & 0x10) {
        dutyDimming = ADC;
        ADCSRA |= 0x10;
//        Serial.println(dutyDimming);
        setDutyDimming(dutyDimming);
      }
    break;
    case STATE_CHANGE_FREQ:
      Serial.println(freqOCR);
      setFreq(freqOCR);
      delay(100);
      state = STATE_IDLE;
    break;
  }
}

void changeMode(unsigned int mode_ch) {
  if (mode_ch == MODE_TOGGLE) {
    mode = MODE_DIMMING;
    stopTimerToggle();
    startTimerDimming();
    Serial.println("Dimmimg mode");
  } else if (mode_ch == MODE_DIMMING) {
    mode = MODE_TOGGLE;
    stopTimerDimming();
    startTimerToggle();
    Serial.println("Toggle mode");
  }
}

void reset() {
  stopTimerToggle();
  stopTimerDimming();
}

void setFreq(unsigned int freqOCR) {
  stopTimerToggle();
  ICR1 = freqOCR;
  OCR1A = freqOCR / 2;
  OCR1B = freqOCR / 2;
  startTimerToggle();
}

void setDutyDimming(unsigned int dt) {
//  TCCR3B &= ~(0x07);
  OCR3A = dt;
//  TCCR3B |= 0x02;
}

void stopTimerToggle() {
  TCCR1B &= ~(0x07);
  TCNT1 = 0x0;
  TCCR1A &= 0x0F;
}

void startTimerToggle() {
  TCCR1A |= 0xF0;
  TCCR1B |= 0x05;
}

void stopTimerDimming() {
  TCCR3B &= ~(0x07);
  TCNT3 = 0x0;
  TCCR3A &= 0x3F;
}

void startTimerDimming() {
  TCCR3A |= 0x80;
  TCCR3B |= 0x02;
}
