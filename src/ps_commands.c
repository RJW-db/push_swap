/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_commands.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/14 19:45:53 by rde-brui      #+#    #+#                 */
/*   Updated: 2026/03/06 18:05:24 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_to_top(t_node **from, t_node **to, char *str)
{
	t_node	*head;

	if (*from == NULL)
		return (0);
	head = (*from)->next;
	if (*to != NULL)
	{
		(*from)->next = *to;
		*to = *from;
	}
	else
	{
		(*from)->next = NULL;
		*to = *from;
	}
	*from = head;
	if (str != NULL)
		(void)write(STDOUT_FILENO, str, ft_strlen(str));
	return (1);
}

void	swap_top_2(t_node **head, char *str)
{
	t_node	*tmp;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	tmp = (*head)->next;
	(*head)->next = tmp->next;
	tmp->next = (*head);
	(*head) = tmp;
	if (str != NULL)
		(void)write(STDOUT_FILENO, str, ft_strlen(str));
}

void	first_to_last(t_node **first_to_last, char *str)
{
	t_node	*temp;
	t_node	*new_head;

	if (*first_to_last == NULL || (*first_to_last)->next == NULL)
		return ;
	new_head = (*first_to_last)->next;
	temp = (*first_to_last);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = (*first_to_last);
	(*first_to_last)->next = NULL;
	(*first_to_last) = new_head;
	if (str != NULL)
		(void)write(STDOUT_FILENO, str, ft_strlen(str));
}

void	last_to_first(t_node **last_to_first, char *str)
{
	t_node	*tmp;
	t_node	*new_head;

	if (*last_to_first == NULL || (*last_to_first)->next == NULL)
		return ;
	tmp = (*last_to_first);
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	new_head = tmp->next;
	new_head->next = (*last_to_first);
	tmp->next = NULL;
	(*last_to_first) = new_head;
	if (str != NULL)
		(void)write(STDOUT_FILENO, str, ft_strlen(str));
}

void	use_commands(t_swap *s, t_node **a, t_node **b)
{
	while (s->optimal.rr-- > 0)
	{
		first_to_last(a, NULL);
		first_to_last(b, NULL);
		(void)write(1, "rr\n", 3);
	}
	while (s->optimal.rrr-- > 0)
	{
		last_to_first(a, NULL);
		last_to_first(b, NULL);
		(void)write(1, "rrr\n", 4);
	}
	while (s->optimal.ra-- > 0)
		first_to_last(a, "ra\n");
	while (s->optimal.rb-- > 0)
		first_to_last(b, "rb\n");
	while (s->optimal.rra-- > 0)
		last_to_first(a, "rra\n");
	while (s->optimal.rrb-- > 0)
		last_to_first(b, "rrb\n");
}
