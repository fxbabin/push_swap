/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 13:45:26 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/15 13:36:46 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_elem(int **tab, t_ps *t, int idx, t_list **steps)
{
	int		start;
	int		end;

	(void)tab;
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
	apply_steps(tab, t, steps);
	if (t->top1 > 0 && *tab[0] > *tab[1])
		ft_lstpushback(steps, "sa", 2);
	apply_steps(tab, t, steps);
	return (0);
}

void	ft_selection_sort(int **tab, t_ps *t, int len, t_list **steps)
{
	int		tmp;
	int		min;
	int		ret;

	(void)len;
	tmp = t->top1;
	ret = 0;
	while (tmp > 2)
	{
		min = get_min(tab, 0, t->top1);
		move_elem(tab, t, min, steps);
		if ((ret = is_sorted(tab, 0, t->top1)) == 1)
			break ;
		ft_lstpushback(steps, "pb", 2);
		apply_steps(tab, t, steps);
		tmp--;
	}
	if (!ret)
		small_sort(tab, t, steps);
	while (t->top1 < t->top2)
		handler(tab, t, "pa", t->opt);
}
