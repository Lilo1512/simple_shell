#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @paths: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *paths)
{
struct stat st;

(void)info;
if (!paths || stat(paths, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int a = 0, n = 0;
for (n = 0, a = start; a < stop; a++)
if (pathstr[a] != ':')
buf[n++] = pathstr[a];
buf[n] = 0;
return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int a = 0, curr_pos = 0;
char *paths;
if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[a] || pathstr[a] == ':')
{
paths = dup_chars(pathstr, curr_pos, a);
if (!*paths)
_strcat(paths, cmd);
else
{
_strcat(paths, "/");
_strcat(paths, cmd);
if (is_cmd(info, paths))
return (paths);
if (!pathstr[a])
break;
curr_pos = a;
}
a++;
}
return (NULL);
}
}
