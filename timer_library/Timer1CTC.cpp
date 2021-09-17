#include "Timer1CTC.h"

Timer1CTC Timer1;

void (*Timer1CTC::isrCallback)() = Timer1CTC::isrDefaultUnused;

ISR (TIMER1_COMPA_vect)
{
  Timer1.isrCallback();
}

void Timer1CTC::isrDefaultUnused()
{
}
