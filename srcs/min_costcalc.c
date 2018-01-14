/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_costcalc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 17:24:33 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/14 17:30:21 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			get_mininsertidx(int **tab, t_ps *t, t_op *op, int elem)
{
	int		start;
	int		end;
	int		i;
	int		max;

	start = t->top1 + 1;
	end = t->top2;
	i = start;
	max = get_max(tab, start, end);
	if (elem > *tab[max] || elem < *tab[get_min(tab, start, end)])
	{
		op->rb += ((max - start) <= (end - start) / 2) ? max - start : 0;
		op->rrb += ((max - start) > (end - start) / 2) ? end - max + 1 : 0;
	}
	else if (elem > *tab[start] && elem < *tab[end])
		return ;
	else
	{
		while (++i <= end)
			if (elem < *tab[i - 1] && elem > *tab[i])
			{
				op->rb += ((i - start) <= (end - start) / 2) ? i - start : 0;
				op->rrb += ((i - start) > (end - start) / 2) ? end - i + 1 : 0;
			}
	}
}

int				get_mininsertcost(int **tab, t_ps *t)
{
	int		i;
	int		min;
	int		midx;
	t_op	op;

	i = -1;
	midx = 0;
	min = t->top2;
	while (++i <= t->top1)
	{
		init_op(&op);
		op.ra += (i <= t->top1 / 2) ? i : 0;
		op.rra += (i > t->top1 / 2) ? t->top1 - i + 1 : 0;
		if (t->top2 - t->top1 > 1)
			get_mininsertidx(tab, t, &op, *tab[i]);
		optimize_op(&op);
		if ((op.ra + op.rb + op.rr + op.rra + op.rrb + op.rrr) < min)
		{
			min = (op.ra + op.rb + op.rr + op.rra + op.rrb + op.rrr);
			midx = i;
		}
	}
	return (midx);
}

int				get_nedian(int **tab, int top, int limit)
{
	int		**stab;
	int		ned;

	stab = cpytab(tab, top);
	ft_quicksort(stab, 0, top);
	ned = *stab[top - limit];
	free2((void**)stab, top);
	return (ned);
}

int				get_minnedcost(int **tab, t_ps *t, int ned)
{
	int		i;
	int		min;
	int		midx;
	t_op	op;

	i = -1;
	midx = 0;
	min = t->top2;
	while (++i <= t->top1)
	{
		init_op(&op);
		op.ra += (i <= t->top1 / 2) ? i : 0;
		op.rra += (i > t->top1 / 2) ? t->top1 - i + 1 : 0;
		if (t->top2 - t->top1 > 1)
			get_mininsertidx(tab, t, &op, *tab[i]);
		optimize_op(&op);
		if (*tab[i] > ned)
			op.ra += 500;
		if ((op.ra + op.rb + op.rr + op.rra + op.rrb + op.rrr) < min)
		{
			min = (op.ra + op.rb + op.rr + op.rra + op.rrb + op.rrr);
			midx = i;
		}
	}
	return (midx);
}

int				get_insertidx(int **tab, t_ps *t, int idx1)
{
	int		max;
	int		min;
	int		i;

	(void)tab;
	(void)t;
	(void)idx1;
	i = t->top1 + 1;
	max = get_max(tab, t->top1 + 1, t->top2);
	min = get_min(tab, t->top1 + 1, t->top2);
	if (*tab[idx1] > *tab[max] || *tab[idx1] < *tab[min])
		return (max);
	else if (*tab[idx1] > *tab[t->top1 + 1] && *tab[idx1] < *tab[t->top2])
		return (t->top1 + 1);
	else
	{
		while (++i <= t->top2)
		{
			if (*tab[idx1] < *tab[i - 1] && *tab[idx1] > *tab[i])
				return (i);
		}
	}
	return (-1);
}
