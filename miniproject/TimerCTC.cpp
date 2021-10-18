#include "Timer3CTC.h"

Timer3CTC Timer3;

void (*Timer3CTC::isrCallback)() = Timer3CTC::isrDefaultUnused;

ISR (TIMER3_COMPA_vect)
{
  Timer3.isrCallback();
}

void Timer3CTC::isrDefaultUnused()
{
}
