/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:55:19 by cdana             #+#    #+#             */
/*   Updated: 2020/09/21 10:57:02 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "problem.h"

int			ft_variables(int **problem)
{
	int		i;
	int		j;
	int		var;

	i = 0;
	var = 0;
	while (problem[i])
	{
		j = 0;
		while (problem[i][j])
		{
			if (abs(problem[i][j]) > var)
				var = abs(problem[i][j]);
			j++;
		}
		i++;
	}
	return (var);
}

t_problem	*ft_solver(int **base, t_problem *p)
{
	while (p->prev || p->stack[0])
	{
		if (p->stack[0])
			p = ft_makeproblem(base, p);
		if (p->dim < 2)
			p = ft_killproblem(base, p);
		else if (p->prev && p->stack[0] == 0)
			p = ft_killproblem(base, p);
	}
	return (p);
}

int			**ft_solve(int **problem)
{
	t_problem	*p;
	int			**solutions;

	p = malloc(sizeof(t_problem));
	p->problem = problem;
	p->dim = ft_dimension(problem);
	p->var = ft_variables(problem);
	ft_fillstack(p);
	p->solutions = malloc(3 * sizeof(int*));
	p->solutions[0] = ft_zeros(p->var);
	if (ft_unitpropagate(p->problem, p->solutions[0], p->var) == -1)
	{
		free(p->solutions[0]);
		p->solutions[0] = 0;
		p->dim = 0;
	}
	p->solutions[1] = 0;
	if (p->dim > 1)
		p = ft_solver(problem, p);
	if (p->stack)
		free(p->stack);
	solutions = p->solutions;
	free(p);
	return (solutions);
}
