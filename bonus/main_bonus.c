/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/17 16:08:12 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/04/18 20:26:10 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

// ctrl + d, stops get_next_line with EOF
int	main(int argc, char **argv)
{
	t_swap	swap;
	bool	is_this_sorted;

	swap.a = NULL;
	if (argc == 1)
		return (error_handling(swap.a));
	if (nodes(argc - 1, argv + 1, &swap) == false)
		return (error_handling(swap.a));
	swap.b = NULL;
	parsing_and_applying_instructions(&swap);
	is_this_sorted = check_if_sorted(swap.a);
	free_linked_list(swap.a);
	if (is_this_sorted == false || swap.b != NULL)
	{
		free_linked_list(swap.b);
		write(STDOUT_FILENO, "KO\n", 3);
		return (EXIT_FAILURE);
	}
	write(STDOUT_FILENO, "OK\n", 3);
	return (EXIT_SUCCESS);
}
