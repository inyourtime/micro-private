#include <avr/io.h>
#include "timer_setup.h"

void Timer_init(uint8_t timer, uint8_t mode)
{
  if (timer == TIMER_0) {
    TCCR0A = 0;
    TCCR0B = 0;
    if (mode == NORMAL) {
      // Normal mode in timer 0
    } else if (mode == CTC) {
      // CTC mode in timer 0
      TCCR0A |= 0x02;
    }
  } else if (timer == TIMER_1) {
    TCCR1A = 0;
    TCCR1B = 0;
    if (mode == NORMAL) {
      // Normal mode in timer 1
    } else if (mode == CTC) {
      // CTC mode in timer 1
      TCCR1B |= 0x08;
    }
  } else if (timer == TIMER_2) {
    TCCR2A = 0;
    TCCR2B = 0;
    if (mode == NORMAL) {
      // Normal mode in timer 2
    } else if (mode == CTC) {
      // CTC mode in timer 2
      TCCR2B |= 0x02;
    }
  } else if (timer == TIMER_3) {
    TCCR3A = 0;
    TCCR3B = 0;
    if (mode == NORMAL) {
      // Normal mode in timer 3
    } else if (mode == CTC) {
      // CTC mode in timer 3
      TCCR3B |= 0x08;
    }
  } else if (timer == TIMER_4) {
    TCCR4A = 0;
    TCCR4B = 0;
    if (mode == NORMAL) {
      // Normal mode in timer 4
    } else if (mode == CTC) {
      // CTC mode in timer 4
      TCCR4B |= 0x08;
    }
  } else if (timer == TIMER_5) {
    TCCR5A = 0;
    TCCR5B = 0;
    if (mode == NORMAL) {
      // Normal mode in timer 5 
    } else if (mode == CTC) {
      // CTC mode in timer 5
      TCCR5B |= 0x08;
    }
  }
}

void Timer_ON(uint8_t timer, uint16_t prescaler, uint16_t start_from)
{
  if (timer == TIMER_0) {
    TCNT0 = start_from;
    switch (prescaler) {
      case 1:    TCCR0B |= 0x01; break;
      case 8:    TCCR0B |= 0x02; break;
      case 64:   TCCR0B |= 0x03; break;
      case 256:  TCCR0B |= 0x04; break;
      case 1024: TCCR0B |= 0x05; break;
      default:   TCCR0B |= 0x00; break;
    }
  } else if (timer == TIMER_1) {
    TCNT1 = start_from;
    switch (prescaler) {
      case 1:    TCCR1B |= 0x01; break;
      case 8:    TCCR1B |= 0x02; break;
      case 64:   TCCR1B |= 0x03; break;
      case 256:  TCCR1B |= 0x04; break;
      case 1024: TCCR1B |= 0x05; break;
      default:   TCCR1B |= 0x00; break;
    }
  } else if (timer == TIMER_2) {
    TCNT2 = start_from;
    switch (prescaler) {
      case 1:    TCCR2B |= 0x01; break;
      case 8:    TCCR2B |= 0x02; break;
      case 64:   TCCR2B |= 0x03; break;
      case 256:  TCCR2B |= 0x04; break;
      case 1024: TCCR2B |= 0x05; break;
      default:   TCCR2B |= 0x00; break;
    }
  } else if (timer == TIMER_3) {
    TCNT3 = start_from;
    switch (prescaler) {
      case 1:    TCCR3B |= 0x01; break;
      case 8:    TCCR3B |= 0x02; break;
      case 64:   TCCR3B |= 0x03; break;
      case 256:  TCCR3B |= 0x04; break;
      case 1024: TCCR3B |= 0x05; break;
      default:   TCCR3B |= 0x00; break;
    }
  } else if (timer == TIMER_4) {
    TCNT4 = start_from;
    switch (prescaler) {
      case 1:    TCCR4B |= 0x01; break;
      case 8:    TCCR4B |= 0x02; break;
      case 64:   TCCR4B |= 0x03; break;
      case 256:  TCCR4B |= 0x04; break;
      case 1024: TCCR4B |= 0x05; break;
      default:   TCCR4B |= 0x00; break;
    }
  } else if (timer == TIMER_5) {
    TCNT5 = start_from;
    switch (prescaler) {
      case 1:    TCCR5B |= 0x01; break;
      case 8:    TCCR5B |= 0x02; break;
      case 64:   TCCR5B |= 0x03; break;
      case 256:  TCCR5B |= 0x04; break;
      case 1024: TCCR5B |= 0x05; break;
      default:   TCCR5B |= 0x00; break;
    }
  }
}

void Timer_OFF(uint8_t timer) 
{
  if (timer == TIMER_0) {
    TCCR0B &= ~(0x07);
  } else if (timer == TIMER_1) {
    TCCR1B &= ~(0x07);
  } else if (timer == TIMER_2) {
    TCCR2B &= ~(0x07);
  } else if (timer == TIMER_3) {
    TCCR3B &= ~(0x07);
  } else if (timer == TIMER_4) {
    TCCR4B &= ~(0x07);
  } else if (timer == TIMER_5) {
    TCCR5B &= ~(0x07);
  }
}


