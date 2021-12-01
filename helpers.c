#include "monty.h"

int define_push(void)
{
	push = malloc(sizeof(instruction_t));
	if (push == NULL)
		return (-1);

	push->opcode = "push";
	push->f = push_func;

	return (0);
}

int define_pall(void)
{
	pall = malloc(sizeof(instruction_t));
	if (pall == NULL)
		return (-1);

	pall->opcode = "pall";
	pall->f = pall_func;

	return (0);
}


int check_int(char *str)
{
	size_t i;

	i = 0;
	while (str[i] && i < strlen(str) - 1)
	{
		if (str[i] + '0' < '0' || str[i] + '0' > '9')
			return (-1);

		i++;
	}

	return (0);
}

size_t len_stack(void)
{
	size_t len;

	len = 0;

	return (len);
}
