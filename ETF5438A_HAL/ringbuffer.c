/**
 * @file ringbuffer.c
 * @author Strahinja Jankovic (jankovics@etf.bg.ac.rs)
 * @date 2016
 * @brief Ringbuffer implementation
 *
 * Ringbuffer implementation which allows Byte sized elements to be stored and
 * retrieved.
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"

#include "ringbuffer.h"


RingBufferHandle_t xRingBufferCreate( uint8_t ucSize )
{
	/* allocate buffer memory using pvPortMalloc */
	uint8_t *pucBuffer = ( uint8_t * ) pvPortMalloc( ucSize );
	/* allocate RingBuffer_t struct memory using pvPortMalloc */
	RingBuffer_t *pxRingBuffer = ( RingBuffer_t * ) pvPortMalloc( sizeof( RingBuffer_t ) );

	/* initialize pointers and counts */
	pxRingBuffer->pucBuffer = pucBuffer;
	pxRingBuffer->pucHead = pucBuffer;
	pxRingBuffer->pucTail = pucBuffer;
	pxRingBuffer->pucEnd = pucBuffer + ucSize - 1;
	pxRingBuffer->ucCount = 0;
	pxRingBuffer->ucMaxCount = ucSize - 1;

	/* return handle */
	return pxRingBuffer;
}

UBaseType_t xRingBufferEnqueue( RingBufferHandle_t xRingBuffer, uint8_t ucData )
{
	RingBuffer_t *pxRingBuffer = ( RingBuffer_t *) xRingBuffer;

	/* store item at head location */
	*pxRingBuffer->pucHead = ucData;

	/* wrap head pointer if end of buffer is reached, or just increment it */
	if( pxRingBuffer->pucHead == pxRingBuffer->pucEnd )
	{
		pxRingBuffer->pucHead = pxRingBuffer->pucBuffer;
	}
	else
	{
		pxRingBuffer->pucHead++;
	}

	/* increment number of items in queue */
	if( ( pxRingBuffer->ucCount + 1) < pxRingBuffer->ucMaxCount )
	{
		pxRingBuffer->ucCount++;
	}

	return pdPASS;
}

UBaseType_t xRingBufferDequeue( RingBufferHandle_t xRingBuffer, uint8_t *pucData )
{
	RingBuffer_t *pxRingBuffer = ( RingBuffer_t *) xRingBuffer;

	if( ( pxRingBuffer->pucHead == pxRingBuffer->pucTail ) && ( pxRingBuffer->ucCount == 0 ) )
	{
		/* if buffer is empty, return pdFAIL */
		return pdFAIL;
	}
	else
	{
		/* if there is data, get data from tail location */
		*pucData = *pxRingBuffer->pucTail;

		/* wrap tail pointer if at end of buffer, or just increment it */
		if( pxRingBuffer->pucTail == pxRingBuffer->pucEnd )
		{
			pxRingBuffer->pucTail = pxRingBuffer->pucBuffer;
		}
		else
		{
			pxRingBuffer->pucTail++;
		}

		/* decrement item count */
		if( pxRingBuffer->ucCount > 0 )
		{
			pxRingBuffer->ucCount--;
		}
	}

	return pdPASS;
}
