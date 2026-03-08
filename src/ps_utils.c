/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 20:58:05 by rde-brui      #+#    #+#                 */
/*   Updated: 2026/03/06 18:05:43 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_linked_list(t_node *stack)
{
	t_node	*tmp;

	while (stack != NULL)
	{
		tmp = (stack)->next;
		free(stack);
		stack = tmp;
	}
}

int	error_handling(t_node *full_stack)
{
	(void)write(STDERR_FILENO, "Error\n", 6);
	free_linked_list(full_stack);
	return (EXIT_FAILURE);
}

bool	check_if_sorted(t_node *linked_list)
{
	int	previous_node_value;

	if (linked_list == NULL || linked_list->next == NULL)
		return (false);
	previous_node_value = linked_list->value;
	linked_list = linked_list->next;
	while (linked_list != NULL)
	{
		if (previous_node_value > linked_list->value)
			return (false);
		previous_node_value = linked_list->value;
		linked_list = linked_list->next;
	}
	return (true);
}

void	three_or_less_nodes(t_node **a)
{
	if (check_if_sorted(*a) == true)
		return ;
	if ((*a)->next->value > (*a)->value
		&& (*a)->next->value > (*a)->next->next->value)
		last_to_first(a, "rra\n");
	else if ((*a)->value > (*a)->next->value
		&& (*a)->value > (*a)->next->next->value)
		first_to_last(a, "ra\n");
	if ((*a)->value > (*a)->next->value)
		swap_top_2(a, "sa\n");
}

void	set_current_to_zero(t_moves	*set)
{
	set->ra = 0;
	set->rb = 0;
	set->rr = 0;
	set->rra = 0;
	set->rrb = 0;
	set->rrr = 0;
	set->mixed = 0;
}
