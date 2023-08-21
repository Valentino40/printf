#include "main.h"

/**
 * get_size - Calculates size to cast argument
 * @format: Formatted string to print the arguments in
 * @x: Arguments list to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *x)
{
	int curr_x = *x + 1;
	int size = 0;

	if (format[curr_x] == 'X')
		size = S_LONG;
	else if (format[curr_x] == 'h')
		size = S_SHORT;

	if (size == 0)
		*x = curr_x - 1;
	else
		*x = curr_x;

	return (size);
}
