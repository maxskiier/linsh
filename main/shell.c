#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pwd.h>

#include <shell_defines.h>
#include <shell_sig.h>
#include <shell_utils.h>

char *buf;
char **tokbuf;

int main(int argc, char **argv) {
	buf = calloc(1, TOKEN_SIZE_MAX);
	tokbuf = calloc(LINSH_MAX_TOKENS, TOKEN_SIZE_MAX);
	struct passwd *pw = getpwuid(getuid());
	char is_root = '=';
	bool is_loginsh = false;
	__attribute__((cleanup(free_helper))) char *path = malloc(TOKEN_SIZE_MAX);
	__attribute__((cleanup(free_helper))) char *tmp = malloc(TOKEN_SIZE_MAX);

	if (!strcmp(argv[0], "-linsh"))
		is_loginsh = true;
	else if (argc > 1 && !strcmp(argv[1], "--login"))
		is_loginsh = true;

	if (!pw) {
		puts("error loading passwd");
		exit(-1);
	}

	if (!strcmp(pw->pw_name, "root"))
		is_root = '#';

	signal(SIGINT, sigint_hdlr);

	/* Allocate space for the pointer array */
	for (int i = 1; i * sizeof(char *) < TOKEN_SIZE_MAX; i++)
		tokbuf[i-1] = calloc(1, TOKEN_SIZE_MAX / sizeof(char *));

	while (true) {
start:
		memset(buf, 0, TOKEN_SIZE_MAX);
		/* Get input here */
		printf("[%s@%s %s] %c> ", pw->pw_name, int_get_ptr(gethostname, buf, TOKEN_SIZE_MAX-1),
		       get_last_dir(path, getcwd(tmp, TOKEN_SIZE_MAX-1)), is_root);
		fgets(buf, TOKEN_SIZE_MAX-1, stdin);
		strtok(buf, "\n");
		int len = strlen(buf);
		for (int i = -len; i; i++) {
			if (buf[i+len] <= ' ')
				goto start;
			else
				break;
		}

		/* Let's get tokens and check for our builtins */
		get_str_token(buf);

		if (!strcmp(tokbuf[0], "exit")) {
			puts("exit");
			exit(0);
		}

		if (!strcmp(tokbuf[0], "logout")) {
			if (!is_loginsh) {
				puts("linsh: not a login shell");
				continue;
			}
			exit(0);
		}

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

		if (!strcmp(tokbuf[0], "exec"))
			execvp(tokbuf[1], (char * const *)tokbuf + sizeof(char *));

		pid_t pid = fork();
		if (!pid) {
			execvp(tokbuf[0], (char * const *)tokbuf);
			perror("linsh");
			exit(-1);
		}

		int status;
		waitpid(pid, &status, 0);
	}
	free(buf);
	free(tokbuf);
}
