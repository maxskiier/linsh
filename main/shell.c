#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#include <shell_defines.h>
#include <shell_sig.h>
#include <shell_utils.h>

char *buf;
char **tokbuf;

int main(int argc, char **argv) {
	buf = calloc(1, COMMAND_SIZE_MAX);
	tokbuf = calloc(1, COMMAND_SIZE_MAX);
	struct passwd *pw = getpwuid(getuid());
	char is_root = '$';

	if (!pw) {
		puts("error loading passwd");
		exit(-1);
	}

	if (!strcmp(pw->pw_name, "root"))
		is_root = '#';

	signal(SIGINT, sigint_hdlr);

	/* Allocate space for the pointer array */
	for (int i = 1; i * sizeof(char *) < COMMAND_SIZE_MAX; i++)
		tokbuf[i-1] = calloc(1, COMMAND_SIZE_MAX / sizeof(char *));

	while (true) {
		/* Get input here */
		printf("%s %c ", getcwd(buf, COMMAND_SIZE_MAX-1), is_root);
		fgets(buf, COMMAND_SIZE_MAX-1, stdin);
		strtok(buf, "\n");

		/* Let's get tokens and check for our builtins */
		get_str_token(buf);

		if (!strcmp(buf, "exit"))
			exit(0);

		if (!strcmp(tokbuf[0], "cd")) {
			if (tokbuf[1]) {
				if (!strcmp(tokbuf[1], "~"))
					chdir(getenv("HOME"));
				chdir(tokbuf[1]);
			} else
				puts("cd: missing operand\n");
			continue;
		}

		if (!strcmp(tokbuf[0], "clear")) {
			/* Clear screen with this godforsaken escape sequence */
			printf("\e[1;1H\e[2J");
			continue;
		}

		pid_t pid = fork();
		if (!pid) {
			execvp(tokbuf[0], (char * const *)tokbuf);
			perror(strerror(errno));
		}
		wait(NULL);
	}
	
}