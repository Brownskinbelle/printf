#include "main.h"
/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char extra_a = 0, pad = ' ';
	int index = BUFF_SIZE - 2, len = 2, pad_start = 1;
	unsigned long numb_addres;
	char map_to[] = "0123456789abcdef";
	void *addres = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addres == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	numb_addres = (unsigned long)addres;

	while (numb_addres > 0)
	{
		buffer[index--] = map_to[numb_addres % 16];
		numb_addres /= 16;
		len++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		extra_a = '+', len++;
	else if (flags & F_SPACE)
		extra_a = ' ', len++;
	index++;
	/*return (write(1, &buffer[b], BUFF_SIZE - b - 1));*/
	return (write_pointer(buffer, index, len, width,
				flags, pad, extra_a, pad_start));
}
/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = 0, ofset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + ofset] = str[i];
		else
			ofset += append_hexa_code(str[i], buffer, i + ofset);
		i++;
	}
	buffer[i + ofset] = '\0';
	return (write(1, buffer, i + ofset));
}
/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *str;
	int i, counts = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char y = str[i];

		write(1, &y, 1);
		counts++;
	}
	return (counts);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char m;
	char *str;
	unsigned int i, j;
	int counts = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				m = out[j];
				write(1, &m, 1);
				counts++;
				break;
			}
		}
		if (!in[j])
		{
			m = str[i];
			write(1, &m, 1);
			counts++;
		}
	}
	return (counts);
}

