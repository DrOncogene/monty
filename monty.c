#include "monty.h"

stack_t *stack = NULL;
FILE *byte_file = NULL;
instruction_t *push = NULL;
instruction_t *pall = NULL;

int main(int argc, char **argv)
{
	char *code, *opnames[] = {"push", "pall\n"};
	unsigned int line_num, i;
	size_t n;
	ssize_t m;
	instruction_t *opcodes[2];

	if (argc != 2)
	{
		dprintf(2, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	define_push();
	define_pall();
	opcodes[0] = push;
	opcodes[1] = pall;
	byte_file = fopen(argv[1], "r");
	if (byte_file == NULL)
	{
		dprintf(2, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	n = 0;
	line_num = 0;

	while ((m = getline(&code, &n, byte_file)) >= 0)
	{
		for (i = 0; i < 2; i++)
		{
			if (strcmp(strtok(strdup(code), " "), opnames[i]) == 0)
			{
				(opcodes[i]->f)(&stack, line_num);
			}
		}
		line_num++;
	}
	return (0);
}

char *get_arg_at(unsigned int line_num)
{
	unsigned int i;
	size_t n;
	char *arg, *code, *saveptr;

	n = 0;
	rewind(byte_file);
	for (i = 0; i <= line_num; i++)
	{
		if (getline(&code, &n, byte_file) == -1)
			return (NULL);
	}
	saveptr = NULL;
	strtok_r(code, " ", &saveptr);
	arg = strtok_r(NULL, " ", &saveptr);

	return (arg);
}
