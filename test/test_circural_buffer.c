#ifdef TEST

#include "circural_buffer.h"
#include "unity.h"

CBufStatus status;
CBufType buf;
uint16_t test_value = 0xB00B;
uint16_t read_destination = 0;

void setUp(void) {

  CBufInit(&buf);
  read_destination = 0;
  test_value = 0xB00B;
}

void tearDown(void) {}

void test_circural_buffer_EmptyAfterInit(void) {

  status = CBufInit(&buf);
  TEST_ASSERT_EQUAL(cbufempty, status);
}

void test_circural_buffer_CBufIsEmptyReturnsEmptyWhenEmpty(void) {

  status = CBufIsEmpty(&buf);
  TEST_ASSERT_EQUAL(cbufempty, status);
}

void test_circural_buffer_CBufIsEmptyReturnsOkWhenNotEmpty(void) {

  CBufPush(&buf, test_value);
  status = CBufIsEmpty(&buf);
  TEST_ASSERT_EQUAL(cbufok, status);
}

void test_circural_buffer_CBufIsFullReturnsFullWhenFull(void) {

  for (int i = 0; i < BUF_SIZE - 1; i++) {
    CBufPush(&buf, test_value);
  }
  status = CBufIsFull(&buf);
  TEST_ASSERT_EQUAL(cbuffull, status);
}

void test_circural_buffer_NotEmptyAfterWriting(void) {

  CBufPush(&buf, test_value);
  TEST_ASSERT_FALSE(CBufIsEmpty(&buf));
}

void test_circural_buffer_ReturnsWrittenVar(void) {

  CBufPush(&buf, test_value);
  CBufPop(&buf, &read_destination);
  TEST_ASSERT_EQUAL_UINT16(test_value, read_destination);
}

void test_circural_buffer_HeadLoopsAtTheEdges(void) {

  for (int i = 0; i < BUF_SIZE; i++) {
    test_value = i;
    CBufPush(&buf, test_value);
    CBufPop(&buf, &read_destination);
  }
  TEST_ASSERT_EQUAL_UINT16(0, buf.head);
}

void test_circural_buffer_CBufPushReturnsFullWhenWrittenToFull(void) {

  for (int i = 0; i < BUF_SIZE; i++) {
    status = CBufPush(&buf, test_value);
  }
  TEST_ASSERT_EQUAL(cbuffull, status);
}

void test_circural_buffer_CBufPushDontOverwriteWhenFull(void) {

  CBufPush(&buf, 0xADA);
  for (int i = 0; i < BUF_SIZE; i++) {
    CBufPush(&buf, test_value);
  }
  CBufPop(&buf, &read_destination);
  TEST_ASSERT_EQUAL(0xADA, read_destination);
}

void test_circural_buffer_CBufPushReturnsFullWhenFilled(void) {

  for (int i = 0; i < BUF_SIZE - 1; i++) {
    CBufPush(&buf, test_value);
  }
  status = CBufPush(&buf, test_value);
  TEST_ASSERT_EQUAL(cbuffull, status);
}

void test_circural_buffer_TailLoopsAtTheEdges(void) {

  CBufPush(&buf, test_value);
  for (int i = 0; i < BUF_SIZE; i++) {
    CBufPush(&buf, test_value);
    CBufPop(&buf, &read_destination);
  }
  TEST_ASSERT_EQUAL_UINT16(0, buf.tail);
}

void test_circural_buffer_PopReturnCbufokWhenRead(void) {

  CBufPush(&buf, test_value);
  CBufPush(&buf, test_value);
  status = CBufPop(&buf, &read_destination);
  TEST_ASSERT_EQUAL(cbufok, status);
}

void test_circural_buffer_PopReturnCbufemptyWhenFullyRead(void) {

  CBufPush(&buf, test_value);
  status = CBufPop(&buf, &read_destination);
  TEST_ASSERT_EQUAL(cbufempty, status);
}

void test_circural_buffer_PopReturnCbufemptyWhenReadEmpty(void) {

  status = CBufPop(&buf, &read_destination);
  TEST_ASSERT_EQUAL(cbufempty, status);
}

void test_circural_buffer_PopReturnWrittenVar(void) {

  CBufPush(&buf, test_value);
  status = CBufPop(&buf, &read_destination);
  TEST_ASSERT_EQUAL(test_value, read_destination);
}

void test_circural_buffer_GetsParsableWhenNewLineWritten(void) {

  CBufPush(&buf, '\n');
  TEST_ASSERT(buf.parsable);
}

void test_circural_buffer_NotGetParsableWhenNewLineNotWritten(void) {

  CBufPush(&buf, test_value);
  TEST_ASSERT_FALSE(buf.parsable);
}

void test_circural_buffer_GetsNotParsableWhenNewLineRead(void) {

  CBufPush(&buf, '\n');
  CBufPop(&buf, &read_destination);
  TEST_ASSERT_FALSE(buf.parsable);
}

#endif // TEST
