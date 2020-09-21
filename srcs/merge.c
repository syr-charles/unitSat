/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:14:17 by cdana             #+#    #+#             */
/*   Updated: 2020/09/21 19:39:45 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "problem.h"

int			ft_insert(int **solutions, int *solution, int len)
{
	int		a;
	int		b;
	int		c;

	a = 0;
	b = len / 2;
	while (b > 1)
	{
		c = a + b;
		if (solutions[c][0] < solution[0])
			a = a + b;
		b = b / 2;
	}
	c = a;
	while (solutions[c] && solutions[c][0] < solution[0]) c++;
	a = len;
	while (a > c)
	{
		solutions[a] = solutions[a - 1];
		a--;
	}
	solutions[c] = solution;
	solutions[len + 1] = 0;
	return (1);
}

int			ft_mergeline(int *l, int *r, int *solution, int var)
{
	int		i;

	i = 0;
	while (i <= var)
	{
		solution[i] = 0;
		if (l[i] && l[i] == -r[i])
			return (0);
		if (l[i] > 0 || r[i] > 0)
			solution[i] = 1;
		if (l[i] < 0 || r[i] < 0)
			solution[i] = -1;
		i++;
	}
	return (1);
}

int			ft_contains(int *sml, int *big, int *tocheck)
{
	int		i;

	i = 0;
	while (tocheck[i] && sml[tocheck[i]] == big[tocheck[i]]) i++;
	if (tocheck[i] == 0)
		return (1);
	return (0);
}

int			ft_clean(int **solutions, int var)
{
	int		len;
	int		i;
	int		j;
	int		k;
	int		*tocheck;

	tocheck = ft_zeros(var);
	len = 0;
	i = 0;
	while (solutions[i])
	{
		j = 0;
		tocheck[0] = 0;
		k = 1;
		while (k <= var)
		{
			if (solutions[i][k])
			{
				tocheck[j] = k;
				tocheck[j + 1] = 0;
				j++;
			}
			k++;
		}
		j = i + 1;
		while (solutions[j])
		{
			if (solutions[j] && ft_contains(solutions[i], solutions[j], tocheck) == 1)
			{
				free(solutions[j]);
				k = j;
				while (solutions[k + 1])
				{
					solutions[k] = solutions[k + 1];
					k++;
				}
				solutions[k] = 0;
			}
			else
				j++;
		}
		i++;
	}
	free(tocheck);
	return (1);
}

int			**ft_merge(int **base, int **left, int **right, int var)
{
	int		i;
	int		j;
	int		c;
	int		**new;
	int		*solution;

	i = 0;
	while (left[i]) i++;
	j = 0;
	while (right[j]) j++;
	new = malloc((i * j + 2) * sizeof(int*));
	solution = ft_zeros(var);
	printf("Merge O(%d) ", i * j);
	i = 0;
	c = 0;
	new[c] = 0;
	while (left[i])
	{
		j = 0;
		while (right[j])
		{
			if (ft_mergeline(left[i], right[j], solution, var) == 1 &&
					ft_unitpropagate(base, solution, var) == 1)
			{
				ft_insert(new, solution, c);
				c++;
				solution = ft_zeros(var);
			}
			j++;
		}
		i++;
	}
	new[c] = 0;
	free(solution);
	ft_clean(new, var);
	i = 0;
	while (new[i]) i++;
	printf("Result (%d)\n", i);
	return (new);
}
