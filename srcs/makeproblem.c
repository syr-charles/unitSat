/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeproblem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 13:18:58 by cdana             #+#    #+#             */
/*   Updated: 2020/09/21 19:21:40 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "problem.h"

int			ft_dimension(int **problem)
{
	int		i;
	int		j;
	int		dim;

	dim = 0;
	i = 0;
	while (problem[i])
	{
		j = 0;
		while (problem[i][j]) j++;
		if (j == 0)
			return (0);
		if (dim < j)
			dim = j;
		i++;
	}
	return (dim);
}

int			*ft_subline(int *line, int x)
{
	int		i;
	int		j;
	int		*sl;

	i = 0;
	while (line[i]) i++;
	sl = malloc(i * sizeof(int));
	j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != x)
		{
			sl[j] = line[i];
			j++;
		}
		i++;
	}
	sl[j] = 0;
	return (sl);
}

int			**ft_subproblem(int	**problem, int x)
{
	int		i;
	int		j;
	int		k;
	int		**sub;
	
	i = 0;
	while (problem[i]) i++;
	sub = malloc((i + 1) * sizeof(int*));
	i = 0;
	k = 0;
	while (problem[i])
	{
		j = 0;
		while (problem[i][j] && problem[i][j] != x) j++;
		if (problem[i][j] == x)
		{
			sub[k] = ft_subline(problem[i], x);
			j = i;
			free(problem[i]);
			while (problem[j + 1])
			{
				problem[j] = problem[j + 1];
				j++;
			}
			problem[j] = 0;
			k++;
		}
		else
			i++;
	}
	sub[k] = 0;
	return (sub);
}

t_problem	*ft_makeproblem(int **base, t_problem *p)
{
	t_problem	*q;

	q = malloc(sizeof(t_problem));
	q->problem = ft_subproblem(p->problem, p->stack[0]);
	q->var = p->var;
	q->dim = ft_dimension(q->problem);
	ft_fillstack(q);
	q->solutions = 0;
	if (q->dim > 1)
	{
		q->solutions = malloc(3 * sizeof(int*));
		q->solutions[0] = ft_zeros(q->var);
		ft_unitpropagate(base, q->solutions[0], q->var);
		q->solutions[1] = 0;
	}
	if (q->dim == 0)
	{
		q->solutions = malloc(3 * sizeof(int*));
		q->solutions[0] = 0;
	}
	if (q->dim == 1)
	{
		q->solutions = malloc(4 * sizeof(int*));
		q->solutions[0] = ft_zeros(q->var);
		if (ft_unitpropagate(q->problem, q->solutions[0], q->var) == 1 &&
				ft_unitpropagate(base, q->solutions[0], q->var) == 1)
			q->solutions[1] = 0;
		else
		{
			free(q->solutions[0]);
			q->solutions[0] = 0;
		}
	}
	q->prev = p;
	return (q);
}
