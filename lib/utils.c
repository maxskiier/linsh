#include <limits.h>
#include <pwd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <shell_defines.h>
#include <shell_utils.h>

extern char **tokbuf;

void get_str_token(char *str) {
	char *tmp = strdup(str);
	int i = 1;

	tokbuf[0] = strtok(tmp, " ");
	do {
		tokbuf[i] = strtok(NULL, " ");
	} while (tokbuf[i++] && i < LINSH_MAX_TOKENS * TOKEN_SIZE_MAX / sizeof(char *));
}

char *get_last_dir(char *buf, char *cwd)
{
	if (!cwd)
		return NULL;
	if (!buf)
		buf = malloc(PATH_MAX);

	char *tmp = strrchr(cwd, '/');
	struct passwd *pw = getpwuid(getuid());
	__attribute__((cleanup(free_helper))) char *usr = malloc(TOKEN_SIZE_MAX);

	sprintf(usr, "/home/%s", pw->pw_name);

	if (!tmp)
		sprintf(buf, "%s", cwd);
	else if (!strcmp(usr, cwd))
		sprintf(buf, "%s", "~");
	else
		sprintf(buf, "%s", tmp+1);
	return buf;
}

void free_helper(char **ptr)
{
	if (!ptr)
		return;
	free(*ptr);
}

char *int_get_ptr(int (*func)(char *ptr, size_t size), char *ptr, size_t size)
{
	func(ptr, size);
	return ptr;
}
