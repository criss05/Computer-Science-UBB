#include "FAID.h"
#include <ctype.h>
#include <string.h>

typedef enum {
	Q0,
	QSymb,
	Error
} State;

bool check_identifier(const char* token)
{
	State state = Q0;
	int i = 0;
	char c;
	char symbols[] = "_,.!?'\":@#$^&<>/\\";

	while ((c = token[i]) != '\0') {
		switch (state) {
		case Q0:
			if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
				state = QSymb;
			else state = Error;
			break;

		case QSymb:
			if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || isdigit(c) || c == '_')
				state = QSymb;
			else
				state = Error;
			break;

		default:
			state = Error;
		}

		if (state == Error)
			return false;
		i++;
	}
	return (state == QSymb);
}
