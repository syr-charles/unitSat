/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   problem.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdana <cdana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 11:32:14 by cdana             #+#    #+#             */
/*   Updated: 2020/09/20 18:46:02 by cdana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROBLEM_H
# define PROBLEM_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_problem t_problem;
struct	s_problem {
	int			**problem;
	int			**solutions;
	int			*stack;
	int			dim;
	int			var;
	t_problem	*prev;
};

int			**ft_solve(int **problem);
int			ft_dimension(int **problem);
int			*ft_zeros(int var);
t_problem	*ft_makeproblem(int	**base, t_problem *p);
t_problem	*ft_killproblem(int **base, t_problem *p);
int			ft_fillstack(t_problem *p);
int			ft_variables(int **problem);
int			ft_unitpropagate(int **problem, int *solution, int var);
int			**ft_merge(int **base, int **left, int **right, int var);

#endif
