/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_utils_3.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 13:05:12 by rde-brui      #+#    #+#                 */
/*   Updated: 2026/03/06 18:01:42 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	sorting_order(t_swap *swap, t_node **a, t_node *tmp, bool check)
{
	const int	min = find_min_num(*a);
	const int	max = find_max_num(*a);

	while (tmp->next != NULL)
	{
		if (check == false)
			swap->optimal.ra++;
		if (tmp->value > tmp->next->value)
		{
			if (!((tmp->value != max && tmp->next->value != min)
					|| (tmp->value != max && (*a)->value != min))
				|| (check == true || max != tmp->value))
			{
				swap->optimal.ra = 0;
				return (false);
			}
			check = true;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	ascending_order(t_swap *swap, t_node **a, int stack_nodes)
{
	bool		check;

	set_current_to_zero(&swap->optimal);
	if (check_if_sorted(*a) == true)
		return (true);
	check = false;
	check = sorting_order(swap, a, *a, check);
	if (check == false)
		return (false);
	if (check == true && swap->optimal.ra > stack_nodes - swap->optimal.ra)
	{
		swap->optimal.rra = stack_nodes - swap->optimal.ra;
		swap->optimal.ra = 0;
	}
	else if (check == false)
		swap->optimal.ra = 0;
	return (true);
}

bool	dup_check(t_node *linked_list)
{
	t_node	*tmp;
	int		value;

	while (linked_list != NULL)
	{
		value = linked_list->value;
		linked_list = linked_list->next;
		tmp = linked_list;
		while (tmp != NULL)
		{
			if (value == tmp->value)
				return (false);
			tmp = tmp->next;
		}
	}
	return (true);
}
