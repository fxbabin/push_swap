/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 17:39:12 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/19 19:01:35 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		advselection_sort2(int **tab, t_ps *t, t_list **steps)
{
	move_elem(tab, t, get_max(tab, t->top1 + 1, t->top2), steps);
	apply_steps(tab, t, steps);
	ft_selection_sort(tab, t, 0, steps);
}

void			advselection_sort(int **tab, t_ps *t, t_op *op, t_list **steps)
{
	int		idx1;
	int		idx2;
	int		ned;
	int		t1;

	while (t->top1 > 5)
	{
		ned = get_nedian(tab, t->top1, t->top1 - 5);
		t1 = t->top1 - 5;
		while (t->top1 >= t1)
		{
			idx1 = get_minnedcost(tab, t, ned);
			if (t->top2 - t->top1 > 0)
				idx2 = get_insertidx(tab, t, idx1);
			else
				idx2 = 0;
			move_elem(tab, t, idx1, steps);
			move_elem(tab, t, idx2, steps);
			ft_lstpushback(steps, "pb", 2);
			optimize(tab, t, op, steps);
		}
	}
	advselection_sort2(tab, t, steps);
}

void			opti_sort(int **tab, t_ps *t, t_op *op, t_list **steps)
{
	int		idx1;
	int		idx2;
	int		ned;

	ned = get_nedian(tab, t->top1, 10);
	while (t->top1 >= 10)
	{
		idx1 = get_minnedcost(tab, t, ned);
		if (t->top2 - t->top1 > 0)
			idx2 = get_insertidx(tab, t, idx1);
		else
			idx2 = 0;
		move_elem(tab, t, idx1, steps);
		move_elem(tab, t, idx2, steps);
		ft_lstpushback(steps, "pb", 2);
		optimize(tab, t, op, steps);
	}
	move_elem(tab, t, get_max(tab, t->top1 + 1, t->top2), steps);
	apply_steps(tab, t, steps);
	advselection_sort(tab, t, op, steps);
}
