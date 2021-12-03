#include "monty.h"
instruction_t **opcodes = NULL;

int main(int argc, char **argv)
{
	stack_t *stack = NULL;
	FILE *byte_file;
	char *opcode, *code, *code_h, *arg;
	size_t n;
	unsigned int line_num;
	int idx, status;

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
	code = NULL;
	n = 0;
	while (getline(&code, &n, byte_file) != -1)
	{
		code_h = code;
		opcode = strtok(code, " ");
		arg = strtok(NULL, " ");
		idx = opcode_index(opcode);
		if (idx != -1)
		{
			status = (opcodes[idx]->f)(&stack, line_num, arg);
			if (status > 0)
			{
				fclose(byte_file);
				free(code_h);
				free_all(stack);
				print_error_exit(status, line_num + 1);
			}
		}
		else
		{
			free_all(stack);
			if (*(opcode + strlen(opcode) - 1) == '\n')
				opcode[strlen(opcode) - 1] = '\0';
			dprintf(2, "L%u: unknown instruction %s\n", line_num + 1, opcode);
			free(code_h);
			fclose(byte_file);
			exit(EXIT_FAILURE);
		}
		free(code_h);
		code = NULL;
		line_num++;
	}
	free(code);
	free_all(stack);
	fclose(byte_file);

	return (0);
}

int opcode_index(char *opcode)
{
	char *opnames[] = {"push", "pall", "pint", "pop", NULL};
	int i, match;

	i = 0;
	while (opnames[i])
	{
		match = 0;
		if (strncmp(opcode, opnames[i], strlen(opnames[i])) == 0)
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
