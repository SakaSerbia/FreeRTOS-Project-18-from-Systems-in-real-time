/**
 * @file hal_led.h
 * @author Strahinja Jankovic (jankovics@etf.bg.ac.rs)
 * @date 2016
 * @brief LED API
 * 
 * Helper functions for LED management
 */

#ifndef HAL_LED_H
#define HAL_LED_H

/* LEDS are connected to Port D */
#define LED_PORT_DIR	( P4DIR )
#define LED_PORT_OUT	( P4OUT )

/* LED pins definitions */
#define LED1_BIT		( 3 )
#define LED2_BIT		( 4 )
#define LED3_BIT		( 5 )
#define LED4_BIT		( 6 )

/* macros to be used in code */
#define LED1			( 1 << LED1_BIT )
#define LED2			( 1 << LED2_BIT )
#define LED3			( 1 << LED3_BIT )
#define LED4			( 1 << LED4_BIT )
#define LED_ALL			( LED1 | LED2 | LED3 | LED4 )

/**
 * @brief Initialize ports supported by HAL
 * 
 * Initialize LED ports and pins
 */
extern void vHALInitLED( void );

/* LED management macros */
/* Turn on LED */
#define halSET_LED(led)			( LED_PORT_OUT |= led )
/* Turn off LED */
#define halCLR_LED(led)			( LED_PORT_OUT &= ~led )
/* Toggle LED */
#define halTOGGLE_LED(led)		( LED_PORT_OUT ^= led )


#endif /* HAL_BOARD_H */
