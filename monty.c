#include "monty.h"

stack_t *stack = NULL;
FILE *byte_file = NULL;
instruction_t **opcodes = NULL;

int main(int argc, char **argv)
{
	char *code, *code_h, *curr_code, *opnames[] = {"push", "pall"};
	unsigned int line_num, i;
	size_t n;
	ssize_t m;

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
	n = 0;
	line_num = 0;
	code = NULL;
	while ((m = getline(&code, &n, byte_file)) >= 0)
	{
		code_h = code;
		curr_code = strtok(code, " ");
		for (i = 0; i < 2; i++)
		{
			if (strncmp(curr_code, opnames[i], strlen(opnames[i])) == 0)
			{
				free(code_h);
				(opcodes[i]->f)(&stack, line_num);
				break;
			}
		}
		code = NULL;
		line_num++;
	}
	free(code);
	free_all();
	return (0);
}
