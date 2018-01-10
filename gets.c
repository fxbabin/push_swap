/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 11:57:59 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/10 13:36:17 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				getopts(const char *opt)
{
	int		i;

	i = -1;
	if (ft_strbspn(opt, "-cv") && ft_strlen(opt) < 4)
	{
		if (opt[0] == '-')
		{
			if (opt[1] == 'c')
				i = 1;
			else if (opt[1] == 'v')
				i = 2;
		}
		if (ft_strlen(opt) == 3)
		{
			if ((i == 1 && opt[2] == 'v') || (i == 2 && opt[2] == 'c'))
				i = 0;
			else
				i = -1;
		}
	}
	return (i);
}

int				getmedian(int **tab, int top)
{
	int		**stab;
	int		med;

	stab = cpytab(tab, top);
	ft_quicksort(stab, 0, top);
	med = *stab[top / 2];
	free2((void**)stab, top - 1);
	return (med);
}

int				get_min(int **tab, int start, int end)
{
	int		midx;
	int		min;
	int		i;

	i = start;
	min = *tab[start];
	midx = start;
	if (end == start)
		return (start);
	while (++i <= end)
	{
		if (*tab[i] < min)
		{	
			min = *tab[i];
			midx = i;
		}
	}
	return (midx);
}

int				get_max(int **tab, int start, int end)
{
	int		madx;
	int		max;
	int		i;

	i = start;
	max = *tab[start];
	madx = start;
	if (end == start)
		return (start);
	while (++i <= end)
	{
		if (*tab[i] > max)
		{

			max = *tab[i];
			madx = i;
		}
	}
	return (madx);
}
