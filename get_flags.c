#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string that print the arguments
 * @y: take parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *y)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int z, curr_y;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_y = *y + 1; format[curr_y] != '\0'; curr_y++)
	{
		for (z = 0; FLAGS_CH[z] != '\0'; z++)
			if (format[curr_y] == FLAGS_CH[z])
			{
				flags |= FLAGS_ARR[z];
				break;
			}

		if (FLAGS_CH[z] == 0)
			break;
	}

	*y = curr_y - 1;

	return (flags);
}
