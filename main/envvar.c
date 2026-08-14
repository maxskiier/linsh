#include <stdlib.h>

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
