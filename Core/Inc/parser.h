#ifndef PARSER_H
#define PARSER_H

#include "circural_buffer.h"
#define EOL '\n'

typedef enum {
  parsererror = -2,
  parsernoeol = -1,
  parserok = 0
} ParserStatus;

ParserStatus ParserTakeLine(CBufType *buf, char *destination);
#endif // PARSER_H
