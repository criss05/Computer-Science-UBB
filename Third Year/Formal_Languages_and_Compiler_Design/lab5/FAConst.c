#include "FAConst.h"
#include <ctype.h>
#include <string.h>

typedef enum {
	Q0,
	QS,
	QZ,
	QD,
	QSymb,
	QQ,
	Error
} State;

bool check_constant(const char* token)
{
	State state = Q0;
	int i = 0;
	char c;
	char symbols[] = " _,.!?':@#$^&<>/\\";

	while ((c = token[i]) != '\0') {
		switch (state) {
		case Q0:
			if (c == '+' || c == '-')
				state = QS;
			else if (c == '0')
				state = QZ;
			else if (c >= '1' && c <= '9')
				state = QD;
			else if (c == '\"')
				state = QSymb;
			else state = Error;
			break;

		case QS:
			if (c >= '1' && c <= '9')
				state = QD;
			else state = Error;
			break;

		case QZ:
			state = Error;
			break;

		case QD:
			if (isdigit(c))
				state = QD;
			else
				state = Error;
			break;

		case QSymb:
			if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || strchr(symbols, c) || isdigit(c))
				state = QSymb;
			else if (c == '\"')
				state = QQ;
			else
				state = Error;
			break;

		case QQ:
			state = Error;
			break;

		default:
			state = Error;
		}

		if (state == Error)
			return false;
		i++;
	}
	return (state == QZ || state == QD ||state == QQ);
}
