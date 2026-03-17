#include "dprint.h"

void dprint(
	void*				buf__,
	int					len__
	)
{
	char* char_ptr = (char*)buf__;
	char* value_ptr = (char*)buf__;

	for (int i = 0; i < len__; i++)
	{
		printf("%02X ", *value_ptr++);
		printf("%c ", *char_ptr++);
	}
}
