/**
 * @file hal_led.c
 * @author Strahinja Jankovic
 * @date 2016
 * @brief LED API
 */

#include "msp430.h"
#include "hal_led.h"

void vHALInitLED( void )
{
    /* Switch port to output */
    LED_PORT_DIR |= LED_ALL;
    /* Switch LEDs off initially */
    LED_PORT_OUT &= ~LED_ALL;
}
