#include "monty.h"

/**
  * define_opcodes - creates the array of opcodes structs
  * none
  * Return: 0 if successful, -1 otherwise
  */
int define_opcodes(void)
{
	char *opnames[] = {"push", "pall", "pint", "pop", "swap", "add",
		"nop", "sub", "div", "mul", "mod", "pchar", "pstr", "rotl",
		"rotr", "queue", "isstack", "stack", NULL};
	int i;

	int (*opfuncs[])(stack_t **, unsigned int, ...) = {push_func,
	pall_func, pint_func, pop_func, swap_func, add_func, nop_func,
	sub_func, div_func, mul_func, mod_func, pchar_func, pstr_func,
	rotl_func, rotr_func, queue_mode, NULL, stack_mode};
	i = 0;
	opcodes = malloc(sizeof(instruction_t *) * 19);
	while (opnames[i])
	{
		opcodes[i] = malloc(sizeof(instruction_t));
		if (opcodes[i] == NULL)
			return (501);

		opcodes[i]->opcode = opnames[i];
		opcodes[i]->f = opfuncs[i];
		i++;
	}
	opcodes[i] = NULL;
	return (0);
}

/**
  * free_all - frees the opcodes struct array and the stack
  * @stack: the monty stack
  * Return: nothing
  */
void free_all(stack_t *stack)
{
	int i;
	stack_t *stack_hold;

	i = 0;
	while (opcodes[i])
	{
		free(opcodes[i]);
		i++;
	}
	free(opcodes);

	while (stack)
	{
		if (stack->prev == NULL)
		{
			free(stack);
			break;
		}
		stack_hold = stack;
		stack = stack->prev;

		free(stack_hold);
	}
}

/**
  * check_int - checks if all letters in str are digits
  * @str: the string arg to an opcode
  * Return: 0 if successful, -1 otherwise
  */
int check_int(char *str)
{
	size_t i, len_str;

	i = 0;
	len_str = strlen(str);

	while (str[i] && i < len_str)
	{
		if (i == 0)
		{
			if (!(isdigit(str[i]) || str[i] == '+' || str[i] == '-'))
				return (-1);
		}
		else
		{
			if (!(isdigit(str[i])))
				return (-1);
		}

		i++;
	}

	return (0);
}

/**
  * print_error_exit - prints error messages and exit the program
  * @error_num: the error number
  * @line_num: the current line number
  * Return: nothing
  */
void print_error_exit(int error_num, unsigned int line_num)
{
	switch (error_num)
	{
		case 501:
			dprintf(2, "Error: malloc failed\n");
			break;
		case 500:
			dprintf(2, "L%u: usage: push integer\n", line_num);
			break;
		case 502:
			dprintf(2, "L%u: can't pint, stack empty\n", line_num);
			break;
		case 503:
			dprintf(2, "L%u: can't pop an empty stack\n", line_num);
			break;
		case 504:
			dprintf(2, "L%u: can't swap, stack too short\n", line_num);
			break;
		case 505:
			dprintf(2, "L%u: can't add, stack too short\n", line_num);
			break;
		case 506:
			dprintf(2, "L%u: can't sub, stack too short\n", line_num);
			break;
		case 507:
			dprintf(2, "L%u: can't div, stack too short\n", line_num);
			break;
		case 508:
			dprintf(2, "L%u: division by zero\n", line_num);
			break;
		case 509:
			dprintf(2, "L%u: can't mul, stack too short\n", line_num);
			break;
		case 510:
			dprintf(2, "L%u: can't mod, stack too short\n", line_num);
			break;
		case 511:
			dprintf(2, "L%u: can't pchar, stack empty\n", line_num);
			break;
		case 512:
			dprintf(2, "L%u: can't pchar, value out of range\n", line_num);
			break;
	}
	exit(EXIT_FAILURE);
}
