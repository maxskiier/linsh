#include <stdlib.h>
#include <string.h>

#include <shell_utils.h>

void envar_parse_str(char **tok_str)
{
	int i = 0;

	while (tok_str[i]) {
		if (tok_str[i][0] == '$')
			tok_str[i] = getenv(&tok_str[i][1]);
		i++;
	}
}

void export_envvar(char **tok_str)
{
	int i = 0;

	while (tok_str[i]) {
		char *tmp_ptr = strchr(tok_str[i], '=');
		if (!tmp_ptr) {
			i++;
			continue;
		}

		putenv(tok_str[i]);
		i++;
	}
}
