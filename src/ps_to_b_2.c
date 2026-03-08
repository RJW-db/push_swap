/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_to_b_2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/04 12:51:29 by rjw           #+#    #+#                 */
/*   Updated: 2026/03/06 18:10:13 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "push_swap.h"

static void	mixed_commands(t_moves *cur, t_moves *new_cur)
{
	if (cur->ra < cur->rb)
		new_cur->ra = cur->ra;
	else
		new_cur->rb = cur->rb;
	if (cur->rra < cur->rrb)
		new_cur->rra = cur->rra;
	else
		new_cur->rrb = cur->rrb;
}

static int	optimal_moves(t_moves *cur)
{
	t_moves	new_cur;

	set_current_to_zero(&new_cur);
	cur->rr = maximum_movements(cur->ra, cur->rb);
	cur->rrr = maximum_movements(cur->rra, cur->rrb);
	new_cur.mixed = minimum_movements(cur->ra, cur->rra);
	new_cur.mixed += minimum_movements(cur->rb, cur->rrb);
	if (cur->rr <= cur->rrr && cur->rr <= new_cur.mixed)
	{
		new_cur.mixed = cur->rr;
		new_cur.rr = minimum_movements(cur->ra, cur->rb);
		new_cur.ra = cur->ra - new_cur.rr;
		new_cur.rb = cur->rb - new_cur.rr;
	}
	else if (cur->rrr <= cur->rr && cur->rrr <= new_cur.mixed)
	{
		new_cur.mixed = cur->rrr;
		new_cur.rrr = minimum_movements(cur->rra, cur->rrb);
		new_cur.rra = cur->rra - new_cur.rrr;
		new_cur.rrb = cur->rrb - new_cur.rrr;
	}
	else
		mixed_commands(cur, &new_cur);
	*cur = new_cur;
	return (new_cur.mixed);
}

static int	count_rotations(t_node *stack, int max_val, int new_val, int count)
{
	t_node	*tmp;

	tmp = stack;
	if (max_val < stack->value)
		return (0);
	while (tmp->value != max_val)
	{
		tmp = tmp->next;
		count++;
	}
	while (tmp != NULL)
	{
		if (new_val > tmp->value)
			return (count);
		tmp = tmp->next;
		count++;
	}
	tmp = stack;
	count = 0;
	while (tmp->value > new_val && tmp->value != max_val)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

static int	min_rotate(t_swap *s, t_node *node_in_a, t_moves *current, int i)
{
	int	current_mininum_moves;
	int	count;

	count = 0;
	current->ra = i;
	current->rra = s->a_size - i;
	current->rb = count_rotations(s->b, s->max_value, node_in_a->value, count);
	current->rrb = s->b_size - current->rb;
	current_mininum_moves = optimal_moves(current);
	return (current_mininum_moves);
}

void	optimal_movement(t_swap *s, t_node *tmp)
{
	t_moves	current;
	int		i;
	int		current_mininum_moves;
	int		optimal;

	optimal = INT_MAX;
	i = 0;
	while (i < s->a_size)
	{
		current_mininum_moves = min_rotate(s, tmp, &current, i);
		if (current_mininum_moves < optimal)
		{
			optimal = current_mininum_moves;
			s->optimal = current;
		}
		i++;
		tmp = tmp->next;
	}
}
