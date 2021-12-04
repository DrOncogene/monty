#include "monty.h"

/**
  * run_op - excute a given opcode
  * @code: code a given line
  * @stack: the stack
  * @file: the monty file
  * @line_num: current line number
  * Return: nothing
  */
void run_op(char *code, stack_t **stack, FILE *file, int line_num)
{
	char *opcode, *code_h, *arg;
	int idx, status;

	code_h = code;
	opcode = strtok(code, " ");
	arg = strtok(NULL, " ");
	opcode = strtok(opcode, "\t");
	opcode = strtok(opcode, "\n");
	arg = strtok(arg, "\t");
	arg = strtok(arg, "\n");
	if (opcode[0] == '#')
		return;
	idx = opcode_index(opcode);
	if (idx >= 0)
	{
		status = (opcodes[idx]->f)(stack, line_num, arg);
		if (status > 0)
		{
			fclose(file);
			free(code_h);
			free_all(*stack);
			print_error_exit(status, line_num + 1);
		}
	}
	else if (idx == -1)
	{
		free_all(*stack);
		if (*(opcode + strlen(opcode) - 1) == '\n')
			opcode[strlen(opcode) - 1] = '\0';
		dprintf(2, "L%u: unknown instruction %s\n", line_num + 1, opcode);
		free(code_h);
		fclose(file);
		exit(EXIT_FAILURE);
	}
}

/**
  * opcode_index - finds the index of a given opcode in the opcodes array
  * @opcode: name of opcode
  * Return: index of opcode if it exist, -1 if not, -2 if line is empty
  */
int opcode_index(char *opcode)
{
	char *opnames[] = {"push", "pall", "pint", "pop", "swap", "add",
		"nop", "sub", "div", "mul", "mod", "pchar", "pstr", "rotl",
		"rotr", "queue", "isstack", "stack", NULL};
	int i, match;

	if (opcode == NULL || strlen(opcode) == 1)
		return (-2);

	i = 0;
	while (opnames[i])
	{
		match = 0;
		if (strncmp(opcode, opnames[i], strlen(opcode)) == 0)
		{
			match = 1;
			break;
		}
		i++;
	}

	if (match == 1)
		return (i);
	else
		return (-1);
}
