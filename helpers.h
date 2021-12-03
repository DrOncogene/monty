#ifndef HELPERS_H
#define HELPERS_H
#include <ctype.h>
int define_opcodes(void);
void print_error_exit(int error_num, unsigned int line_num);
void free_all(stack_t *);
int check_int(char *str);

#endif
