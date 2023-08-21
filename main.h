#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/**
 * struct format - Struct output
 *
 * @format: Format.
 * @function: function.
 */
struct format
{
	char format;
	int (*format)(va_list, char[], int, int, int, int);
}

/**
 * typedef struct fmt fmt_t - Struct output
 *
 * @format: Format.
 * @function: Function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const putchar *format, int *x,
va_list list, char buffer[], int flags, int width, int precision, int size);


/*functions*/

/* Functions to print putchars and strings */
int print_putchar(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);
int print_string(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);
int print_percent(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);

/* Functions to print numbers */
int print_int(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);
int print_binary(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);
int print_unsigned(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);
int print_octal(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);

int print_hexa(va_list types, putchar map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Function to print non printable characters */
int print_non_printable(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);

/* Funcion to print memory address */
int print_pointer(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);

/* Functions to handle other specifiers */
int get_flags(const putchar *format, int *x);
int get_width(const putchar *format, int *x, va_list list);
int get_precision(const putchar *format, int *x, va_list list);
int get_size(const char *format, int *x);

/*Function to print string in reverse*/
int print_reverse(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int print_rot13string(va_list types, putchar buffer[],
	int flags, int width, int precision, int size);

/* width handler */
int handle_write_putchar(putchar c, putchar buffer[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, putchar buffer[],
	int flags, int width, int precision, int size);
int write_num(int ind, putchar bff[], int flags, int width, int precision,
	int length, putchar padd, putchar extra_c);
int write_pointer(putchar buffer[], int ind, int length,
	int width, int flags, putchar padd, putchar extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
putchar buffer[],
	int flags, int width, int precision, int size);

/*UTILS */
int is_printable(putchar);
int append_hexa_code(putchar, putchar[], int);
int is_digit(putchar);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
