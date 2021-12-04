#include "monty.h"

/**
  * push_func - function for push opcode
  * @stack: the monty stack
  * @line_num: the current line number
  * Return: 0 if successful, or an error num if not
  */
int push_func(stack_t **stack, unsigned int line_num, ...)
{
	char *data;
	stack_t *new;
	va_list ap;

	va_start(ap, line_num);
	data = va_arg(ap, char *);
	va_end(ap);
	if (data == NULL || check_int(data) == -1)
		return (500);

	if (*stack == NULL)
	{
		*stack = malloc(sizeof(stack_t));
		if (*stack == NULL)
			return (501);

		(*stack)->n = atoi(data);
		(*stack)->prev = NULL;
		(*stack)->next = NULL;
	}
	else
	{
		new =  malloc(sizeof(stack_t));
		if (new == NULL)
			return (501);

		new->n = atoi(data);
		new->next = NULL;
		new->prev = *stack;
		(*stack)->next = new;
		*stack = new;
	}
	return (0);
}


/**
  * pall_func - function for push opcode
  * @stack: the monty stack
  * @line_num: the current line number
  * Return: always 0
  */
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


/**
  * pint_func - function for push opcode
  * @stack: the monty stack
  * @line_num: the current line number
  * Return: 0 if successful, an error num otherwise
  */
int pint_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top;

	top = *stack;
	if (top == NULL)
		return (502);

	printf("%d\n", top->n);

	return (0);
}

/**
  * pop_func - function for push opcode
  * @stack: the monty stack
  * @line_num: the current line number
  * Return: 0 if successful, an error otherwise
  */
int pop_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top, *second_top;

	top = *stack;
	if (top == NULL)
		return (503);

	second_top = top->prev;
	if (second_top)
		second_top->next = NULL;

	free(top);
	*stack = second_top;

	return (0);
}

/**
  * swap_func - swaps the top two stack items
  * @stack: the monty stack
  * @line_num: current line number
  * Return: 0 if successful, an error num otherwise
  */
int swap_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top, *second_top, *third_top;

	top = *stack;
	if (top == NULL)
		return (504);

	second_top = top->prev;
	if (second_top == NULL)
		return (504);

	third_top = second_top->prev;
	if (third_top)
		third_top->next = top;
	top->prev = third_top;
	top->next = second_top;
	second_top->prev = top;
	second_top->next = NULL;
	*stack = second_top;

	return (0);
}

/**
  * add_func - adds the top two stack items
  * @stack: the monty stack
  * @line_num: current line number
  * Return: 0 if successful, an error num otherwise
  */
int add_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top, *second_top;
	int res;

	top = *stack;
	if (top == NULL)
		return (505);
	second_top = top->prev;
	if (second_top == NULL)
		return (505);

	res = top->n + second_top->n;
	second_top->n = res;
	second_top->next = NULL;
	free(top);
	*stack = second_top;

	return (0);
}

/**
  * nop_func - adds the top two stack items
  * @stack: the monty stack
  * @line_num: current line number
  * Return: always 0
  */
int nop_func(stack_t **stack, unsigned int line_num, ...)
{
	/* just gimmick */
	if (stack && line_num)
		return (0);
	return (0);
}

/**
  * sub_func - adds the top two stack items
  * @stack: the monty stack
  * @line_num: current line number
  * Return: 0 if successful, an error num otherwise
  */
int sub_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top, *second_top;
	int res;

	top = *stack;
	if (top == NULL)
		return (506);
	second_top = top->prev;
	if (second_top == NULL)
		return (506);

	res = second_top->n - top->n;
	second_top->n = res;
	second_top->next = NULL;
	free(top);
	*stack = second_top;

	return (0);
}

/**
  * div_func - adds the top two stack items
  * @stack: the monty stack
  * @line_num: current line number
  * Return: 0 if successful, an error num otherwise
  */
int div_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top, *second_top;
	int res;

	top = *stack;
	if (top == NULL)
		return (507);

	second_top = top->prev;
	if (second_top == NULL)
		return (507);

	if (top->n == 0)
		return (508);

	res = second_top->n / top->n;
	second_top->n = res;
	second_top->next = NULL;
	free(top);
	*stack = second_top;

	return (0);
}

/**
  * mul_func - adds the top two stack items
  * @stack: the monty stack
  * @line_num: current line number
  * Return: 0 if successful, an error num otherwise
  */
int mul_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top, *second_top;
	int res;

	top = *stack;
	if (top == NULL)
		return (509);
	second_top = top->prev;
	if (second_top == NULL)
		return (509);

	res = second_top->n * top->n;
	second_top->n = res;
	second_top->next = NULL;
	free(top);
	*stack = second_top;

	return (0);
}

/**
  * mod_func - adds the top two stack items
  * @stack: the monty stack
  * @line_num: current line number
  * Return: 0 if successful, an error num otherwise
  */
int mod_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top, *second_top;
	int res;

	top = *stack;
	if (top == NULL)
		return (510);

	second_top = top->prev;
	if (second_top == NULL)
		return (510);

	if (top->n == 0)
		return (508);

	res = second_top->n % top->n;
	second_top->n = res;
	second_top->next = NULL;
	free(top);
	*stack = second_top;

	return (0);
}

/**
  * pchar_func - function for push opcode
  * @stack: the monty stack
  * @line_num: the current line number
  * Return: 0 if successful, an error num otherwise
  */
int pchar_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top;

	top = *stack;
	if (top == NULL)
		return (511);

	if (isascii(top->n))
		printf("%c\n", top->n);
	else
		return (512);

	return (0);
}

/**
  * pstr_func - function for push opcode
  * @stack: the monty stack
  * @line_num: the current line number
  * Return: always 0
  */
int pstr_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top;

	top = *stack;
	if (top == NULL)
	{
		printf("\n");
		return (0);
	}

	while (top)
	{
		if (top->n == 0)
			break;
		if (isascii(top->n))
			printf("%c", top->n);
		else
			break;

		top = top->prev;
	}
	printf("\n");

	return (0);
}

/**
  * rotl_func - function for push opcode
  * @stack: the monty stack
  * @line_num: the current line number
  * Return: always 0
  */
int rotl_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top, *second_top, *last, *second_last;

	top = *stack;
	if (top == NULL)
		return (0);

	second_top = top->prev;
	if (second_top == NULL)
		return (0);

	last = second_top;
	while (last && last->prev)
		last = last->prev;

	second_last = last;
	last = second_last->prev;

	top->prev = NULL;
	if (last)
	{
		top->next = last;
		last->prev = top;
	}
	else if (second_last)
	{
		top->next = second_last;
		second_last->prev = top;
	}

	second_top->next = NULL;
	*stack = second_top;

	return (0);
}

/**
  * rotr_func - function for push opcode
  * @stack: the monty stack
  * @line_num: the current line number
  * Return: always 0
  */
int rotr_func(stack_t **stack, unsigned int line_num
		__attribute__((unused)), ...)
{
	stack_t *top, *last, *second_last;

	top = *stack;
	if (top == NULL)
		return (0);

	last = top->prev;
	while (last && last->prev)
		last = last->prev;

	if (last)
	{
		second_last = last->next;
		top->next = last;
		last->prev = top;
		last->next = NULL;
		second_last->prev = NULL;
		*stack = last;
	}

	return (0);
}
