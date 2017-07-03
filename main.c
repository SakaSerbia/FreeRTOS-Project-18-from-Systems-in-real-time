/**
 * @file main.c
 * @brief Project: Real time systems, serial number 18.
 * @author Stefan Tesanovic
 * @date 11/06/2017
 *
 * Realize the system that starts acquiring from channels A14 and A15 for every 100 ms with software timer.
 * In an interrupt routine, the conversion results are entered in line with Queue, which is protected by mutsex, so when someone wants to read a message from the line, he must first take a mutsex. The message should contain the information about the channel that was evaluated and the 12 bit value that was read.
 * The tasks xTask1 and xTask2 read messages from the line, where xTask1 reads only messages related to channel A14, and xTask2 reads only messages related to channel A15.
 * Therefore, it is necessary for the tasks to first check what is at the top of the line (peek), so if it finds that the message is intended for them, they then read the message and remove it from the line (receive).
 * Task xTask1 counts the average of the last 16 received bounces and immediately into the mailbox (Queue length 1) with overwrite.
 * Task xTask2 counts the average of the last 32 received bounces and immediately into the mailbox (Queue length 1) with overwrite.
 * At the push of the button S1 and S2, the task xTask3 reads the corresponding mailbox and displays the measured mean value on the multiplexed LED display.
 *
 */

/* Standard includes */
#include <stdio.h>
#include <stdlib.h>

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "uart.h"
#include "adc.h"
#include "semphr.h"

/* Hardware includes */
#include "msp430.h"
#include "hal_ETF5438A.h"

/* Delay introduced due to synchronization of taps */
#define mainTASK_SYNC_DELAY     ( pdMS_TO_TICKS(20) )

/* The timer period used for multiplexing the display */
#define mainTIMERLED_PERIOD     ( pdMS_TO_TICKS(5) )

/* Timer periods */
#define mainTIMER100_PERIOD     ( pdMS_TO_TICKS(100) )

/* Task Priorities */
#define mainHP_TASK_PRIO        ( 2 )
#define mainLP_TASK_PRIO        ( 1 )

/* Start konverzije */
#define adcSTART_CONV       do { ADC12CTL0 |= ADC12SC; } while( 0 )

/* Function declarations */
static void prvSetupHardware( void );
static void prvTask1( void *pvParameters );
static void prvTask2( void *pvParameters );
static void prvTask3( void *pvParameters );
static void vTimer100Callback( TimerHandle_t xTimer100 );   // software timer
static void vTimerLEDCallback( TimerHandle_t xTimer );

/* Handler declarations */
static TaskHandle_t      xTask3         = NULL;
static TimerHandle_t     xTimerLED      = NULL;
static TimerHandle_t     xTimer100      = NULL;
static QueueHandle_t     xADCDataQueue  = NULL;
static QueueHandle_t     xQueue1        = NULL; //For task1
static QueueHandle_t     xQueue2        = NULL; //For task2
static SemaphoreHandle_t xMutex_ADCQueue= NULL;

/* Variables that counting the number of bounces received for Task1 and Task2 */
uint8_t ucCounter1, ucCounter2;

/* The number of bounces based on which is calculat average value for Task1 and Task2 */
const uint16_t usSamples1=16, usSamples2=32;

/* The mean value of the 16 bounces for Task 1 */
uint16_t usADCAvg_value1 = 0;

/* The last 16 readouts are cyclically typed in the series */
uint16_t usADCRead1[ 16 ] = { 0 };

/* The mean value of the 32 bounces for Task 2 */
uint16_t usADCAvg_value2 = 0;

/* The last 32 readouts are cyclically typed in the series */
uint32_t ulADCRead2[ 32 ] = { 0 };

/* A set of four digits whose values are printed on the LED */
int pucDigit[ 4 ];

/* The mean value of the selected task that will be printed on the LED */
uint16_t Avg_Value_LED;

/* Table for printing the digits on the LED */
const uint8_t pucTabelaseg[] = {    0x7e,
                                    0x30,
                                    0x6d,
                                    0x79,
                                    0x33,
                                    0x5b,
                                    0x5f,
                                    0x70,
                                    0x7f,
                                    0x7b };

/**
 * @brief Entering the mean value of the last 16 buffers measured on channel A14
 *
 * Check if the message at the top of the message line is for Task1.
 * If it is, it reads the message and the swab is out of line.
 * After that, the average value of the last 32 received bounces is recalculated and the new medium is entered into the mailbox with overwrite.
 *
 */
