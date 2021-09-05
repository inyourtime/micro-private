#ifndef _TIMER_SETUP_H
#define _TIMER_SETUP_H

#ifdef __cplusplus
extern "C" {
#endif

// Timer overflow interuot enable
#define EN_INT_OVF_TIMER1() TIMSK1 |= 1<<TOIE1
#define EN_INT_OVF_TIMER2() TIMSK2 |= 1<<TOIE2
#define EN_INT_OVF_TIMER3() TIMSK3 |= 1<<TOIE3
#define EN_INT_OVF_TIMER4() TIMSK4 |= 1<<TOIE4
#define EN_INT_OVF_TIMER5() TIMSK5 |= 1<<TOIE5

// Timer1 output compare match enable
#define EN_INT_OCA_TIMER1() TIMSK1 |= 1<<OCIE1A
#define EN_INT_OCB_TIMER1() TIMSK1 |= 1<<OCIE1B
#define	EN_INT_OCC_TIMER1() TIMSK1 |= 1<<OCIE1C

// Timer2 output compare match enable	
#define EN_INT_OCA_TIMER2() TIMSK2 |= 1<<OCIE2A
#define EN_INT_OCB_TIMER2() TIMSK2 |= 1<<OCIE2B

// Timer3 output compare match enable	
#define EN_INT_OCA_TIMER3() TIMSK3 |= 1<<OCIE3A
#define EN_INT_OCB_TIMER3() TIMSK3 |= 1<<OCIE3B
#define EN_INT_OCC_TIMER3() TIMSK3 |= 1<<OCIE3C

// Timer4 output compare match enable	
#define EN_INT_OCA_TIMER4() TIMSK4 |= 1<<OCIE4A
#define EN_INT_OCB_TIMER4() TIMSK4 |= 1<<OCIE4B
#define EN_INT_OCC_TIMER4() TIMSK4 |= 1<<OCIE4C

// Timer5 output compare match enable
#define EN_INT_OCA_TIMER5() TIMSK5 |= 1<<OCIE5A
#define EN_INT_OCB_TIMER5() TIMSK5 |= 1<<OCIE5B
#define EN_INT_OCC_TIMER5() TIMSK5 |= 1<<OCIE5C

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
