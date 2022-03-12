/**
 * @file	: parser.h
 * @brief	Header for parser.c file
 *
 * Header containing the function prototypes, and
 * status enum for parser.
 *
 */

#ifndef PARSER_H
#define PARSER_H

#include "circural_buffer.h"
#include "stdbool.h"
#include "string.h"

/**
 * COUNT_OF
 *
 * Function-alike macro for counting members of array.
 *
 * @param[in] Pointer to first member of array
 * @param[out] Number of members of array
 */
#define COUNT_OF(arr) (sizeof(arr) / sizeof(0 [arr]))
/**
 * EOL
 *
 * Definition of End-of-line character
 *
 */
#define EOL '\n'

/**
 * ParserStatus
 * Parser status enum
 *
 * Enum containing return codes of parser functions
 *
 */
typedef enum {
  parsererror = -2,
  parseroverflowed = -1,
  parserok = 0
} ParserStatus;

/**
 * Takes one, whole line from buffer
 *
 * This function take whole line from circural buffer pointed by passed pointer,
 * reading up to EOL sign. Take the size of destination array too, to prevent the overwriting.
 *
 * @param[in] CBufType *buf Pointer to circural buffer
 * @param[in] char* Pointer to the destination array
 * @param[in]  uint8_t Destination array size
 * @param[out] ParsesStatus Return code from ParserStatus enum
 *
 */
ParserStatus ParserTakeLine(CBufType *buf, char *destination,
                            uint8_t destination_size);

/**
 * Takes the string array and splits it by terminator sign.
 *
 * This function take the string (prefferably from ParserTakeLine) and pass
 * the part of the input string up to termination sign ('#')
 * into destination string(also null-terminated).
 * Takes the reenter param to find out if the other part of splitted string is expected,
 * or new string is going to be passed.
 * Takes the destination array size, not to overflow.
 *
 *
 * @param[in] char [] Pointer to the input string
 * @param[in] char* Pointer to the destination array
 * @param[in] bool Boolean value describing if it is
 * first or next call on the same string
 * @param[in]  uint8_t Destination array size
 * @param[out] ParsesStatus Return code from ParserStatus enum
 *
 */
ParserStatus ParserParse(char input_string[], char *destination, bool reenter,
                         uint8_t destination_size);

#endif // PARSER_H
