#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @c: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *c)
{
int a = 0;
if (!c)
return (0);
while (*c++)
a++;
return (a);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s3: the first strang
 * @s4: the second strang
 *
 * Return: negative if s3 < s4, positive if s3 > s4, zero if s3 == s4
 */
int _strcmp(char *s3, char *s4)
{
while (*s3 && *s4)
{
if (*s3 != *s4)
return (*s3 - *s4);
s3++;
s4++;
}
if (*s3 == *s4)
return (0);
else
return (*s3 < *s4 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
char *ret = dest;
while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
