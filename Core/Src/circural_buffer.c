#include "circural_buffer.h"

CBufStatus CBufInit(CBufType *cbuf) {
  cbuf->tail = 0;
  cbuf->head = 0;
  cbuf->parsable = false;
  CBufStatus status = cbufok;
  status = CBufIsEmpty(cbuf);
  if (status == cbufempty) {
    return cbufempty;
  } else {
    // Should never enter here
    return cbuferror;
  }
}

CBufStatus CBufIsEmpty(CBufType *cbuf) {
  if (cbuf->tail == cbuf->head) {
    return cbufempty;
  } else {
    return cbufok;
  }
}

CBufStatus CBufIsFull(CBufType *cbuf) {
  if (((cbuf->head + 1) % BUF_SIZE) == cbuf->tail) {
    return cbuffull;
  } else {
    return cbufok;
  }
}

CBufStatus CBufPush(CBufType *cbuf, uint16_t val) {
  CBufStatus status = CBufIsFull(cbuf);
  if (status == cbufok) {
    cbuf->body[cbuf->head] = val;
    cbuf->head = (cbuf->head + 1) % BUF_SIZE;
    status = CBufIsFull(cbuf);
    if (val == '\n') {
      cbuf->parsable = true;
    };

    return status;
  } else if (status == cbuffull) {
    return status;
  } else {
    // Should never enter here
    return cbuferror;
  }
}

CBufStatus CBufPop(CBufType *cbuf, uint16_t *destination) {
  CBufStatus status = CBufIsEmpty(cbuf);
  if (status == cbufok) {
    *destination = cbuf->body[cbuf->tail];
    if (cbuf->body[cbuf->tail] == '\n') {
      cbuf->parsable = false;
    }
    cbuf->tail = (cbuf->tail + 1) % BUF_SIZE;
    status = CBufIsEmpty(cbuf);
    return status;
  } else if (status == cbufempty) {
    return status;
  } else {
    // Should never enter here
    return cbuferror;
  }
}

bool CBufIsParsable(CBufType *cbuf) { return cbuf->parsable; }
