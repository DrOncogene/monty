#include "monty.h"
instruction_t **opcodes = NULL;

/**
  * main - main function of the program
  * @argc: arg count
  * @argv: arg vector
  * Return: alway zero, exits if error occurs
  */
int main(int argc, char **argv)
{
	stack_t *stack = NULL;
	FILE *byte_file;
	char *code, *code_h;
	size_t n;
	unsigned int line_num;
	int status;

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

	status = define_opcodes();
	if (status > 0)
		print_error_exit(status, 0);
	line_num = 0;
	code = NULL;
	n = 0;
	while (getline(&code, &n, byte_file) != -1)
	{
		code_h = code;
		run_op(code, &stack, byte_file, line_num);
		free(code_h);
		code = NULL;
		line_num++;
	}
	free(code);
	free_all(stack);
	fclose(byte_file);

	return (0);
}
