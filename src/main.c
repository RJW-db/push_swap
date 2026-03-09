/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/29 21:11:24 by rde-brui      #+#    #+#                 */
/*   Updated: 2026/03/06 16:45:28 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_swap	swap;

	ft_memset(&swap.optimal, 0, sizeof(t_moves));
	if (argc == 1)
		return (error_handling(&swap));
	if (nodes(argc - 1, argv + 1, &swap) == false)
		return (error_handling(&swap));
	if (argc == 3 && swap.a->value > swap.a->next->value)
		swap_top_2(&swap.a, "sa\n");
	else if (argc == 4)
		three_or_less_nodes(&swap.a);
	else if (ascending_order(&swap, &swap.a, swap.total_nodes) == true)
		use_commands(&swap, &swap.a, &swap.b);
	else
	{
		push_to_b(&swap, &swap.a, &swap.b);
		push_to_a(&swap, &swap.b, &swap.a);
	}
	free_linked_list(swap.a);
	return (EXIT_SUCCESS);
}
