#ifndef Timer1_H
#define Timer1_H

#include <avr/io.h>

#define NORMAL 0
#define CTC    1

class Timer1 {
  public:
    /******************************
     * Configuration *
     *****************************/
    Timer1(uint8_t mode) {  // constructor
      _mode = mode;
    }
    void initialize(uint16_t prescaler = 1) { // Setup timer mode and prescaler
      TCCR1A = 0;
      TCCR1B = 0;
      if (_mode == NORMAL) {
        // Do not any thing
      } else if (_mode == CTC) {
        TCCR1B |= 0x08;
      }
      setPrescaler(prescaler);
    }
    void setPrescaler(uint16_t prescaler = 1) { // Setup prescaler
      const uint16_t _prescaler = prescaler;
      switch (_prescaler) {
        case 1:    clockSelectBits |= 0x01; break;
        case 8:    clockSelectBits |= 0x02; break;
        case 64:   clockSelectBits |= 0x03; break;
        case 256:  clockSelectBits |= 0x04; break;
        case 1024: clockSelectBits |= 0x05; break;
        default:   clockSelectBits |= 0x00; break;
      }
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
  
  private:
    uint8_t clockSelectBits;
    uint8_t _mode;
};

#endif
