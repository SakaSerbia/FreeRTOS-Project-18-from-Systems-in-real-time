/**
 * @file uart.c
 * @author Strahinja Jankovic (jankovics@etf.bg.ac.rs)
 * @date 2016
 * @brief OS-aware UART communication
 *
 * Implementation of UART communication using FreeRTOS.
 * UART Task is created which handles all UART data communication.
 * Other tasks communicate with UART Task using "UART Queue".
 */

/* Standard includes. */
#include <stdio.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "uart.h"
#include "ringbuffer.h"

/* Hardware includes. */
#include "msp430.h"
#include "hal_ETF5438A.h"

/** @brief UART message enum */
typedef enum
{
	UART_MSG_STR,	/**< message contains string to be sent to PC */
	UART_MSG_CMD,	/**< message contains command; not used at the moment */
	UART_MSG_DAT	/**< message contains data; not used at the moment */
} UartMsgType_t;

/** @brief UART message structure */
typedef struct
{
	UartMsgType_t eMsgType;	/**< message type enum */
	uint8_t *pucMsgData;	/**< message data buffer */
} UARTMessage_t;

/** @brief UART Ringbuffer handle */
static RingBufferHandle_t xStringBuffer;
/** @brief UART Queue handle */
static QueueHandle_t xUARTQueue;

/**
 * @brief UART Task function
 * @param pvParameters not used
 *
 * UART Task that handles communication with PC.
 * Blocks while waiting on queue messages.
 * When message is received, it is parsed and bytes are placed into
 * Ringbuffer.
 * If data is not currently being transmitted, initialize transmission.
 */
static void prvTaskUART( void *pvParameters )
{
	UARTMessage_t *pucRxMsg;

	for( ;; )
	{
		/* block on reading message from queue */
		if( xQueueReceive( xUARTQueue, &pucRxMsg, portMAX_DELAY ) == pdTRUE )
		{
			/* if string message is received */
			if( pucRxMsg->eMsgType == UART_MSG_STR )
			{
				/* enqueue data into ring buffer */
				while( *pucRxMsg->pucMsgData != 0 )
				{
					xRingBufferEnqueue( xStringBuffer, *pucRxMsg->pucMsgData++ );
				}

				/* if transmission is not in progress, initiate transmission */
				if( !( UCA0IE & UCTXIE ) )
				{
					uint8_t ucData;
					xRingBufferDequeue( xStringBuffer, &ucData );
					UCA0TXBUF = ucData;
					UCA0IE |= UCTXIE;
				}
			}
		}
		else
		{
			for( ;; );
		}
	}
}

/** @brief Callback function handle */
static ReceiveByteCallbackFunction_t prvReceiveByteCallback;

void vUartSetRxCallback( ReceiveByteCallbackFunction_t pvCallbackFunction )
{
	prvReceiveByteCallback = pvCallbackFunction;
}

void vUartInit( void )
{
	P3SEL |= BIT4 | BIT5;	/* set P3.4 and P3.5 for USCI */
	UCA0CTL1 |= UCSWRST;	/* enter software reset */
	UCA0CTL1 |= UCSSEL_2;	/* select SMCLK for BRCLK */
	UCA0BRW = 86;			/* set BR to 86 and BRS to 6 for 115200 */
	UCA0MCTL = UCBRS_6;
	UCA0CTL1 &= ~UCSWRST;	/* leave software reset */
	UCA0IE |= UCRXIE;		/* enable USCI_A0 RX interrupt */

	/* create ringbuffer */
	xStringBuffer = xRingBufferCreate( 128 );
	/* create UART queue */
	xUARTQueue = xQueueCreate( 10, sizeof( UARTMessage_t * ) );
	/* create UART task */
	xTaskCreate( prvTaskUART, "UART Task", 4*configMINIMAL_STACK_SIZE, NULL, 6, NULL );
}

BaseType_t xUartSendString( const char *pcString, TickType_t xBlockTime )
{
	UARTMessage_t xMsg = { UART_MSG_STR, (uint8_t *)pcString };
	UARTMessage_t *pxMsg = &xMsg;
	BaseType_t xRet = pdFAIL;

	if( xQueueSendToBack( xUARTQueue, &pxMsg, xBlockTime ) == pdTRUE )
	{
		xRet = pdPASS;
	}

	return xRet;
}

void __attribute__ ( ( interrupt( USCI_A0_VECTOR ) ) ) vUSCIA0ISR ( void )
{
	switch( __even_in_range( UCA0IV, 4 ) )
	{
	case 0:		/* no interrupt */
		break;
	case 2:		/* RX interrupt */
		/* if callback is defined, execute it */
		if ( prvReceiveByteCallback )
		{
			prvReceiveByteCallback( UCA0RXBUF );
		}
		break;
	case 4:		/* TX interrupt */
	{
		RingBuffer_t *pxRingBuffer = ( RingBuffer_t *) xStringBuffer;

		/* dequeue from ringbuffer as long as there is data */
		if( pxRingBuffer->ucCount > 0 )
		{
			UCA0TXBUF = *pxRingBuffer->pucTail;

			if( pxRingBuffer->pucTail == pxRingBuffer->pucEnd )
			{
				pxRingBuffer->pucTail = pxRingBuffer->pucBuffer;
			}
			else
			{
				pxRingBuffer->pucTail++;
			}
			pxRingBuffer->ucCount--;

		}
		else
		{
			/* when there is no more data, disable interrupt */
			UCA0IE &= ~UCTXIE;
		}
	}
		break;
	}
}
