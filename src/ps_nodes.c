/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_nodes.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 17:33:40 by rde-brui      #+#    #+#                 */
/*   Updated: 2026/03/06 18:11:41 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "push_swap.h"

static bool		are_args_digits(char **argv);
static t_node	*new_node(char *content);
static bool		strict_atoi(const char *nptr, int *value);

bool	nodes(int argc, char **argv, t_swap *swap)
{
	t_node	*tmp;
	int		i;

	if (are_args_digits(argv) == false)
		return (false);
	swap->a = new_node(argv[0]);
	if (!swap->a)
		return (false);
	tmp = swap->a;
	i = 1;
	while (i < argc)
	{
		tmp->next = new_node(argv[i]);
		if (!tmp->next)
			return (false);
		tmp = tmp->next;
		++i;
	}
	if (dup_check(swap->a) == false)
		return (false);
	swap->total_nodes = i;
	return (true);
}

static bool	are_args_digits(char **argv)
{
	int	i;

	while (*argv != NULL)
	{
		i = 0;
		if ((*argv)[i] == '\0')
			return (false);
		if ((*argv)[i] == '+' || (*argv)[i] == '-')
			++i;
		while ((*argv)[i] != '\0')
		{
			if (ft_isdigit((*argv)[i]) == 0)
				return (false);
			++i;
		}
		++argv;
	}
	return (true);
}

static t_node	*new_node(char *content)
{
	t_node	*p;

	p = malloc(sizeof(t_node) * 1);
	if (!p)
		return (NULL);
	p->next = NULL;
	if (strict_atoi(content, &p->value) == false)
		return (NULL);
	return (p);
}

static bool	strict_atoi(const char *nptr, int *value)
{
	long	result;
	long	sign;

	result = 0;
	sign = 1;
	if (*nptr == '\0')
		return (0);
	if (*nptr == '-' || *nptr == '+')
		sign = 0L - (long)(*nptr++ == '-');
	if (*nptr == '\0' || *nptr == '-' || *nptr == '+')
		return (false);
	while (*nptr >= '0' && *nptr <= '9'
		&& result < (long)INT_MAX && result > (long)INT_MIN)
		result = result * 10 + (*nptr++ - '0');
	result *= sign;
	if (*nptr != '\0' || (result > (long)INT_MAX || result < (long)INT_MIN))
		return (false);
	*value = (int)result;
	return (true);
}
