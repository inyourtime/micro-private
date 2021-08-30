#include <avr/io.h>
#include "timer_setup.h"

void Timer_init(uint8_t timer, uint8_t mode) {
	if (timer == TIMER_0) {
    TCCR0A = 0;
    TCCR0B = 0;
		if (mode == NORMAL) {
			// Normal mode in timer 0
			TCCR0A &= ~(1<<WGM01)|(1<<WGM00);
			TCCR0B &= ~(1<<WGM02);
		} else if (mode == CTC) {
			// CTC mode in timer 0
			TCCR0A &= ~(1<<WGM00);
			TCCR0A |= (1<<WGM01);
			TCCR0B &= ~(1<<WGM02);
		}
	} else if (timer == TIMER_1) {
    TCCR1A = 0;
    TCCR1B = 0;
		if (mode == NORMAL) {
			// Normal mode in timer 1
			TCCR1A &= ~(1<<WGM11)|(1<<WGM10);
			TCCR1B &= ~(1<<WGM13)|(1<<WGM12); 
		} else if (mode == CTC) {
			// CTC mode in timer 1
			TCCR1A &= ~(1<<WGM11)|(1<<WGM10);
			TCCR1B |= (1<<WGM12);
			TCCR1B &= ~(1<<WGM13);
		}
	} else if (timer == TIMER_2) {
    TCCR2A = 0;
    TCCR2B = 0;
		if (mode == NORMAL) {
			// Normal mode in timer 2
			TCCR2A &= ~(1<<WGM21)|(1<<WGM20);
			TCCR2B &= ~(1<<WGM22);
		} else if (mode == CTC) {
			// CTC mode in timer 2
			TCCR2A &= ~(1<<WGM20);
			TCCR2A |= (1<<WGM21);
			TCCR2B &= ~(1<<WGM22);
		}
	} else if (timer == TIMER_3) {
    TCCR3A = 0;
    TCCR3B = 0;
		if (mode == NORMAL) {
			// Normal mode in timer 3
			TCCR3A &= ~(1<<WGM31)|(1<<WGM30);
			TCCR3B &= ~(1<<WGM33)|(1<<WGM32);
		} else if (mode == CTC) {
			// CTC mode in timer 3
			TCCR3A &= ~(1<<WGM31)|(1<<WGM30);
			TCCR3B |= (1<<WGM32);
			TCCR3B &= ~(1<<WGM33);
		}
	} else if (timer == TIMER_4) {
    TCCR4A = 0;
    TCCR4B = 0;
		if (mode == NORMAL) {
			// Normal mode in timer 4
			TCCR4A &= ~(1<<WGM41)|(1<<WGM40);
			TCCR4B &= ~(1<<WGM43)|(1<<WGM42);
		} else if (mode == CTC) {
			// CTC mode in timer 4
			TCCR4A &= ~(1<<WGM41)|(1<<WGM40);
			TCCR4B |= (1<<WGM42);
			TCCR4B &= ~(1<<WGM43);
		}
	} else if (timer == TIMER_5) {
    TCCR5A = 0;
    TCCR5B = 0;
		if (mode == NORMAL) {
			// Normal mode in timer 5
			TCCR5A &= ~(1<<WGM51)|(1<<WGM50);
			TCCR5B &= ~(1<<WGM53)|(1<<WGM52);
		} else if (mode == CTC) {
			// CTC mode in timer 5
			TCCR5A &= ~(1<<WGM51)|(1<<WGM50);
			TCCR5B |= (1<<WGM52);
			TCCR5B &= ~(1<<WGM53);
		}
	}
}

void Timer_ON(uint8_t timer, uint16_t prescaler, uint16_t start_from) {
	if (timer == TIMER_0) {
//		TCCR0B &= ~(0x07);
		if (prescaler == 1) {
			TCCR0B |= 0x01;
		} else if (prescaler == 8) {
			TCCR0B |= 0x02;
		} else if (prescaler == 64) {
			TCCR0B |= 0x03;
		} else if (prescaler == 256) {
			TCCR0B |= 0x04;
		} else if (prescaler == 1024) {
			TCCR0B |= 0x05;
		}
		TCNT0 = start_from;
	} else if (timer == TIMER_1) {    
//		TCCR1B &= ~(0x07);
		if (prescaler == 1) {
			TCCR1B |= 0x01;
		} else if (prescaler == 8) {
			TCCR1B |= 0x02;
		} else if (prescaler == 64) {
			TCCR1B |= 0x03;
		} else if (prescaler == 256) {
			TCCR1B |= 0x04;
		} else if (prescaler == 1024) {
			TCCR1B |= 0x05;
		}
		TCNT1 = start_from;
	} else if (timer == TIMER_2) {
//		TCCR2B &= ~(0x07);
		if (prescaler == 1) {
			TCCR2B |= 0x01;
		} else if (prescaler == 8) {
			TCCR2B |= 0x02;
		} else if (prescaler == 64) {
			TCCR2B |= 0x03;
		} else if (prescaler == 256) {
			TCCR2B |= 0x04;
		} else if (prescaler == 1024) {
			TCCR2B |= 0x05;
		}
		TCNT2 = start_from;
	} else if (timer == TIMER_3) {
//		TCCR3B &= ~(0x07);
		if (prescaler == 1) {
			TCCR3B |= 0x01;
		} else if (prescaler == 8) {
			TCCR3B |= 0x02;
		} else if (prescaler == 64) {
			TCCR3B |= 0x03;
		} else if (prescaler == 256) {
			TCCR3B |= 0x04;
		} else if (prescaler == 1024) {
			TCCR3B |= 0x05;
		}
		TCNT3 = start_from;
	} else if (timer == TIMER_4) {
//		TCCR4B &= ~(0x07);
		if (prescaler == 1) {
			TCCR4B |= 0x01;
		} else if (prescaler == 8) {
			TCCR4B |= 0x02;
		} else if (prescaler == 64) {
			TCCR4B |= 0x03;
		} else if (prescaler == 256) {
			TCCR4B |= 0x04;
		} else if (prescaler == 1024) {
			TCCR4B |= 0x05;
		}
		TCNT4 = start_from;
	} else if (timer == TIMER_5) {
//		TCCR5B &= ~(0x07);
		if (prescaler == 1) {
			TCCR5B |= 0x01;
		} else if (prescaler == 8) {
			TCCR5B |= 0x02;
		} else if (prescaler == 64) {
			TCCR5B |= 0x03;
		} else if (prescaler == 256) {
			TCCR5B |= 0x04;
		} else if (prescaler == 1024) {
			TCCR5B |= 0x05;
		}
		TCNT5 = start_from;
	}
}

void Timer_OFF(uint8_t timer) {
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
