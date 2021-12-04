#include "monty.h"

/**
  * push_func - push a new value to the top/rear of stack/queue
  * @stack: the stack top or queue front
  * @line_num: the current line number
  * Return: 0 if successful, or an error num if not
  */
int push_func(stack_t **stack, unsigned int line_num, ...)
{
	char *data;
	stack_t *new, *rear;
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
		return (0);
	}

	rear = *stack;
	if (strcmp(opcodes[16]->opcode, "isstack") != 0)
		while (rear && rear->prev)
			rear = rear->prev;
	new =  malloc(sizeof(stack_t));
	if (new == NULL)
		return (501);
	new->n = atoi(data);
	if (strcmp(opcodes[16]->opcode, "isstack") == 0)
	{
		new->next = NULL;
		new->prev = *stack;
		(*stack)->next = new;
		*stack = new;
	}
	else
	{
		new->prev = NULL;
		new->next = rear;
		rear->prev = new;
	}

	return (0);
}

/**
  * pall_func - prints all values on the stack/queue
  * @stack: stack top or queue front
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
  * pint_func - prints the top/front value of the stack/queque
  * @stack: stack top or queue front
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
  * pop_func - deletes the top/front item on the stack/queue
  * @stack: stack top or queue front
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
  * swap_func - swaps the top/front two stack/queue items
  * @stack: the stack top or queue front
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
  * add_func - adds the top/front two stack/queue items
  * @stack: the stack top or queue front
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
  * nop_func - does nothing
  * @stack: the stack top or queue front
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
  * sub_func - substract the top/front two stack/queue items
  * @stack: the stack top or queue front
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
  * div_func - divides the top/front two stack/queue items
  * @stack: the stack top or queue front
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
  * mul_func - multiplies the top/front two stack/queue items
  * @stack: the stack top or queue front
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
  * mod_func - modulus of the top/front two stack/queue items
  * @stack: the stack top or queue front
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
  * pchar_func - prints ascii char of the top/front stack/queue item
  * @stack: the stack top or queue front
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
  * pstr_func - prints a str from all stack/queue item values
  * @stack: the stack top or queue front
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
  * rotl_func - rotates the queue/stack to the top
  * @stack: the stack top or queue front
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
  * rotr_func - rotates the stack/queue to the bottom
  * @stack: the stack top or queue front
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

/**
  * queue_mode - changes the data format to queue(FIFO)
  * @stack: the stack top or queue front
  * @line_num: the current line number
  * Return: always 0
  */
int queue_mode(stack_t **stack, unsigned int line_num, ...)
{
	opcodes[16]->opcode = "isqueue";
	/* just gimmick */
	if (stack && line_num)
		return (0);

	return (0);
}

/**
  * stack_mode - changes the data format to stack(LIFO)
  * @stack: the stack top or queue front
  * @line_num: the current line number
  * Return: always 0
  */
int stack_mode(stack_t **stack, unsigned int line_num, ...)
{
	opcodes[16]->opcode = "isstack";
	/* just gimmick */
	if (stack && line_num)
		return (0);

	return (0);
}
