#include "monty.h"

void push_func(stack_t **stack, unsigned int line_num)
{
	char *data;
	stack_t *new;

	data = get_arg_at(line_num);
	if (data == NULL)
	{
		dprintf(2, "L%u: usage: push integer\n", line_num + 1);
		exit(EXIT_FAILURE);
	}

	if (*stack == NULL)
	{
		*stack = malloc(sizeof(stack_t));
		(*stack)->n = atoi(data);
		(*stack)->prev = NULL;
		(*stack)->next = NULL;
	}
	else
	{
		new =  malloc(sizeof(stack_t));
		new->n = atoi(data);
		new->next = NULL;
		new->prev = *stack;
		*stack = new;
	}
}

void pall_func(stack_t **stack, unsigned int line_num __attribute__((unused)))
{
	stack_t *current;


	current = *stack;
	while (current)
	{
		printf("%d\n", current->n);
		current = current->prev;
	}
}
