/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 13:16:44 by cdana             #+#    #+#             */
/*   Updated: 2020/09/21 16:29:37 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "problem.h"

int		*ft_ordervar(int *var, int *occ)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	while (var[i])
	{
		j = i + 1;
		while (var[j])
		{
			if (occ[i] < occ[j])
			{
				tmp = occ[i];
				occ[i] = occ[j];
				occ[j] = tmp;
				tmp = var[i];
				var[i] = var[j];
				var[j] = tmp;
			}
			j++;
		}
		i++;
	}
	free(occ);
	return (var);
}

int		*ft_getvar(t_problem *p)
{
	int		*var;
	int		*occ;
	int		i;
	int		j;
	int		k;

	var = malloc((2 * (p->var) + 1) * sizeof(int));
	occ = malloc((2 * (p->var) + 1) * sizeof(int));
	var[0] = 0;
	occ[0] = 0;
	i = 0;
	while (p->problem[i])
	{
		j = 0;
		while (p->problem[i][j])
		{
			k = 0;
			while (var[k] && var[k] != p->problem[i][j]) k++;
			if (var[k])
				occ[k]++;
			else
			{
				var[k] = p->problem[i][j];
				occ[k] = 1;
				var[k + 1] = 0;
				occ[k + 1] = 0;
			}
			j++;
		}
		i++;
	}
	return (ft_ordervar(var, occ));
}

int		ft_testline(int *stack, int k, int *line)
{
	int		i;
	int		j;
	int		pass;

	pass = 0;
	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i] != stack[j] && j < k) j++;
		if (j < k)
			pass = 1;
		i++;
	}
	return pass;
}
int		ft_cleanstack(t_problem *p)
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		pass;

	k = 1;
	while (p->stack[k])
	{
		pass = 1; // 1 if the variable is contained in the previous ones
		i = 0;
		while (pass && p->problem[i])
		{
			j = 0;
			while (p->problem[i][j] && p->problem[i][j] != p->stack[k]) j++;
			if (p->problem[i][j] == p->stack[k])
				pass = ft_testline(p->stack, k, p->problem[i]);
			i++;
		}
		if (pass == 0)
			k++;
		else
		{
			l = k;
			while (p->stack[l + 1])
			{
				p->stack[l] = p->stack[l + 1];
				l++;
			}
			p->stack[l] = 0;
		}
	}
	return (1);
}

int		ft_fillstack(t_problem *p)
{
	int		*var;

	if (p->dim < 2)
	{
		p->stack = 0;
		return (0);
	}
	var = ft_getvar(p);
	p->stack = var;
	ft_cleanstack(p);
	return (1);
}
