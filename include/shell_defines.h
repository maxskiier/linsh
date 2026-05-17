#ifndef SHELL_DEFINES_H
#define SHELL_DEFINES_H

#define TOKEN_SIZE_MAX 256
#define LINSH_MAX_TOKENS 128

#define CLEANUP(__f) __attribute__((cleanup(__f)))

#endif /* SHELL_DEFINES_H */
