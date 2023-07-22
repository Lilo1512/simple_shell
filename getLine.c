#include "shell.h"
/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t i = 0;
size_t len_q = 0;
if (!*len) /* if nothing left in the buffer, fill it */
{
/*bfree((void **)info->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
i = getline(buf, &len_q, stdin);
#else
i = _getline(info, buf, &len_q);
#endif
if (i > 0)
{
if ((*buf)[i - 1] == '\n')
{
(*buf)[i - 1] = '\0'; /* remove trailing newline */
i--;
}
info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);
/* if (_strchr(*buf, ';')) is this a command chain? */
{
*len = i;
info->cmd_buf = buf;
}
}
}
return (i);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
static char *buf; /* the ';' command chain buffer */
static size_t a, k, len;
ssize_t i = 0;
char **buf_q = &(info->arg), *q;
_putchar(BUF_FLUSH);
i = input_buf(info, &buf, &len);
if (i == -1) /* EOF */
return (-1);
if (len) /* we have commands left in the chain buffer */
{
k = a; /* init new iterator to current buf position */
q = buf + a; /* get pointer for return */
check_chain(info, buf, &k, a, len);
while (k < len) /* iterate to semicolon or end */
{
if (is_chain(info, buf, &k))
break;
k++;
}
a = k + 1; /* increment past nulled ';'' */
if (a >= len) /* reached end of buffer? */
{
a = len = 0; /* reset position and length */
info->cmd_buf_type = CMD_NORM;
}
*buf_q = q; /* pass back pointer to current command position */
return (_strlen(q)); /* return length of current command */
}
*buf_q = buf; /* else not a chain, pass back buffer from _getline() */
return (i); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @a: size
 *
 * Return: i
 */
ssize_t read_buf(info_t *info, char *buf, size_t *a)
{
ssize_t i = 0;
if (*a)
return (0);
i = read(info->readfd, buf, READ_BUF_SIZE);
if (i >= 0)
*a = i;
return (i);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @est: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: c
 */
int _getline(info_t *info, char **est, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t a, len;
size_t n;
ssize_t i = 0, c = 0;
char *q = NULL, *new_q = NULL, *e;
q = *est;
if (q && length)
c = *length;
if (a == len)
a = len = 0;
i = read_buf(info, buf, &len);
if (i == -1 || (i == 0 && len == 0))
return (-1);
e = _strchr(buf + i, '\n');
n = e ? 1 + (unsigned int)(e - buf) : len;
new_q = _realloc(q, c, c ? c + n : n + 1);
if (!new_q) /* MALLOC FAILURE! */
return (q ? free(q), -1 : -1);
if (c)
_strncat(new_q, buf + a, n - a);
else
_strncpy(new_q, buf + a, n - a + 1);
c += n - a;
a = n;
q = new_q;
if (length)
*length = c;
*est = q;
return (c);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