static void prvTask1( void *pvParameters )
{
    /* Check whether the message in the row with the messages belongs to Task1 */
    ADCmsg_t xCheckQueue;

    /* Enters the data if it belongs to Tasku1 */
    ADCmsg_t xReadQueue;

    /* The sum of the last 32 */
    uint16_t usSum=0;

    int i = 0;
    for ( ;; )
    {

        /* Read the message without deleting it from the message line */
        xQueuePeek ( xADCDataQueue , &xCheckQueue , portMAX_DELAY ) ;

        /* If the message represents a conversion value from channel A14 then it belongs to Tasku1 */
        if( xCheckQueue.buttonNum == S1)
        {

            /* Take the mutex to access the line with the messages containing the conversion results */
            xSemaphoreTake( xMutex_ADCQueue, portMAX_DELAY );

            /* Read the message */
            xQueueReceive( xADCDataQueue, &xReadQueue, portMAX_DELAY );

            /* Release the mutex */
            xSemaphoreGive( xMutex_ADCQueue );

            /* In the array with the index counter, the value of the read data is entered */
            usADCRead1[ ucCounter1 ] = xReadQueue.value;

            /* The counter is increased by 1 */
            ucCounter1 = ucCounter1 + 1;

            /* If the counter has exceeded 16, it resets to 0 */
            /* This way, the cyclical entry of the last 16 readers received is provided */
            if( ucCounter1 == usSamples1) ucCounter1 = 0;

            /* The calculation of the last 32 */
            usSum = 0;
            for (i = 0; i < usSamples1; i++)
                usSum += usADCRead1[ i ];

            /* The mean value of the last 16 bets is calculated */
            usADCAvg_value1 = usSum / usSamples1;

            /* A mailbox with an overwrite is entered */
            xQueueOverwrite ( xQueue1 , &usADCAvg_value1 );

        }

    }

}

/**
 * @brief Entering the mean value of the last 32 buffers measured on channel A15
 *
 * Check if the message at the top of the message line is for Task2.
 * If it is, it reads the message and the swab is out of line.
 * After that, the average value of the last 32 received bounces is recalculated and the new medium is entered into the mailbox with overwrite.
 *
 */
static void prvTask2( void *pvParameters )
{

    /* Check whether the message in the row with the messages belongs to Task2 */
    ADCmsg_t xCheckQueue;

    /* Enters the data if it belongs to Tasku2 */
    ADCmsg_t xReadQueue;

    /* The sum of the last 32 */
    uint32_t usSum=0;
    int i = 0;
    for ( ;; )
    {

        /* Read the message without deleting it from the message line */
        xQueuePeek ( xADCDataQueue , &xCheckQueue , portMAX_DELAY ) ;

        /* If the message represents a conversion value from channel A15 then it belongs to Tasku2 */
        if( xCheckQueue.buttonNum == S2 )
        {

            /* Take the mutex to access the line with the messages containing the conversion results */
            xSemaphoreTake( xMutex_ADCQueue, portMAX_DELAY );

            /* Read the message */
            xQueueReceive( xADCDataQueue, &xReadQueue, portMAX_DELAY );

            /* Release the mutex */
            xSemaphoreGive( xMutex_ADCQueue );

            /* In the array with the index counter, the value of the read data is entered */
            ulADCRead2[ ucCounter2 ] = xReadQueue.value;

            /* The counter is increased by 1 */
            ucCounter2 = ucCounter2 + 1;

            /* If the counter has exceeded 32, it resets to 0 */
            /* This way, the cyclical entry of the last 32 readers received is provided */
            if( ucCounter2 == usSamples2) ucCounter2 = 0;

            /* The calculation of the last 32 */
            usSum = 0;
            for (i = 1; i < usSamples2; i++)
                usSum += ulADCRead2[ i ];

            /* The mean value of the last 32 is calculated */
            usADCAvg_value2 = usSum / usSamples2;

            /* A mailbox with an overwrite is entered */
            xQueueOverwrite ( xQueue2 , &usADCAvg_value2 );

        }
    }
}

/**
 * @brief It forms a array of four digits based on a four-digit number
 *
 * Based on a four-digit number, a array of four digits is created that will serve
 * to print the mean value of the selected channel on the LED.
 *
 */
static void prvToDigits()
{

    pucDigit[ 3 ] = Avg_Value_LED % 10;
    Avg_Value_LED /= 10;
    pucDigit[ 2 ] = Avg_Value_LED % 10;
    Avg_Value_LED /= 10;
    pucDigit[ 1 ] = Avg_Value_LED % 10;
    Avg_Value_LED /= 10;
    pucDigit[ 0 ] = Avg_Value_LED % 10;

}

