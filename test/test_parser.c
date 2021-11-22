#ifdef TEST

#include "circural_buffer.h"
#include "parser.h"
#include "unity.h"
#include <stdlib.h>

#define COUNT_OF(arr) (sizeof(arr) / sizeof(0 [arr]))

CBufType buf;
ParserStatus status;
char take_line_destination[10];
char *after_take_line = take_line_destination + 11;
char *str = "H#100\nD#100\n\0";
char *no_eol_string = "0123456789ABCDEFGH";
char *expected = "H#100";
char *expected2 = "D#100";
char *expected_handshake_type_str = "H";
char *expected_data = "100";
char parsed_text[8];
char *after_parsed_text = parsed_text + 9;

void FillBufferWithString(CBufType *buf, char *str) {
  int i = 0;
  CBufStatus status = cbufok;
  while (str[i] != '\0') {
    status = CBufPush(buf, str[i]);
    i++;
  }
}

void setUp(void) {

  CBufInit(&buf);
  FillBufferWithString(&buf, str);
  status = parsererror;
}

void tearDown(void) {}

void test_parser_DontHangWhenNoNl(void) {

  CBufInit(&buf); // To flush the buffer
  FillBufferWithString(&buf, no_eol_string);
  ParserTakeLine(&buf, take_line_destination, COUNT_OF(take_line_destination));
  TEST_PASS_MESSAGE("Didn't hang on lack of new line.");
}

void test_parser_TakeLineReturnsParserok(void) {

  status = ParserTakeLine(&buf, take_line_destination,
                          COUNT_OF(take_line_destination));
  TEST_ASSERT_EQUAL(parserok, status);
}

void test_parser_TakelineNotOverflow(void) {

  *after_take_line = 8;
  CBufInit(&buf); // To flush the buffer
  FillBufferWithString(&buf, no_eol_string);
  status = ParserTakeLine(&buf, take_line_destination,
                          COUNT_OF(take_line_destination));
  TEST_ASSERT_EQUAL(8, *after_take_line);
}

void test_parser_TakelineReturnOverflowed(void) {
  *after_take_line = 8;
  CBufInit(&buf); // To flush the buffer
  FillBufferWithString(&buf, no_eol_string);
  status = ParserTakeLine(&buf, take_line_destination,
                          COUNT_OF(take_line_destination));
  TEST_ASSERT_EQUAL(parseroverflowed, status);
}

void test_parser_TakeLineTakesWholeLine(void) {

  ParserTakeLine(&buf, take_line_destination, COUNT_OF(take_line_destination));
  TEST_ASSERT_EQUAL_STRING(expected, take_line_destination);
}

void test_parser_TakeLineTakesSecondWholeLine(void) {
  ParserTakeLine(&buf, take_line_destination, COUNT_OF(take_line_destination));
  ParserTakeLine(&buf, take_line_destination, COUNT_OF(take_line_destination));
  TEST_ASSERT_EQUAL_STRING(expected2, take_line_destination);
}

void test_parser_ParseReturnParserok(void) {

  ParserTakeLine(&buf, take_line_destination, COUNT_OF(take_line_destination));
  status = ParserParse(take_line_destination, parsed_text, false,
                       COUNT_OF(parsed_text));
  TEST_ASSERT_EQUAL(parserok, status);
}

void test_parser_ParseReturnCorrectTransactionType(void) {

  ParserTakeLine(&buf, take_line_destination, COUNT_OF(take_line_destination));
  status = ParserParse(take_line_destination, parsed_text, false,
                       COUNT_OF(parsed_text));
  TEST_ASSERT_EQUAL_STRING(expected_handshake_type_str, parsed_text);
}

void test_parser_ParseReturnCorrectValue(void) {

  ParserTakeLine(&buf, take_line_destination, COUNT_OF(take_line_destination));
  ParserParse(take_line_destination, parsed_text, false, COUNT_OF(parsed_text));
  ParserParse(take_line_destination, parsed_text, true, COUNT_OF(parsed_text));

  TEST_ASSERT_EQUAL(100, atoi(parsed_text));
}

void test_parser_ParseDontOverwrite(void) {

  *after_parsed_text = 8;
  CBufInit(&buf); // To flush the buffer
  FillBufferWithString(&buf, no_eol_string);
  ParserTakeLine(&buf, take_line_destination, COUNT_OF(take_line_destination));
  ParserParse(take_line_destination, parsed_text, false, COUNT_OF(parsed_text));
  TEST_ASSERT_EQUAL(8, *after_parsed_text);
}

void test_parser_ParseReturnParseroverfloved(void) {

  *after_parsed_text = 8;
  CBufInit(&buf); // To flush the buffer
  FillBufferWithString(&buf, no_eol_string);
  ParserTakeLine(&buf, take_line_destination, COUNT_OF(take_line_destination));
  status = ParserParse(take_line_destination, parsed_text, false,
                       COUNT_OF(parsed_text));
  TEST_ASSERT_EQUAL(parseroverflowed, status);
}

#endif // TEST
