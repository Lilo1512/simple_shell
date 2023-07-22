#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
int a, k, n, o, numwords = 0;
char **c;
if (str == NULL || str[0] == 0)
return (NULL);
if (!d)
d = " ";
for (a = 0; str[a] != '\0'; a++)
if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
numwords++;
if (numwords == 0)
return (NULL);
c = malloc((1 + numwords) *sizeof(char *));
if (!c)
return (NULL);
for (a = 0, k = 0; k < numwords; k++)
{
while (is_delim(str[a], d))
a++;
n = 0;
while (!is_delim(str[a + n], d) && str[a + n])
n++;
c[k] = malloc((n + 1) * sizeof(char));
if (!c[k])
{
for (n = 0; n < k; n++)
free(c[n]);
free(c);
return (NULL);
}
for (o = 0; o < n; o++)
c[k][o] = str[a++];
c[k][o] = 0;
}
c[k] = NULL;
return (c);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
int a, k, n, o, numwords = 0;
char **c;
if (str == NULL || str[0] == 0)
return (NULL);
for (a = 0; str[a] != '\0'; a++)
if ((str[a] != d && str[a + 1] == d) ||
(str[a] != d && !str[a + 1]) || str[a + 1] == d)
numwords++;
if (numwords == 0)
return (NULL);
c = malloc((1 + numwords) *sizeof(char *));
if (!c)
return (NULL);
for (a = 0, k = 0; k < numwords; k++)
{
while (str[a] == d && str[a] != d)
a++;
n = 0;
while (str[a + n] != d && str[a + n] && str[a + n] != d)
n++;
c[k] = malloc((n + 1) * sizeof(char));
if (!c[k])
{
for (n = 0; n < n; n++)
free(c[n]);
free(c);
return (NULL);
}
for (o = 0; o < n; o++)
c[k][o] = str[a++];
c[k][o] = 0;
}
c[k] = NULL;
return (c);
}
