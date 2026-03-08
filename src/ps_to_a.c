/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_to_a.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/11 16:08:48 by rde-brui      #+#    #+#                 */
/*   Updated: 2026/03/06 18:01:42 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_value(t_swap *s, t_node **b, t_node **a, t_node *tmp_a)
{
	s->min_value = find_min_num(*a);
	s->optimal.ra = 0;
	while (tmp_a->value != s->min_value)
	{
		s->optimal.ra++;
		tmp_a = tmp_a->next;
	}
	if (s->min_value < (*b)->value)
	{
		while (tmp_a != NULL && tmp_a->value < (*b)->value)
		{
			s->optimal.ra++;
			tmp_a = tmp_a->next;
		}
	}
	s->optimal.rra = s->a_size - s->optimal.ra;
	if (s->optimal.rra < s->optimal.ra)
		s->optimal.ra = 0;
	else
		s->optimal.rra = 0;
	use_commands(s, a, b);
	s->a_size += push_to_top(b, a, "pa\n");
	s->b_size--;
}

static int	last_value_node(t_node *stack)
{
	while (stack->next != NULL)
		stack = stack->next;
	return (stack->value);
}

void	push_to_a(t_swap *s, t_node **b, t_node **a)
{
	three_or_less_nodes(a);
	s->max_value = find_max_num(*a);
	if ((*b)->value > s->max_value)
	{
		s->a_size += push_to_top(b, a, "pa\n");
		s->b_size--;
	}
	if (*b != NULL)
	{
		while ((*b)->next != NULL)
		{
			s->max_value = last_value_node(*a);
			if (s->max_value > (*b)->value && (*b)->value > find_min_num(*a))
				last_to_first(a, "rra\n");
			else if ((*a)->value > (*b)->value)
				rotate_value(s, b, a, *a);
		}
		rotate_value(s, b, a, *a);
	}
	s->min_value = find_min_num(*a);
	while ((*a)->value != s->min_value)
		last_to_first(a, "rra\n");
}
