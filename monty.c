#include "monty.h"

stack_t *stack = NULL;
FILE *byte_file = NULL;
instruction_t **opcodes = NULL;
int next_opcode(unsigned int line_num);
int main(int argc, char **argv)
{
	unsigned int line_num;
	int index;

	if (argc != 2)
	{
		dprintf(2, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	byte_file = fopen(argv[1], "r");
	if (byte_file == NULL)
	{
		dprintf(2, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	define_opcodes();
	line_num = 0;
	while ((index = next_opcode(line_num)) != -1)
	{
		(opcodes[index]->f)(&stack, line_num);
		line_num++;
	}
	free_all();

	return (0);
}

int next_opcode(unsigned int line_num)
{
	unsigned int i, match;
	size_t n;
	char *code, *code_h, *saveptr, *opnames[] = {"push", "pall", NULL};

	n = 0;
	rewind(byte_file);
	for (i = 0; i <= line_num; i++)
	{
		code = NULL;
		if (getline(&code, &n, byte_file) == -1)
		{
			free(code);
			return (-1);
		}
		if (i < line_num)
			free(code);
	}
	code_h = code;
	saveptr = NULL;
	code = strtok_r(code, " ", &saveptr);
	i = 0;
	while (opnames[i])
	{
		match = 0;
		if (strncmp(code, opnames[i], strlen(opnames[i])) == 0)
		{
			free(code_h);
			match = 1;
			break;
		}
		i++;
	}

	if (match == 1)
		return (i);
	if (match == 0)
	{
		if (*(code + strlen(code) - 1) == '\n')
			code[strlen(code) - 1] = '\0';
		dprintf(2, "L%u: unknown instruction %s\n", line_num + 1, code);
		free(code_h);
		free_all();
		exit(EXIT_FAILURE);
	}

	free(code_h);
	return (-1);
}