/**
 * @brief The mean value to be printed on the LED is calculated
 *
 * It is examined whether the S1 or S2 key is pressed, and depending on that, xTask3 reads the corresponding mailbox
 * and displays the average value on the multiplexed LED display.
 *
 */
static void prvTask3( void *pvParameters )
{

    /* Variables that are used to check whether the S1 key is pressed */
    uint8_t ucLastState1 = 0, ucState1 = 0;

    /* Variables that are used to check whether the S2 key is pressed */
    uint8_t ucLastState2 = 0, ucState2 = 0;

    for ( ;; )
    {

        /* The current state of the S1 key */
        ucState1 = P2IN & BIT4;

        /* If the S1 key is pressed */
        if( ( ucState1 == 0x00 ) && ( ucLastState1 == BIT4 ) )
        {

            /* Read the average value from the mailbox belonging to Task1 */
            xQueueReceive( xQueue1 , &Avg_Value_LED , 0 );

            /* Calculate the figure of this mean value */
            prvToDigits();
        }

        /* The current key condition is pre-installed */
        ucLastState1 = ucState1;

        /* Synchronization of the taskov is in progress */
        vTaskDelay( mainTASK_SYNC_DELAY );

        /* The current state of the S2 key */
       ucState2 = P2IN & BIT5;

       /* If the S2 key is pressed */
       if( ( ucState2 == 0x00) && ( ucLastState2 == BIT5 ) )
       {

           /* Read the average value from the mailbox belonging to Task2 */
           xQueueReceive( xQueue2 , &Avg_Value_LED , 0 );

           /* Calculate the figure of this mean value */
           prvToDigits();
       }

        /* The current key condition is pre-installed */
        ucLastState2 = ucState2;

        /* Synchronization of the taskov is in progress */
        vTaskDelay( mainTASK_SYNC_DELAY );
    }
}

/**
 * @brief LED timer
 *
 *  This timer is being used for multiplexing the display and showing the needed value.
 *
 */
static void vTimerLEDCallback( TimerHandle_t xTimer )
{

	/* usDigit represents the priority order of the digit
	 * in the value that should be displayed;
	 * function takes the digit and displays it
	 * on the correct part of the display
	 */
    static uint8_t ucDigit = 0;

    switch( ucDigit )
    {

    case 0:
        P10OUT |= BIT6;
        P6OUT = pucTabelaseg[ pucDigit[ 0 ] ];
        P11OUT &= ~BIT1;
        ucDigit = 1;
        break;

    case 1:
        P11OUT |= BIT1;
        P6OUT = pucTabelaseg[ pucDigit[ 1 ] ];
        P11OUT &= ~BIT0;
        ucDigit = 2;
        break;

    case 2:
        P11OUT |= BIT0;
        P6OUT = pucTabelaseg[ pucDigit[ 2 ] ];
        P10OUT &= ~BIT7;
        ucDigit = 3;
        break;
		
    case 3:
        P10OUT |= BIT7;
        P6OUT = pucTabelaseg[ pucDigit[ 3 ] ];
        P10OUT &= ~BIT6;
        ucDigit = 0;
        break;

    default:
        break;

    }

}

/**
 * @brief Callback function for timer
 *
 * Starts AD conversion every 100ms.
 */
static void vTimer100Callback( TimerHandle_t xTimer100 )
{

    adcSTART_CONV;
}

/**
 * @brief Kreiranje potrebnih taskova i semafora
 *
 * Ispituje se da li je pritisnut taster S1 ili S2, i u zavisnosti od toga xTask3 ocitava odgovarajuci mailbox/promenljivu
 * i prikazuje ocitanu srednju vrednost na multipleksiranom LED displeju.
 * Kako se funkcija se poziva na svaku 1ms, to se na 1ms i vrsi multipleksiranje displeja.
 *
 */
