#ifndef _TIMER1_SETUP_H
#define _TIMER1_SETUP_H

#ifdef __cplusplus
extern "C" {
#endif

void timer1SetupCTC2(void);
void timer1SetupCTC(void);
void timer3SetupCTC(void);
void myDelay500(void);
void myDelay100(void);
void timer1Start(void);
void timer1Stop(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
