
#ifndef _ADC_SETUP_H
#define _ADC_SETUP_H

#ifdef __cplusplus
extern "C" {
#endif

void adcSetup(unsigned int);
int adcChangeChannel(unsigned int );
void adcStartConversion(void);
int adcConversionDone(void);
unsigned int adcReadData(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
