#include "parser.h"

ParserStatus ParserTakeLine(CBufType *buf, char *destination)
{
	uint8_t i = 0;
	uint16_t Temp = 0;
	do
	{
	CBufPop(buf, &Temp);
			if(Temp == EOL)
				{
					destination[i] = '\0';
				}
				else
				{
					destination[i] = Temp;
				}
			i++;
	}
	while(Temp != EOL);
}
