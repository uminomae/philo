#include "philo.h"

static void	make_first_ptr_node(t_ptr_list *list, t_ptr_node *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_ptr_node(t_ptr_list *list, t_ptr_node *node)
{
	list->tail->next = node;
	list->tail = node;
}

static t_ptr_node	*init_ptr_node()
{
	t_ptr_node	*node;

	node = (t_ptr_node *)malloc(sizeof(t_ptr_node));
	if (node == NULL)
		exit(1);
	node->ptr = NULL;
	node->next = NULL;
	return (node);
}

static void	add_ptr_list(t_ptr_list *ptr_list, void *ptr)
{
	t_ptr_node	*node;

	node = init_ptr_node();
	node->ptr = ptr;
	if (ptr_list->head == NULL)
		make_first_ptr_node(ptr_list, node);
	else
		add_last_ptr_node(ptr_list, node);
}

void	*malloc_and_add_ptr_list(t_ptr_list *ptr_list, size_t size)
{
	void	*ret;

	(void)ptr_list;
	ret = malloc(size);
	if (ret == NULL)
		exit(1);
	add_ptr_list(ptr_list, ret);
	return (ret);
}
