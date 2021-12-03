#include "monty.h"

int push_func(stack_t **stack, unsigned int line_num, ...)
{
	char *data;
	stack_t *new;
	va_list ap;

	va_start(ap, line_num);
	data = va_arg(ap, char *);
	va_end(ap);
	if (data == NULL || check_int(data) == -1)
	{
		free_all(*stack);
		return (500);
	}
	if (*stack == NULL)
	{
		*stack = malloc(sizeof(stack_t));
		if (*stack == NULL)
		{
			free_all(*stack);
			return (501);
		}
		(*stack)->n = atoi(data);
		(*stack)->prev = NULL;
		(*stack)->next = NULL;
	}
	else
	{
		new =  malloc(sizeof(stack_t));
		if (new == NULL)
		{
			free_all(*stack);
			return (501);
		}
		new->n = atoi(data);
		new->next = NULL;
		new->prev = *stack;
		*stack = new;
	}
	return (0);
}

int pall_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *current;


	current = *stack;
	while (current)
	{
		printf("%d\n", current->n);
		current = current->prev;
	}
	return (0);
}
