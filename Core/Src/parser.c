#include "parser.h"

ParserStatus ParserTakeLine(CBufType *buf, char *destination,
                            uint8_t destination_size) {
  CBufStatus bufstatus = cbufok;
  uint8_t i = 0;
  uint16_t Temp = 0;
  do {

    bufstatus = CBufPop(buf, &Temp);
    if (Temp == EOL) {
      destination[i] = '\0';
    } else {
      destination[i] = Temp;
    }
    i++;
    if (i >= destination_size) {
      return parseroverflowed;
    }
  } while (Temp != EOL && bufstatus == cbufok);
  return parserok;
}

ParserStatus ParserParse(char input_string[], char *destination, bool reenter,
                         uint8_t destination_size) {
  char *tmp;
  int i = 0;
  if (reenter == true) {
    tmp = strtok(NULL, "#");
    while (tmp[i] != '\0') {
      if (i >= destination_size) {
        return parseroverflowed;
      }
      destination[i] = tmp[i];
      i++;
    }
  } else {
    tmp = strtok(input_string, "#");
    while (tmp[i] != '\0') {
      if (i >= destination_size) {
        return parseroverflowed;
      }
      destination[i] = tmp[i];
      i++;
    }
  }

  return parserok;
}
