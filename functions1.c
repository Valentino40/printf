#include "main.h"

/* Print Unsigned Number */
/**
 * print_unsigned - Prints an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int y = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = (num % 10) + '0';
		num /= 10;
	}

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}

/* Print Unsigned Number in  Octal  */
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: List arguments
 * @buffer: Buffer array handle the print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int y = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[y--] = '0';

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}

/* Print Unsigned Number in Hexadecimal */
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: List arguments
 * @buffer: Buffer array handle the print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/* Print Unsigned Number in Upper Hexadecimal */
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: List  arguments
 * @buffer: Buffer array handle the print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/* Print Hexx Num In Lower or Upper */
/**
 * print_hexa - Prints hexadecimal number in lower or upper
 * @types: List arguments
 * @map_to: Array of values to map number
 * @buffer: Buffer array handle the print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int y = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[y--] = flag_ch;
		buffer[y--] = '0';
	}

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}
