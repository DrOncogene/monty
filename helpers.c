#include "monty.h"

int define_opcodes(void)
{
	char *opnames[3] = {"push", "pall", NULL};
	int i;

	void (*opfuncs[])(stack_t **, unsigned int) = {push_func, pall_func};
	i = 0;
	opcodes = malloc(sizeof(instruction_t *) * 2);
	while (opnames[i])
	{
		opcodes[i] = malloc(sizeof(instruction_t));
		if (opcodes[i] == NULL)
			return (-1);

		opcodes[i]->opcode = opnames[i];
		opcodes[i]->f = opfuncs[i];
		i++;
	}
	return (0);
}

char *get_arg_at(unsigned int line_num)
{
	unsigned int i;
	size_t n;
	char *arg, *code, *code_h, *saveptr;

	n = 0;
	code = NULL;
	rewind(byte_file);
	for (i = 0; i <= line_num; i++)
	{
		code = NULL;
		if (getline(&code, &n, byte_file) == -1)
		{
			free(code);
			return (NULL);
		}

		if (i < line_num)
			free(code);
	}
	code_h = code;
	saveptr = NULL;
	strtok_r(code, " ", &saveptr);
	arg = strtok_r(NULL, " ", &saveptr);
	if (arg)
		arg = strdup(arg);
	free(code_h);

	return (arg);
}

void free_all(void)
{
	int i;
	stack_t *stack_hold;

	fclose(byte_file);

	for (i = 0; i < 2; i++)
		free(opcodes[i]);
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

int check_int(char *str)
{
	size_t i, len_str;

	i = 0;
	len_str = strlen(str);
	if (*(str + len_str - 1) == '\n')
		len_str--;

	while (str[i] && i < len_str)
	{
		if (str[i] - '0' < 0 || str[i] - '0' > 9)
			return (-1);

		i++;
	}

	return (0);
}
