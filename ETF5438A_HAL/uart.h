/**
 * @file uart.h
 * @author Strahinja Jankovic (jankovics@etf.bg.ac.rs)
 * @date 2016
 * @brief OS-aware UART communication
 *
 * Implementation of UART communication using FreeRTOS.
 * UART Task is created which handles all UART data communication.
 * Other tasks communicate with UART Task using "UART Queue".
 */

#ifndef UART_H_
#define UART_H_

/* receive calbback function pointer type */
typedef void ( *ReceiveByteCallbackFunction_t )( uint8_t ucData );

/**
 * @brief UART initialization
 *
 * Initialize USCI_A0 hardware for communication.
 * Create 128 byte ringbuffer to store characters that are transmitted to PC.
 * Create 10 item queue to store pointers to UART messages.
 * Create UART Task.
 */
extern void vUartInit( void );

/**
 * @brief API for other tasks to send string to PC
 * @param pcString String to send
 * @param xBlockTime Block time in ticks to wait if UART queue is full
 * @return pdPASS if successfully sent, pdFAIL if not
 *
 * Other tasks can send string to PC using this function.
 */
extern BaseType_t xUartSendString( const char *pcString, TickType_t xBlockTime );

/**
 * @brief Set callback function that is called when character is received from PC
 * @param pvCallbackFunction Callback function pointer
 *
 * If characters sent from PC need to be parsed, callback function can be implemented.
 * Function is executed in ISR context, so use only functions ending with FromISR.
 */
extern void vUartSetRxCallback( ReceiveByteCallbackFunction_t pvCallbackFunction );

#endif /* UART_H_ */
