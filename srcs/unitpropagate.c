/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unitpropagate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 11:53:19 by cdana             #+#    #+#             */
/*   Updated: 2020/09/21 11:56:52 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "problem.h"

int		ft_remove(int *range, int i, int len)
{
	range[i] = range[len - 1];
	range[len - 1] = -1;
	return (1);
}

int		*ft_range(int len)
{
	int		*range;
	int		i;

	range = malloc((len + 1) * sizeof(int));
	i = 0;
	while (i < len)
	{
		range[i] = i;
		i++;
	}
	range[i] = -1;
	return (range);
}

int		ft_propagate(int *solution, int x)
{
	int		y;

	y = abs(x);
	if (x > 0)
		solution[y] = 1;
	else
		solution[y] = -1;
	return (1);
}

int		ft_analyseline(int *line, int *solution)
{
	int		i;
	int		pos;
	int		neg;
	int		x;
	int		y;

	pos = 0;
	neg = 0;
	i = 0;
	while (line[i])
	{
		y = abs(line[i]);
		if (solution[y] == 0)
			x = line[i];
		if (y * solution[y] == -line[i])
			neg++;
		if (y * solution[y] == line[i])
			pos++;
		i++;
	}
	if (pos > 0)
		return (1); // VALIDATED LINE
	if (i - neg == 1)
		return (ft_propagate(solution, x)); // UNITPROPAGATE
	if (i == neg)
		return (-1); // CONTRADICTION
	return (0);
}

int		ft_unitpropagate(int **problem, int *solution, int var)
{
	int		i;
	int		*range;
	int		ret;
	int 	repeat;
	int		len;

	i = 0;
	while (problem[i]) i++;
	range = ft_range(i);
	len = i;
	repeat = 1;
	while (repeat)
	{
		i = 0;
		repeat = 0;
		while (range[i] != -1)
		{
			ret = ft_analyseline(problem[range[i]], solution);
			if (ret == -1)
			{
				free(range);
				return (-1);
			}
			if (ret == 1)
			{
				repeat = 1;
				ft_remove(range, i, len);
				len--;
			}
			else
				i++;
		}
	}
	solution[0] = 0;
	i = 1;
	while (i <= var)
	{	
		solution[0] += abs(solution[i]);
		i++;
	}
	free(range);
	return (1);
}
