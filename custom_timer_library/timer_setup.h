#ifndef _TIMER_SETUP_H
#define _TIMER_SETUP_H

#ifdef __cplusplus
extern "C" {
#endif
  
// Timer define
#define TIMER_0 0
#define TIMER_1 1
#define TIMER_2 2
#define TIMER_3 3
#define TIMER_4 4
#define TIMER_5 5

// Mode define
#define NORMAL 0
#define CTC 1
#define CTC_ICR 2

void Timer_init(uint8_t timer, uint8_t mode);
void Timer_ON(uint8_t timer, uint16_t prescaler, uint16_t start_from);
void Timer_OFF(uint8_t timer);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