void main( void )
{
    /* Inicijalizacija hardvera */
    prvSetupHardware();

    /* Kreiranje taskova */
    xTaskCreate(prvTask1, "LP Task", configMINIMAL_STACK_SIZE, NULL, mainLP_TASK_PRIO, NULL );
    xTaskCreate(prvTask2, "LP Task", configMINIMAL_STACK_SIZE, NULL, mainLP_TASK_PRIO, NULL);
    xTaskCreate(prvTask3, "HP Task", configMINIMAL_STACK_SIZE, NULL,  mainHP_TASK_PRIO, &xTask3);

    /* Kreiranje tajmera za multipleksiranje displeja */
    xTimerLED = xTimerCreate("TimerLED", mainTIMERLED_PERIOD, pdTRUE, NULL, vTimerLEDCallback);

    /* Create timers
    xTimer100 = xTimerCreate("Timer100", mainTIMER100_PERIOD, pdTRUE, NULL, vTimer100Callback);

    /* Red sa porukama u koji se upisuju konvertovani podaci */
    xADCDataQueue = xQueueCreate( 64, sizeof( ADCmsg_t ) );

    /* Red sa porukama duzine 1 u koji se upisuje srednja vrednost poslednjih 16 odbiraka koji pripadaju Tasku1 */
    xQueue1 = xQueueCreate ( 1, sizeof( uint16_t) );

    /* Red sa porukama duzine 1 u koji se upisuje srednja vrednost poslednjih 32 odbiraka koji pripadaju Tasku2 */
    xQueue2 = xQueueCreate ( 1, sizeof( uint16_t) );

    /* Koristi se za pristup redu sa porukama gde se nalaze konvertovani podaci */
    xMutex_ADCQueue = xSemaphoreCreateMutex();

    /* Ukljucuje se tajmer koji sluzi za multipleksiranje LED-a */
    xTimerStart( xTimer100, 0 ); 
    xTimerStart( xTimerLED, 0 );

    /* Startuj scheduler */
    vTaskStartScheduler();


    for( ;; );

}

/**
 * @brief Configure A/D converters
 *
 */
void vADCInitHardware( void )
{

     /* Selection of channels A14 and A15 A / D converters. */
    P7SEL |= BIT6 + BIT7;

    /* Turn on the A / D converter and start the conversion to the SC bit */
    ADC12CTL0 = ADC12ON + ADC12MSC;

     /*  Setting the SHC bit for the sample source and hold signal and the conversion mode is the sequence of the channel */
     ADC12CTL1 = ADC12SHS_0 | ADC12CONSEQ_1 | ADC12SHP;

     /* In MEM0, the converted values from the A14 channel are entered */
     ADC12MCTL0 = ADC12INCH_14;

     /* In MEM1, the converted values from channel A15 are entered and this is the end of the sequence */
     ADC12MCTL1 = ADC12INCH_15 | ADC12EOS;

     /* Allows a break when there is a conversion result in MEM0 or MEM1 */
     ADC12IE |= ADC12IE0 + ADC12IE1;

     /* Permission conversion */
     ADC12CTL0 |= ADC12ENC;

}

/**
 * @brief Configure hardware upon boot
 *
 */
static void prvSetupHardware( void )
{

    taskDISABLE_INTERRUPTS();

    /* Disable the watchdog. */
    WDTCTL = WDTPW + WDTHOLD;

    /* Initialization of AD converter */
    vADCInitHardware();

    /* Configure Clock. Since we aren't using XT1 on the board, */
    /* configure REFOCLK to source FLL adn ACLK. */
    SELECT_FLLREF(SELREF__REFOCLK);
    SELECT_ACLK(SELA__REFOCLK);
    hal430SetSystemClock( configCPU_CLOCK_HZ, configLFXT_CLOCK_HZ );

    /* Enable buttons S1 and S2 as output*/
    P2DIR &= ~(0x30);

    /* Turn on all SELs */
    P11DIR |= BIT0 + BIT1;
    P10DIR |= BIT7 + BIT6;

    /* LED segments are output */
    P6DIR |= ~BIT7;
}

/**
 * @brief Interupt cycle ADC.
 *
 * If a conversion is made, we store the value of the current conversion in the variable.
 * Then we invoke a function that prints that value on the LCD.
 *
 */
#pragma vector=ADC12_VECTOR
__interrupt void adc12_isr()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    switch( ADC12IV )
    {

    case  6: /* Vector  6: ADC12IFG0 */
		{

        /* When the button S1 is pressed, make a message with two fields
		 * report that is's S1 and send the data read from ADC channel 14
		 * resized to 12bits
		 */
        ADCmsg_t  xMsg = { S1, ADC12MEM0 };

        /* Send that message to ADC queue */
        xQueueSendToBackFromISR( xADCDataQueue, &xMsg, &xHigherPriorityTaskWoken );

		}
    break;

    case  8: /* Vector  8: ADC12IFG1 */
		{
		/* When the button S2 is pressed, make a message with two fields
		 * report that is's S2 and send the data read from ADC channel 15
		 * resized to 12bits
		 */
        ADCmsg_t xMsg = { S2, ADC12MEM1 };

        /* Send that message to ADC queue */
        xQueueSendToBackFromISR( xADCDataQueue, &xMsg, &xHigherPriorityTaskWoken );

		}
    break;
	
    default:
        break;

    }

}
