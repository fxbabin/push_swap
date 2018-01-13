/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:54:52 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/13 13:20:55 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_op(t_op *op)
{
	op->ra = 0;
	op->rb = 0;
	op->rra = 0;
	op->rrb = 0;
	op->rr = 0;
	op->rrr = 0;
}

void	optimize_op(t_op *op)
{
	while (op->ra > 0 && op->rb > 0)
	{
		op->rr++;
		op->ra--;
		op->rb--;
	}
	while (op->rra > 0 && op->rrb > 0)
	{
		op->rrr++;
		op->rra--;
		op->rrb--;
	}
}

void	get_mininsertidx(int **tab, t_ps *t, t_op *op, int elem)
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

int		get_mininsertcost(int **tab, t_ps *t)
{
	int		i;
	int		min;
	int		midx;
	t_op	op;

	(void)tab;
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
		//ft_printf("%d ra %d rb %d rr %d rra %d rrb %d rrr %d\n", *tab[i], op.ra, op.rb, op.rr, op.rra, op.rrb, op.rrr);
		if ((op.ra + op.rb + op.rr + op.rra + op.rrb + op.rrr) < min)
		{
			min = (op.ra + op.rb + op.rr + op.rra + op.rrb + op.rrr);
			midx = i;
		}
	}
	return (midx);
}

/*int		get_minmedcost(int **tab, t_ps *t, int med)
{
	int		i;
	int		min;
	int		midx;
	t_op	op;

	(void)tab;
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
		//ft_printf("%d ra %d rb %d rr %d rra %d rrb %d rrr %d\n", *tab[i], op.ra, op.rb, op.rr, op.rra, op.rrb, op.rrr);
		if (*tab[i] > med)
			op.ra += 500;
		if ((op.ra + op.rb + op.rr + op.rra + op.rrb + op.rrr) < min)
		{
			min = (op.ra + op.rb + op.rr + op.rra + op.rrb + op.rrr);
			midx = i;
		}
	}
	return (midx);
}*/

int		getx(int **tab, t_ps *t, int idx1)
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
	//ft_printf("max %d\n", max);
	if (*tab[idx1] > *tab[max] || *tab[idx1] < *tab[min])
		return (max);
	else if (*tab[idx1] > *tab[t->top1 + 1] && *tab[idx1] < *tab[t->top2])
		return (t->top1 + 1);
	else
	{
		while (++i <= t->top2)
		{
			if (*tab[idx1] < *tab[i - 1] &&  *tab[idx1] > *tab[i])
				return (i);
		}
	}
	return (-1);
}


void		apply_op(int **tab, t_ps *t, t_op *op)
{
	while (op->ra > 0 && op->rb > 0)
	{
		handler(tab, t, "rr", t->opt);
		op->ra--;
		op->rb--;
	}
	while (op->ra > 0)
	{
		handler(tab, t, "ra", t->opt); 
		op->ra--;
	}
	while (op->rb > 0)
	{
		handler(tab, t, "rb", t->opt); 
		op->rb--;
	}
	while (op->rra > 0 && op->rrb > 0)
	{
		handler(tab, t, "rrr", t->opt);
		op->rra--;
		op->rrb--;
	}
	while (op->rra > 0)
	{
		handler(tab, t, "rra", t->opt); 
		op->rra--;
	}
	while (op->rrb > 0)
	{
		handler(tab, t, "rrb", t->opt); 
		op->rrb--;
	}
}



void	optimize(int **tab, t_ps *t, t_op *op, t_list **list)
{
	t_list          *l;

	if (!list || !*list)
		return ;
	l = *list;
	init_op(op);
	while ((*list))
	{
		if ((*list)->content)
		{
			if (ft_strequ((char*)(*list)->content, "pb"))
			{
				apply_op(tab, t, op);
				init_op(op);
				handler(tab, t, "pb", t->opt); 
			}
			if (ft_strequ((char*)(*list)->content, "ra"))
				op->ra++;
			if (ft_strequ((char*)(*list)->content, "rb"))
				op->rb++;
			if (ft_strequ((char*)(*list)->content, "rra"))
				op->rra++;
			if (ft_strequ((char*)(*list)->content, "rrb"))
				op->rrb++;
		}
		*list = (*list)->next;
	}
	*list = l;
}

/*int		get_minmedcost(int **tab, t_ps *t, int med)
{
	int		i;
	int		score;
	int		min;
	int		midx;

	i = -1;
	min = t->top2;
	midx = 0;
	while (++i <= t->top1)
	{
		score = 0;
		score = (i > t->top1 / 2) ? t->top1 - i  + 2 : i + 1;
		score += (*tab[i] > med) ? 500 : 0;
		if (t->top2 - t->top1 > 2)
			score += getmininsertidx(tab, t->top1 + 1, t->top2, *tab[i]);
		if (score < min)
		{
			min = score;
			midx = i;
		}
	}
	return (midx);
}*/


