/**
 * @file	: circural_buffer.h
 * @brief	Header for circural_buffer.c file
 *
 * Header containing the function prototypes, structure and
 * status enum for circural buffer.
 *
 */

#ifndef CIRCURAL_BUFFER_H
#define CIRCURAL_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

#define BUF_SIZE 50 ///< Size of the buffer

/** CBufType
 *  Circural buffer struct
 *
 *Structure containing array for storing the contents of a buffer,
 * a head, tail and a boolean value defining if the buffer should
 * or shouldn't contain 'n\' sign, so it could be safely parsed.
 *
 */
typedef struct {

  uint16_t body[BUF_SIZE]; ///< Array of size BUF_SIZE containing the data
  uint16_t head;           ///< Value containing the index to write to
  uint16_t tail;           ///< Value containing the index to read from
  bool parsable; ///< Boolean value describing if the buffer is parsable
                 ///< (contain "\n")

} CBufType;

/** CBufStatus
 *  Circural buffer status enum
 *
 *Enum containing various circural buffer states
 */
typedef enum {
  cbuferror = -3, ///< Returned when some unexpected states happen
  cbufempty = -2, ///< Returned when buffer is empty
  cbuffull = -1,  ///< Returned when buffer is full, or just filled
  cbufok = 0      ///< Returned when buiffer is fully operational
} CBufStatus;

/**
 * Initializes the buffer
 *
 * Sets head and tail to 0, and returns cbufempty if succeed.
 * @param[in] *cbuf Pointer to initialized circural buffer structure
 * @param[out] CBufStatus Status code from CBufStatus enum
 *
 */
CBufStatus CBufInit(CBufType *cbuf);

/**
 * Checks if buffer is empty
 *
 * Returns cbufok when not empty, and cbufempty when empty, basing on
 * the head and tail
 *
 * @param[in] *cbuf Pointer to initialized circural buffer structure
 * @param[out] CBufStatus Status code from CBufStatus enum
 *
 */
CBufStatus CBufIsEmpty(CBufType *cbuf);

/**
 * Checks if buffer is full
 *
 * Returns cbufok when not full, and cbuffull when empty, basing on
 * the head and tail
 *
 * @param[in] *cbuf Pointer to initialized circural buffer structure
 * @param[out] CBufStatus Status code from CBufStatus enum
 *
 */
CBufStatus CBufIsFull(CBufType *cbuf);

/**
 * Checks if buffer is parsable
 *
 * Returns true if parsable field in pointed structure is set,
 * and false it it isn't
 *
 * @param[in] *cbuf Pointer to initialized circural buffer structure
 * @param[out] Bool
 *
 */
bool CBufIsParsable(CBufType *cbuf);

/**
 * Inserts the value into buffer
 *
 * Inserts given value into the buffer pointed by the given pointer,
 * sets the parsable field in pointed structure if val is equal to "\n".
 * Does nothing but return cbuffull when tried to write to full buffer.
 *
 * @param[in] *cbuf Pointer to initialized circural buffer structure
 * @param[in] val Value to be pushed into the buffer
 * @param[out] CBufStatus Status code from CBufStatus enum
 *
 */
CBufStatus CBufPush(CBufType *cbuf, uint16_t val);

/**
 * Reads the value from the buffer
 *
 * Retrieve the oldest value from the buffer through the pointer,
 * returns the status code depending on the effect.
 * Does nothing but return cbempty when tried to read from empty buffer.
 *
 * @param[in] *cbuf Pointer to initialized circural buffer structure
 * @param[in] val Value to be pushed into the buffer
 * @param[out] CBufStatus Status code from CBufStatus enum
 *
 */
CBufStatus CBufPop(CBufType *cbuf, uint16_t *destination);

#endif // CIRCURAL_BUFFER_H
