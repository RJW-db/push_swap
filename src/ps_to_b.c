/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_to_b.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 21:11:24 by rde-brui      #+#    #+#                 */
/*   Updated: 2026/03/06 18:01:42 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	descending_order(t_swap *swap, t_node **b, int max_val)
{
	t_node	*tmp;
	int		counter;

	tmp = *b;
	counter = 0;
	while (tmp->value != max_val)
	{
		tmp = tmp->next;
		counter++;
	}
	if (counter <= swap->b_size - counter)
		while (counter-- > 0)
			first_to_last(b, "rb\n");
	else
		while (swap->b_size - counter++ > 0)
			last_to_first(b, "rrb\n");
}

void	push_to_b(t_swap *s, t_node **a, t_node **b)
{
	s->b_size = push_to_top(a, b, "pb\n");
	s->a_size = s->total_nodes - s->b_size;
	s->max_value = (*b)->value;
	while (s->a_size != 3)
	{
		optimal_movement(s, *a);
		use_commands(s, a, b);
		if ((*a)->value > s->max_value)
			s->max_value = (*a)->value;
		s->b_size += push_to_top(a, b, "pb\n");
		s->a_size--;
		set_current_to_zero(&s->optimal);
	}
	descending_order(s, b, s->max_value);
}
