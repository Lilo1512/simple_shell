#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @c: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *c)

{
int a = 0;
unsigned long int result = 0;
if (*c == '+')
c++;  /* TODO: why does this make main return 255? */
for (a = 0; c[a] != '\0'; a++)
{
if (c[a] >= '0' && c[a] <= '9')
{
result *= 10;
result += (c[a] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
_eputs(info->fname);
_eputs(": ");
print_d(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(estr);
}
/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int a, count = 0;
unsigned int _abs_, current;
if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (a = 1000000000; a > 1; a /= 10)
{
if (_abs_ / a)
{
__putchar('0' + current / a);
count++;
}
current %= a;
}
__putchar('0' + current);
count++;
return (count);
}
/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *est;
unsigned long s = num;
if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
s = -num;
sign = '-';
}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
est = &buffer[49];
*est = '\0';
do {
*--est = array[s % base];
s /= base;
} while (s != 0);
if (sign)
*--est = sign;
return (est);
}
/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
int a;
for (a = 0; buf[a] != '\0'; a++)
if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
{
buf[a] = '\0';
break;
}
}
