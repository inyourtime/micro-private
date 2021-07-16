#define TRAFFIC_GREEN ~(0x1)
#define TRAFFIC_YELLOW ~(0x2)
#define TRAFFIC_RED ~(0x4)
#define ALL_ON 0x00
#define ALL_OFF 0xFF

#define SWITCH_START 0xE
#define SWITCH_CONFIRM 0xD
#define SWITCH_EXIT 0xB
#define IR_SENSOR 0x7
#define IR_AND_START 0x6

#define SEGMENT_DASH 0xBF

#define DELAY1 400

const uint16_t myPassword = 123;
uint16_t enteredPassword;
uint8_t number[3];
int state;
int vacant;
uint8_t digit[16] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
                      0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
                    };
                    
void setup() {
  Serial.begin(57600);
  
  PORTK = 0xFF; // pull up port K
  DDRK = 0; // keypad

  PORTD |= (1 << 7);  // pull up port D7
  DDRD &= ~(1 << 7);  // keypad(DV)

  DDRF = 0xFF;  // 7 segments

  PORTC = 0xFF;  // pull up port C
  DDRC = 0;  // switch C0 to C2 and IR sensor C3

  DDRA = 0xFF;  // traffic light 

  // initialize
  vacant = 3;
  PORTF = digit[vacant];
  PORTA = TRAFFIC_GREEN;
  state = 1;
}

void loop() {
  switch (state) {
    case 1:
      PORTA = TRAFFIC_GREEN;
      PORTF = digit[vacant];
      if ((PINC & 0xF) == IR_SENSOR) {
        state = 2;
      } else if ((PINC & 0xF) == SWITCH_EXIT && vacant < 3) {
        state = 8;
      }
      break;

    case 2:
      PORTA = TRAFFIC_YELLOW;
      if ((PINC & 0xF) == SWITCH_START) {
        state = 3;
      }
      break;
      
    case 3:
      PORTA = TRAFFIC_YELLOW;
      PORTF = SEGMENT_DASH;
      for (int i = 0; i < 3; i++) {
        number[i] = readKeypadSingleDigit();
        delay(10);
        Serial.println(number[i]);
        PORTF = digit[number[i]];
      }
      enteredPassword = combineNumber(number);
      state = 4;
      PORTA = ALL_ON;
      delay(DELAY1);
      PORTA = ALL_OFF;
      delay(DELAY1);  
      break;

    case 4:
      PORTA = TRAFFIC_YELLOW;      
      if ((PINC & 0xF) == SWITCH_CONFIRM) {
        Serial.println(enteredPassword);
        state = 5;
      }
      break;

    case 5:
      if (enteredPassword != myPassword) {
        state = 3;
        PORTA = TRAFFIC_RED;
        delay(DELAY1);
        PORTA = ALL_OFF;
        delay(DELAY1);
      } else if (enteredPassword == myPassword) {
        state = 6;
        PORTA = TRAFFIC_GREEN;
        delay(DELAY1);
        PORTA = ALL_OFF;
        delay(DELAY1);
      }
      break;
      
    case 6: 
      vacant -= 1;
      if (vacant == 0) {
        state = 7;
      } else if (vacant > 0) {
        state = 1;
      }
      break;
      
    case 7: 
      PORTA = TRAFFIC_RED;
      PORTF = digit[vacant];
      if ((PINC & 0xF) == SWITCH_EXIT) {
        state = 8;
      }
      break;
      
    case 8: 
      vacant += 1;
      state = 1;
      PORTA = ALL_ON;
      delay(DELAY1);
      PORTA = ALL_OFF;
      delay(DELAY1);      
      break;

    default:
      state = 1;
      vacant = 3;
  }
}

uint16_t combineNumber(uint8_t num[3]) {
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
      keypad = PINK; // read 8-bit input
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
