#ifndef ADC_H_
#define ADC_H_

#include "FreeRTOS.h"
#include "msp430.h"
#include "queue.h"
#include "task.h"

typedef enum
{
    S1,
    S2
} Button_t;

typedef struct
{
    Button_t buttonNum;
    uint16_t value;
} ADCmsg_t;


#endif /* ADC_H_ */
