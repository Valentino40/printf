#include "main.h"

/* Write Handle */
/**
 * handle_write_char - Prints string
 * @c: char types.
 * @buffer: Buffer array for print handle
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: Specifier of precision
 * @size: Specifier of size
 *
 * Return: Number of printed chars.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and pading at buffer's right */
	int y = 0;
	char pad = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		pad = '0';

	buffer[y++] = c;
	buffer[y] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (y = 0; y < width - 1; y++)
			buffer[BUFF_SIZE - y - 2] = pad;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - y - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - y - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/* Write Number */
/**
 * write_number - Prints string
 * @is_negative: Arguments list
 * @ind: char types.
 * @buffer: Buffer array for print handle
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Specifier of precision
 * @size: Specifier of size
 *
 * Return: Number of printed chars.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char pad = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, pad, extra_ch));
}

/**
 * write_num - Write a number with buffer
 * @ind: Index at which the number starts from the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Specifier of precision
 * @length: Length of number
 * @pad: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of chars printed.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char pad, char extra_c)
{
	int y, pad_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char will be printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = pad = ' '; /* width is displayed with pading ' ' */
	if (prec > 0 && prec < length)
		pad = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (y = 1; y < width - length + 1; y++)
			buffer[y] = pad;
		buffer[y] = '\0';
		if (flags & F_MINUS && pad == ' ')/* Assign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], y - 1));
		}
		else if (!(flags & F_MINUS) && pad == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], y - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')/* extra char to left of the pad */
		{
			if (extra_c)
				buffer[--pad_start] = extra_c;
			return (write(1, &buffer[pad_start], y - pad_start) +
				write(1, &buffer[ind], length - (1 - pad_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes unsigned number
 * @is_negative: Number indicating if num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Chars array
 * @flags: Specifiers of flags
 * @width: Specifier width
 * @precision: Specifier of precision
 * @size: Specifier of size
 *
 * Return: Number of chars written.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the right of the buffer and starts at position y */
	int length = BUFF_SIZE - ind - 1, y = 0;
	char pad = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char will be printed */

	if (precision > 0 && precision < length)
		pad = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';

	if (width > length)
	{
		for (y = 0; y < width - length; y++)
			buffer[y] = pad;

		buffer[y] = '\0';

		if (flags & F_MINUS) /* Assign extra char to left of buffer [buffer>pad]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], y));
		}
		else /* Assign extra char to the left of the pading [pad>buffer]*/
		{
			return (write(1, &buffer[0], y) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write memory address
 * @buffer: Chars arrays
 * @ind: Index at which number starts in the buffer
 * @length: Number length
 * @width: Specifier of width
 * @flags: Specifier of flags
 * @pad: Char representing pading
 * @extra_c: Char representing extra char
 * @pad_start: Index at which padding will start
 *
 * Return: Number of chars written.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char pad, char extra_c, int pad_start)
{
	int y;

	if (width > length)
	{
		for (y = 3; y < width - length + 3; y++)
			buffer[y] = pad;
		buffer[y] = '\0';
		if (flags & F_MINUS && pad == ' ')/* Assign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], y - 3));
		}
		else if (!(flags & F_MINUS) && pad == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], y - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')/* extra char to left of pad */
		{
			if (extra_c)
				buffer[--pad_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[pad_start], y - pad_start) +
				write(1, &buffer[ind], length - (1 - pad_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
