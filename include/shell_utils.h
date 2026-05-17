#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H

#include <stddef.h>

void get_str_token(char *str);

char *get_last_dir(char *buf, char *cwd);

void free_helper(char **ptr);

char *int_get_ptr(int (*func)(char *ptr, size_t size), char *ptr, size_t size);

#endif /* SHELL_UTILS_H */
