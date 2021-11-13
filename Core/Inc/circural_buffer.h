#ifndef CIRCURAL_BUFFER_H
#define CIRCURAL_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

#define BUF_SIZE 8

typedef struct {
  uint16_t body[BUF_SIZE];
  uint16_t head;
  uint16_t tail;
} CBufType;

typedef enum {
  cbuferror = -3,
  cbufempty = -2,
  cbuffull = -1,
  cbufok = 0
} CBufStatus;

CBufStatus CBufInit(CBufType *cbuf);
CBufStatus CBufIsEmpty(CBufType *cbuf);
CBufStatus CBufPush(CBufType *cbuf, uint16_t val);
CBufStatus CBufPop(CBufType *cbuf, uint16_t *destination);
CBufStatus CBufIsFull(CBufType *cbuf);
#endif // CIRCURAL_BUFFER_H