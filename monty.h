#ifndef MONTY_H
#define MONTY_H
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE _DEFAULT_SOURCE
#include "opcodes.h"
#include "helpers.h"

extern instruction_t **opcodes;
void run_op(char *, stack_t **, FILE *, int);
int opcode_index(char *opcode);

#endif
