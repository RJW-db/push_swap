/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_utils_2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/15 21:18:54 by rde-brui      #+#    #+#                 */
/*   Updated: 2026/03/06 18:01:42 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_num(t_node *stack)
{
	int	current_min;

	current_min = stack->value;
	stack = stack->next;
	while (stack != NULL)
	{
		if (stack->value < current_min)
			current_min = stack->value;
		stack = stack->next;
	}
	return (current_min);
}

int	find_max_num(t_node *stack)
{
	int	current_max;

	current_max = stack->value;
	stack = stack->next;
	while (stack != NULL)
	{
		if (stack->value > current_max)
			current_max = stack->value;
		stack = stack->next;
	}
	return (current_max);
}

int	maximum_movements(int number_one, int number_two)
{
	if (number_one >= number_two)
		return (number_one);
	return (number_two);
}

int	minimum_movements(int number_one, int number_two)
{
	if (number_one >= number_two)
		return (number_two);
	return (number_one);
}
