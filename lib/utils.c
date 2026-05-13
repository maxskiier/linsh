#include <string.h>

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