/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 13:45:26 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/11 17:18:49 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_elem(t_ps *t, int idx, t_list **steps)
{
	int		start;
	int		end;

	end = (idx <= t->top1) ? t->top1 : t->top2;
	start = (idx <= t->top1) ? 0 : t->top1 + 1;
	if ((idx - start) <= (end - start) / 2)
	{
		while (idx-- > start)
			(end == t->top1) ? ft_lstpushback(steps, "ra", 2) :
				ft_lstpushback(steps, "rb", 2);
	}
	else if ((idx - start) > (end - start) / 2)
	{
		while (idx <= end && idx++)
			(end == t->top1) ? ft_lstpushback(steps, "rra", 2) :
				ft_lstpushback(steps, "rrb", 2);
	}
}

int		small_sort(int **tab, t_ps *t, t_list **steps)
{
	int		max;
	int		i;

	i = 0;
	max = 0;
	if (t->top2 == 0)
		return (0);
	while (++i <= t->top1)
		if (*tab[i] > *tab[max])
			max = i;
	if (max == 0 && t->top1 == 2)
		ft_lstpushback(steps, "ra", 2);
	else if (max == 1 && t->top1 == 2)
		ft_lstpushback(steps, "rra", 3);
	if (*tab[0] > *tab[1])
		ft_lstpushback(steps, "sa", 2);
	return (0);
}

void	ft_selection_sort(int **tab, t_ps *t, t_list **steps)
{
	int		tmp;
	int		min;

	tmp = t->top1;
	while (tmp > 2)
	{
		min = get_min(tab, 0, t->top1);
		move_elem(t, min, steps);
		if (is_sorted(tab, t->top1, t->top2))
			break ;
		ft_lstpushback(steps, "pb", 2);
		apply_steps(tab, t, steps);
		ft_lstdel(steps, ft_eldel);
		*steps = NULL;
		tmp--;
	}
	if (tmp == 2)
		small_sort(tab, t, steps);
	//while (tmp++ < t->top2)
	//	ft_lstpushback(steps, "pa", 2);
}

int		is_relsorted(int **tab, int start, int end)
{
	int		i;
	int		min;

	min = get_min(tab, start, end);
	i = min;
	while (++i <= end)
		if (*tab[i - 1] > *tab[i])
			return (0);
	i = start;
	if (min > 0)
	{
		if (*tab[end] > *tab[0])
			return (0);
		while (++i <= min - 1)
			if (*tab[i - 1] > *tab[i])
				return (0);
	}
	return (1);
}

int		is_relrsorted(int **tab, int start, int end)
{
	int		i;
	int		max;

	max = get_max(tab, start, end);
	i = max;
	while (++i <= end)
		if (*tab[i - 1] < *tab[i])
			return (0);
	i = start;
	if (max > 0)
	{
		if (*tab[end] < *tab[0])
			return (0);
		while (++i <= max - 1)
			if (*tab[i - 1] < *tab[i])
				return (0);
	}
	return (1);
}
