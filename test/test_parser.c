#ifdef TEST

#include "unity.h"
#include "circural_buffer.h"
#include "parser.h"

CBufType buf;
char destination[30];
char *str = "Banana\nPotato\n\0";
char *expected = "Banana";
char *expected2 = "Potato";

void FillBufferWithString(CBufType *buf, char *str)
{
	int i=0;
	CBufStatus status = cbufok;
	while(str[i] != '\0')
	{
		status = CBufPush(buf, str[i]);
		i++;
	}
}

void setUp(void) {

CBufInit(&buf);

}

void tearDown(void) {}

void test_parser_TakeLineTakesWholeLine(void) {
	FillBufferWithString(&buf, str);
	ParserTakeLine(&buf, destination);
	TEST_ASSERT_EQUAL_STRING(expected, destination);
}

void test_parser_TakeLineTakesSecondWholeLine(void) {
	FillBufferWithString(&buf, str);
	ParserTakeLine(&buf, destination);
	ParserTakeLine(&buf, destination);
	TEST_ASSERT_EQUAL_STRING(expected2, destination);
}

#endif // TEST
