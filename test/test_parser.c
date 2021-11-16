#ifdef TEST

#include "unity.h"
#include "circural_buffer.h"
#include "parser.h"
CBufType buf;
char *destination = "";
char *str = "Banana\0";

void FillBufferWithString(CBufType *buf, char *str)
{
	int i=0;
	while(str[i] != '\0')
	{
		CBufPush(buf, str[i]);
		i++;
	}
}

void setUp(void) {

CBufInit(&buf);

}
void tearDown(void) {}

void test_parser_TakeLineTakesWholeLine(void) {

	ParserTakeLine(&buf, destination);
	TEST_ASSERT_EQUAL_STRING(str, destination);

}

#endif // TEST
