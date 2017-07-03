/**
 * @file ringbuffer.h
 * @author Strahinja Jankovic (jankovics@etf.bg.ac.rs)
 * @date 2016
 * @brief Ringbuffer implementation
 *
 * Ringbuffer implementation which allows Byte sized elements to be stored and
 * retrieved.
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

/* Standard includes. */
#include <stdio.h>

/** @brief Ringbuffer structure */
typedef struct {
	uint8_t *pucBuffer; /**< pointer to buffer memory */
	uint8_t *pucHead;   /**< pointer to current buffer head */
	uint8_t *pucTail;   /**< pointer to current buffer tail */
	uint8_t *pucEnd;    /**< pointer to end of buffer memory */
	uint8_t ucCount;    /**< current count of items in buffer */
	uint8_t ucMaxCount; /**< max number of items in buffer */
} RingBuffer_t;

/** @brief Ringbuffer handle */
typedef void * RingBufferHandle_t;

/**
 * @brief Initialize Ringbuffer
 * @param ucSize number of elements in buffer
 * @return handle of created Ringbuffer
 *
 * Create and initialize Ringbuffer. Function allocates memory needed for buffer according to
 * @p ucSize and initializes all pointers. Returns handle of created Ringbuffer.
 */
extern RingBufferHandle_t xRingBufferCreate( uint8_t ucSize );

/**
 * @brief Enqueue data to Ringbuffer
 * @param xRingBuffer Handle of Ringbuffer where to enqueue
 * @param ucData Data to be enqueued
 * @return pdPASS
 *
 * Enqueue one data item to Ringbuffer. If buffer is full first written item will be overwritten.
 *
 * TODO: Add handling if buffer is full
 */
extern UBaseType_t xRingBufferEnqueue( RingBufferHandle_t xRingBuffer, uint8_t ucData );

/**
 * @brief Dequeue data from Ringbuffer
 * @param xRingBuffer Handle of Ringbuffer from which to dequeue
 * @param pucData Pointer to buffer where dequeued data will be placed
 * @return pdPASS if successful, pdFAIL if not
 *
 * Dequeue one data item from Ringbuffer. If buffer is empty, function will return
 * pdFAIL.
 */
extern UBaseType_t xRingBufferDequeue( RingBufferHandle_t xRingBuffer, uint8_t *pucData );

#endif /* RINGBUFFER_H_ */
