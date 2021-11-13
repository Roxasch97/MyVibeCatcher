#ifdef TEST

#include "circural_buffer.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_circural_buffer_EmptyAfterInit(void) {
  CBufStatus status;
  CBufType buf;
  status = CBufInit(&buf);
  TEST_ASSERT_EQUAL(cbufempty, status);
}

void test_circural_buffer_CBufIsEmptyReturnsEmptyWhenEmpty(void) {

  CBufStatus status;
  CBufType buf;
  CBufInit(&buf);
  status = CBufIsEmpty(&buf);
  TEST_ASSERT_EQUAL(cbufempty, status);
}

void test_circural_buffer_CBufIsEmptyReturnsOkWhenNotEmpty(void) {
  CBufStatus status;
  CBufType buf;
  CBufInit(&buf);
  CBufPush(&buf, 0xB00B);
  status = CBufIsEmpty(&buf);
  TEST_ASSERT_EQUAL(cbufok, status);
}

void test_circural_buffer_CBufIsFullReturnsFullWhenFull(void) {
  CBufStatus status;
  CBufType buf;
  CBufInit(&buf);
  for (int i = 0; i < BUF_SIZE - 1; i++) {
    CBufPush(&buf, 0xB00B);
  }
  status = CBufIsFull(&buf);
  TEST_ASSERT_EQUAL(cbuffull, status);
}

void test_circural_buffer_NotEmptyAfterWriting(void) {
  CBufType buf;
  CBufInit(&buf);
  uint16_t var = 0xB00B;
  CBufPush(&buf, var);
  TEST_ASSERT_FALSE(CBufIsEmpty(&buf));
}

void test_circural_buffer_ReturnsWrittenVar(void) {
  CBufType buf;
  CBufInit(&buf);
  uint16_t var = 0xB00B;
  CBufPush(&buf, var);
  uint16_t destination = 0;
  CBufPop(&buf, &destination);
  TEST_ASSERT_EQUAL_UINT16(var, destination);
}

void test_circural_buffer_HeadLoopsAtTheEdges(void) {

  CBufType buf;
  CBufInit(&buf);
  uint16_t pop_destination;
  int i = 0;
  for (i; i < BUF_SIZE; i++) {
    uint16_t var = i;
    CBufPush(&buf, var);
    CBufPop(&buf, &pop_destination);
  }
  TEST_ASSERT_EQUAL_UINT16(0, buf.head);
}

void test_circural_buffer_CBufPushReturnsFullWhenWrittenToFull(void) {
  CBufStatus status;
  CBufType buf;
  CBufInit(&buf);
  for (int i = 0; i < BUF_SIZE; i++) {
    status = CBufPush(&buf, 0xB00B);
  }
  TEST_ASSERT_EQUAL(cbuffull, status);
}

void test_circural_buffer_CBufPushDontOverwriteWhenFull(void) {
  CBufStatus status;
  CBufType buf;
  CBufInit(&buf);
  CBufPush(&buf, 0xADA);
  for (int i = 0; i < BUF_SIZE; i++) {
    CBufPush(&buf, 0xB00B);
  }
  uint16_t read_val = 0;
  CBufPop(&buf, &read_val);
  TEST_ASSERT_EQUAL(0xADA, read_val);
}

void test_circural_buffer_CBufPushReturnsFullWhenFilled(void) {
  CBufStatus status;
  CBufType buf;
  CBufInit(&buf);
  CBufPush(&buf, 0xADA);
  for (int i = 0; i < BUF_SIZE - 2; i++) {
    CBufPush(&buf, 0xB00B);
  }
  status = CBufPush(&buf, 0xB00B);
  TEST_ASSERT_EQUAL(cbuffull, status);
}

void test_circural_buffer_TailLoopsAtTheEdges(void) {

  CBufType buf;
  CBufInit(&buf);
  CBufPush(&buf, 0xB00B);
  uint16_t destination;
  for (int i = 0; i < BUF_SIZE; i++) {
    CBufPush(&buf, 0xB00B);
    CBufPop(&buf, &destination);
  }
  TEST_ASSERT_EQUAL_UINT16(0, buf.tail);
}

void test_circural_buffer_PopReturnCbufokWhenRead(void) {
  CBufType buf;
  CBufStatus status;
  CBufInit(&buf);
  CBufPush(&buf, 0xB00B);
  CBufPush(&buf, 0xB00B);
  uint16_t destination;
  status = CBufPop(&buf, &destination);
  TEST_ASSERT_EQUAL(cbufok, status);
}

void test_circural_buffer_PopReturnCbufemptyWhenFullyRead(void) {
  CBufType buf;
  CBufStatus status;
  CBufInit(&buf);
  CBufPush(&buf, 0xB00B);
  uint16_t destination;
  status = CBufPop(&buf, &destination);
  TEST_ASSERT_EQUAL(cbufempty, status);
}

void test_circural_buffer_PopReturnCbufemptyWhenReadEmpty(void) {
  CBufType buf;
  CBufStatus status;
  CBufInit(&buf);
  uint16_t destination;
  status = CBufPop(&buf, &destination);
  TEST_ASSERT_EQUAL(cbufempty, status);
}

void test_circural_buffer_PopReturnWrittenVar(void) {
  CBufType buf;
  CBufStatus status;
  CBufInit(&buf);
  CBufPush(&buf, 0xB00B);
  uint16_t destination;
  status = CBufPop(&buf, &destination);
  TEST_ASSERT_EQUAL(0xB00B, destination);
}
#endif // TEST
