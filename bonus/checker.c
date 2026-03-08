/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 13:01:28 by rde-brui      #+#    #+#                 */
/*   Updated: 2024/04/18 20:30:29 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

static t_commands	valid_input_check(char *line)
{
	if (ft_strncmp(line, "pa\n", 3) == 0)
		return (PA);
	else if (ft_strncmp(line, "pb\n", 3) == 0)
		return (PB);
	else if (ft_strncmp(line, "ra\n", 3) == 0)
		return (RA);
	else if (ft_strncmp(line, "rb\n", 3) == 0)
		return (RB);
	else if (ft_strncmp(line, "rr\n", 3) == 0)
		return (RR);
	else if (ft_strncmp(line, "rra\n", 4) == 0)
		return (RRA);
	else if (ft_strncmp(line, "rrb\n", 4) == 0)
		return (RRB);
	else if (ft_strncmp(line, "rrr\n", 4) == 0)
		return (RRR);
	else if (ft_strncmp(line, "sa\n", 3) == 0)
		return (SA);
	else if (ft_strncmp(line, "sb\n", 3) == 0)
		return (SB);
	else if (ft_strncmp(line, "ss\n", 3) == 0)
		return (SS);
	return (FALSE_INPUT);
}

static void	apply_instruction(t_swap *swap, char *gnl, t_commands command_check)
{
	if (command_check == PA)
		push_to_top(&swap->b, &swap->a, NULL);
	else if (command_check == PB)
		push_to_top(&swap->a, &swap->b, NULL);
	if (command_check == RA || command_check == RR)
		first_to_last(&swap->a, NULL);
	if (command_check == RB || command_check == RR)
		first_to_last(&swap->b, NULL);
	if (command_check == RRA || command_check == RRR)
		last_to_first(&swap->a, NULL);
	if (command_check == RRB || command_check == RRR)
		last_to_first(&swap->b, NULL);
	if (command_check == SA || command_check == SS)
		swap_top_2(&swap->a, NULL);
	if (command_check == SB || command_check == SS)
		swap_top_2(&swap->b, NULL);
}

void	parsing_and_applying_instructions(t_swap *swap)
{
	t_commands	command_check;
	char		*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		command_check = valid_input_check(line);
		free(line);
		if (command_check == FALSE_INPUT)
		{
			free_linked_list(swap->a);
			write(STDERR_FILENO, "Error\n", 6);
			exit (EXIT_FAILURE);
		}
		apply_instruction(swap, line, command_check);
	}
}
