#ifndef OPCODE_FUNC_H
#define OPCODE_FUNC_H
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	int (*f)(stack_t **, unsigned int, ...);
} instruction_t;

int push_func(stack_t **, unsigned int, ...);
int pall_func(stack_t **, unsigned int, ...);
int pint_func(stack_t **, unsigned int, ...);
int pop_func(stack_t **, unsigned int, ...);
int swap_func(stack_t **, unsigned int, ...);
int add_func(stack_t **, unsigned int, ...);
int nop_func(stack_t **, unsigned int, ...);
int sub_func(stack_t **, unsigned int, ...);
int div_func(stack_t **, unsigned int, ...);
int mul_func(stack_t **, unsigned int, ...);
int mod_func(stack_t **, unsigned int, ...);
int pchar_func(stack_t **, unsigned int, ...);
int pstr_func(stack_t **, unsigned int, ...);
int rotl_func(stack_t **, unsigned int, ...);
int rotr_func(stack_t **, unsigned int, ...);
int queue_mode(stack_t **, unsigned int, ...);
int stack_mode(stack_t **, unsigned int, ...);

#endif
