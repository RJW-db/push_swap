/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 20:17:46 by rde-brui      #+#    #+#                 */
/*   Updated: 2026/03/06 18:02:02 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libftx.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

typedef struct s_moves
{
	int		ra;
	int		rb;
	int		rr;
	int		rra;
	int		rrb;
	int		rrr;
	int		mixed;
}	t_moves;

typedef struct s_swap
{
	t_node	*a;
	t_node	*b;
	t_moves	optimal;
	int		total_nodes;
	int		a_size;
	int		b_size;
	int		max_value;
	int		min_value;
}	t_swap;

//	main.c
int		main(int argc, char **argv);

//	ps_nodes.c
bool	nodes(int argc, char **argv, t_swap *swap);

//	ps_commands
int		push_to_top(t_node **first, t_node **second, char *str);
void	swap_top_2(t_node **head, char *str);
void	first_to_last(t_node **first_to_last, char *str);
void	last_to_first(t_node **last_to_first, char *str);
void	use_commands(t_swap *s, t_node **a, t_node **b);

//	ps_to_b.c
void	push_to_b(t_swap *s, t_node **a, t_node **b);

//	ps_to_b.c
void	optimal_movement(t_swap *s, t_node *tmp);

//	ps_to_a.c
void	push_to_a(t_swap *s, t_node **b, t_node **a);

//	ps_utils.c
void	free_linked_list(t_node *lst);
int		error_handling(t_node *full_stack);
bool	check_if_sorted(t_node *linked_list);
void	three_or_less_nodes(t_node **a);
void	set_current_to_zero(t_moves	*set);

//	ps_utils_2.c
int		find_min_num(t_node *stack);
int		find_max_num(t_node *stack);
int		minimum_movements(int number_one, int number_two);
int		maximum_movements(int number_one, int number_two);

//	ps_utils_3.c
bool	sorting_order(t_swap *swap, t_node **a, t_node *tmp, bool check);
bool	ascending_order(t_swap *swap, t_node **a, int stack_nodes);
bool	dup_check(t_node *linked_list);

#endif
