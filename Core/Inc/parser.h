#ifndef PARSER_H
#define PARSER_H

#include "circural_buffer.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

#define EOL '\n'

typedef enum {
  parsererror = -2,
  parseroverflowed = -1,
  parserok = 0
} ParserStatus;

ParserStatus ParserTakeLine(CBufType *buf, char *destination,
                            uint8_t destination_size);
ParserStatus ParserParse(char input_string[], char *destination, bool reenter,
                         uint8_t destination_size);

#endif // PARSER_H