void	new_sort(int **tab, t_ps *t, t_op *op, t_list **steps)
{
	int		idx1;
	int		idx2;
	//int		med;
	//int		t1;

	//med = getmedian(tab, t->top1);
	//ft_printf("%d\n", med);
	(void)op;
	//t1 = t->top1 / 2;
	//ft_printf("a\n");
	while (t->top1 >= 0)
	{
		//ft_printf("b\n");
		idx1 = get_mininsertcost(tab, t);
		//ft_printf("b\n");
		//idx1 = get_minmedcost(tab, t, med);
		if (t->top2 - t->top1 > 0)
			idx2 = getx(tab, t, idx1);
		else
			idx2 = 0;
		//ft_printf("idx1 %d %d idx2 %d %d\n", idx1, *tab[idx1], idx2, *tab[idx2]);
		//ft_printf("b\n");
		//ft_printf("idx1 %d idx2 %d\n", idx1, idx2);
		//if (*tab[0]
		move_elem(tab, t, idx1, steps);
		move_elem(tab, t, idx2, steps);
		ft_lstpushback(steps, "pb", 2);
		//ft_lstdump(steps);
		optimize(tab, t, op, steps);
		//t->top1--;
		ft_lstdel(steps, ft_eldel);
		*steps = NULL;
	}
	//ft_selection_sort(tab, t, 20, steps);
	//apply_steps(tab, t, steps);
	//ft_lstdel(steps, ft_eldel);
	//*steps = NULL;
	while (t->top1 < t->top2)
		handler(tab, t, "pa", t->opt);
	move_elem(tab, t, get_min(tab, 0, t->top1), steps);
}


//stack_1 : [1] [74] [21] [7] [92] [19] [15] [89] [41] [45] [56] [31] [71] [84] [65] [57] [99] [63] [68] [32] [26] [62] [91] [12] [54] [70] [85] [95] [96] [72] [90] [58] [86] [43] [29] [8] [11] [66] [16] [30] [44] [60] [49] [98] [69] [97] [18] [17] [33] [78] [9] [53] [23] [100] [73] [10] [76] [75] [42] [50] [13] [40] [81] [6] [4] [3] [94]
//stack_2 : [88] [93] [87] [83] [82] [80] [79] [77] [67] [64] [61] [59] [55] [52] [51] [48] [47] [46] [39] [38] [37] [36] [35] [34] [28] [27] [25] [24] [22] [20] [14] [5] [2]
/*void	neww_sort(int **tab, t_ps *t, t_op *op, t_list **steps)
{
	int		idx1;
	int		idx2;
	int		med;
	int		t1;

	t1 = t->top1 / 2;
	while (t1 > 19)
	{
		med = getmedian(tab, t->top1);
		t1 = t->top1 / 2;
		while (t->top1 > t1)
		{
			idx1 = get_minmedcost(tab, t, med);
			if (t->top2 - t->top1 > 0)
				idx2 = getx(tab, t, idx1);
			else
				idx2 = 0;
			move_elem(tab, t, idx1, steps);
			move_elem(tab, t, idx2, steps);
			ft_lstpushback(steps, "pb", 2);
			optimize(tab, t, op, steps);
			ft_lstdel(steps, ft_eldel);
			*steps = NULL;
		}
	}
	ft_selection_sort(tab, t, steps);
	while (t->top1 < t->top2)
		handler(tab, t, "pa", t->opt);
	//move_elem(t, get_min(tab, 0, t->top1), steps);
}*/

int		inner_main(int argc, char **argv, t_ps *t)
{
	int			**tab;
	t_list		*steps;
	t_op		op;

	steps = NULL;
	init_op(&op);
	if (!(tab = ft_checknumbers(argc, argv, t->opt)))
		return (ft_error(-1));
	t->top1 = (t->opt > -1 && **argv != 'x') ? argc - 3 : argc - 2;
	t->top2 = t->top1;
	if (!(ft_checkdoubles(tab, t->top2)))
		return (ft_error(-1));
	//./push_swap -cv 45 74 16 7 71 99 98 24
	/*if (t->top2 <= 2)
		small_sort(tab, t, &steps);
	else if (t->top2 <= 45)
		ft_selection_sort(tab, t, t->top2, &steps);*/
	//else*/
	new_sort(tab, t, &op, &steps);
	//move_elem(tab, t, 1, &steps);
	//handler
	//move_elem(t, 4, &steps);
	/*handler(tab, t, "pb", t->opt);
	handler(tab, t, "pb", t->opt);
	handler(tab, t, "pb", t->opt);
	init_op(&op);
	//get_mininsertidx(tab, t, &op, 14);
	ft_printf("%d\n", get_mininsertcost(tab, t));*/
	//ft_printf("rb %d rrb %d\n", op.rb, op.rrb);
	apply_steps(tab, t, &steps);
	if (**argv == 'x')
		free2((void**)argv, tabsize(argv));
	free2((void**)tab, t->top2);
	ft_lstdel(&steps, ft_eldel);
	return (0);
}

int		main(int argc, char **argv)
{
	t_ps		t;

	if (argc < 2)
		return (ft_error(-1));
	t.opt = getopts(argv[1]);
	argv = modif_argv(argc, argv, t.opt);
	argc = (argc != tabsize(argv)) ? tabsize(argv) : argc;
	inner_main(argc, argv, &t);
	return (0);
}
