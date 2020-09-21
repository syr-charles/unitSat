/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killproblem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:08:29 by cdana             #+#    #+#             */
/*   Updated: 2020/09/21 19:57:22 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "problem.h"

int			*ft_zeros(int var)
{
	int		*solution;
	int		i;

	solution = malloc((var + 3) * sizeof(int));
	i = 0;
	while (i <= var)
	{
		solution[i] = 0;
		i++;
	}
	return (solution);
}

int			ft_solutionsappend(int **base, t_problem *p, int x)
{
	int		i;
	int		*solution;

	solution = ft_zeros(p->var);
	if (x > 0)
		solution[x] = 1;
	else
		solution[-x] = -1;
	if (ft_unitpropagate(base, solution, p->var) == -1)
	{
		free(solution);
		return (0);
	}
	i = 0;
	while (p->solutions[i]) i++;
	p->solutions[i] = solution;
	p->solutions[i + 1] = 0;
	return (1);
}

int			ft_freesolutions(int **solutions)
{
	int		i;

	if (solutions == 0)
		return (0);
	i = 0;
	while (solutions[i])
	{
		free(solutions[i]);
		i++;
	}
	free(solutions);
	return (1);
}

int			**ft_common(int **solutions, int var)
{
	int		i;
	int		x;
	int		*common;
	int		**pool;

	pool = malloc(3 * sizeof(int*));
	pool[0] = 0;
	if (solutions[0] == 0)
		return (pool);
	common = ft_zeros(var);
	x = 1; 
	while (x <= var)
	{
		common[x] = solutions[0][x];
		x++;
	}
	i = 0;
	while (solutions[i])
	{
		x = 1;
		while (x <= var)
		{
			if (solutions[i][x] != common[x])
				common[x] = 0;
			x++; 
		}
		i++;
	}
	pool[0] = common;
	pool[1] = 0;
	return (pool);
}

t_problem	*ft_killproblem(int **base, t_problem *p)
{
	t_problem	*prev;
	int			**tmp;
	int			**tmp2;
	int			i;

	i = 0;
	while (p->problem[i])
	{
		free(p->problem[i]);
		i++;
	}
	free(p->problem);
	if (p->stack)
		free(p->stack);
	prev = p->prev;
	ft_solutionsappend(base, p, prev->stack[0]);
	i = 0;
	while (prev->stack[i]) i++;
	if (prev->prev == 0)
		printf("Root: ");
	printf("Stack left %d ", i);
	tmp = ft_common(prev->solutions, p->var);
	tmp2 = ft_merge(base, tmp, p->solutions, p->var);
	ft_freesolutions(p->solutions);
	ft_freesolutions(tmp);
	p->solutions = tmp2;
	tmp = ft_common(p->solutions, p->var);
	tmp2 = ft_merge(base, tmp, prev->solutions, p->var);
	ft_freesolutions(prev->solutions);
	ft_freesolutions(tmp);
	prev->solutions = tmp2;
	tmp = ft_merge(base, p->solutions, prev->solutions, p->var);
	ft_freesolutions(prev->solutions);
	ft_freesolutions(p->solutions);
	prev->solutions = tmp;
	i = 0;
	while (prev->stack[i + 1])
	{
		prev->stack[i] = prev->stack[i + 1];
		i++;
	}
	prev->stack[i] = 0;
	free(p);
	//ft_elect(prev);
	return (prev);
}
