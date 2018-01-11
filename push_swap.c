/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:54:52 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/11 23:01:01 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*int		getinsertidx(int **tab, int start, int end, int elem)
  {
  int		i;
  int		max;

  i = start;
  max = get_max(tab, start, end);
//ft_printf("%d\n", max);
if (elem > *tab[max])
return (max);
else if (elem == 0 && elem > *tab[start] && elem < *tab[end])
return (0);
else
{
while (++i <= end)
{
if (elem < *tab[i - 1] && elem > *tab[i])
return (i);
}
}
return (-1);
}*/

int		getmininsertidx(int **tab, int start, int end, int elem)
{
	int		i;
	int		max;

	i = start;
	max = get_max(tab, start, end);
	if (elem > *tab[max])
		return (max - start);
	else if (elem > *tab[start] && elem < *tab[end])
		return (0);
	else
	{
		while (++i <= end)
		{
			if (elem < *tab[i - 1] && elem > *tab[i])
				return (i - start);
		}
	}
	return (0);
}

int		get_mininsertcost(int **tab, t_ps *t)
{
	int		i;
	int		score;
	int		min;
	int		midx;

	i = -1;
	min = t->top1 / 2;
	midx = 0;
	while (++i <= t->top1)
	{
		score = 0;
		score = (i > t->top1 / 2) ? t->top1 - i  + 2 : i + 1;
		if (t->top2 - t->top1 > 2)
			score += getmininsertidx(tab, t->top1 + 1, t->top2, *tab[i]);
		if (score < min)
		{
			min = score;
			midx = i;
		}
	}
	return (midx);
}

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

void	init_op(t_op *op)
{
	op->ra = 0;
	op->rb = 0;
	op->rra = 0;
	op->rrb = 0;
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

int		get_minmedcost(int **tab, t_ps *t, int med)
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
}


void	new_sort(int **tab, t_ps *t, t_op *op, t_list **steps)
{
	int		idx1;
	int		idx2;
	int		med;
	int		t1;

	med = getmedian(tab, t->top1);
	//ft_printf("%d\n", med);
	(void)op;
	t1 = t->top1 / 2;
	while (t->top1 > t1)
	{
		idx1 = get_minmedcost(tab, t, med);
		if (t->top2 - t->top1 > 0)
			idx2 = getx(tab, t, idx1);
		else
			idx2 = 0;
		//ft_printf("idx1 %d idx2 %d\n", idx1, idx2); 
		move_elem(t, idx1, steps);
		move_elem(t, idx2, steps);
		ft_lstpushback(steps, "pb", 2);
		//ft_lstdump(steps);
		optimize(tab, t, op, steps);
		//apply_steps(tab, t, steps);
		//t->top1--;
		ft_lstdel(steps, ft_eldel);
		*steps = NULL;
	}
	/*med = getmedian(tab, t->top1);
	//ft_printf("%d\n", med);
	t1 = t->top1 / 2;
	(void)op;
	while (t->top1 > t1)
	{
		idx1 = get_minmedcost(tab, t, med);
		if (t->top2 - t->top1 > 0)
			idx2 = getx(tab, t, idx1);
		else
			idx2 = 0;
		//ft_printf("idx1 %d idx2 %d\n", idx1, idx2); 
		move_elem(t, idx1, steps);
		move_elem(t, idx2, steps);
		ft_lstpushback(steps, "pb", 2);
		//ft_lstdump(steps);
		optimize(tab, t, op, steps);
		//apply_steps(tab, t, steps);
		//t->top1--;
		ft_lstdel(steps, ft_eldel);
		*steps = NULL;
	}*/
	/*med = getmedian(tab, t->top1);
	//ft_printf("%d\n", med);
	t1 = t->top1 / 2;
	(void)op;
	while (t->top1 > t1)
	{
		idx1 = get_minmedcost(tab, t, med);
		if (t->top2 - t->top1 > 0)
			idx2 = getx(tab, t, idx1);
		else
			idx2 = 0;
		//ft_printf("idx1 %d idx2 %d\n", idx1, idx2); 
		move_elem(t, idx1, steps);
		move_elem(t, idx2, steps);
		ft_lstpushback(steps, "pb", 2);
		//ft_lstdump(steps);
		optimize(tab, t, op, steps);
		//apply_steps(tab, t, steps);
		//t->top1--;
		ft_lstdel(steps, ft_eldel);
		*steps = NULL;
	}
	t1 = t->top1 / 2;
	(void)op;
	while (t->top1 > t1)
	{
		idx1 = get_minmedcost(tab, t, med);
		if (t->top2 - t->top1 > 0)
			idx2 = getx(tab, t, idx1);
		else
			idx2 = 0;
		//ft_printf("idx1 %d idx2 %d\n", idx1, idx2); 
		move_elem(t, idx1, steps);
		move_elem(t, idx2, steps);
		ft_lstpushback(steps, "pb", 2);
		//ft_lstdump(steps);
		optimize(tab, t, op, steps);
		//apply_steps(tab, t, steps);
		//t->top1--;
		ft_lstdel(steps, ft_eldel);
		*steps = NULL;
	}*/
	//ft_selection_sort(tab, t, steps);
	/*while (t->top1 >= 0)
	{
		//idx1 = get_minmedcost(tab, t, med);
		idx1 = get_mininsertcost(tab, t);
		if (t->top2 - t->top1 > 0)
			idx2 = getx(tab, t, idx1);
		else
			idx2 = 0;
		//ft_printf("idx1 %d idx2 %d\n", idx1, idx2); 
		move_elem(t, idx1, steps);
		move_elem(t, idx2, steps);
		ft_lstpushback(steps, "pb", 2);
		//ft_lstdump(steps);
		optimize(tab, t, op, steps);
		//apply_steps(tab, t, steps);
		//t->top1--;
		ft_lstdel(steps, ft_eldel);
		*steps = NULL;
	}
	while (t->top1 < t->top2)
		handler(tab, t, "pa", t->opt);
	move_elem(t, get_min(tab, 0, t->top1), steps);*/
}

void	neww_sort(int **tab, t_ps *t, t_op *op, t_list **steps)
{
	int		idx1;
	int		idx2;
	int		med;
	int		t1;

	med = getmedian(tab, t->top1);
	//ft_printf("%d\n", med);
	(void)op;
	t1 = t->top1 / 2;
	while (t->top1 >= t1)
	{
		//idx1 = get_minmedcost(tab, t, med);
		idx1 = get_mininsertcost(tab, t);
		if (t->top2 - t->top1 > 0)
			idx2 = getx(tab, t, idx1);
		else
			idx2 = 0;
		//ft_printf("idx1 %d idx2 %d\n", idx1, idx2); 
		move_elem(t, idx1, steps);
		move_elem(t, idx2, steps);
		ft_lstpushback(steps, "pb", 2);
		//ft_lstdump(steps);
		optimize(tab, t, op, steps);
		//apply_steps(tab, t, steps);
		//t->top1--;
		ft_lstdel(steps, ft_eldel);
		*steps = NULL;
	}
	while (t->top1 >= 0)
		handler(tab, t, "pb", t->opt);
	/*while (t->top1 > t1)
	{
		idx1 = get_minmedcost(tab, t, med);
		if (t->top2 - t->top1 > 0)
			idx2 = getx(tab, t, idx1);
		else
			idx2 = 0;
		//ft_printf("idx1 %d idx2 %d\n", idx1, idx2); 
		move_elem(t, idx1, steps);
		move_elem(t, idx2, steps);
		ft_lstpushback(steps, "pb", 2);
		//ft_lstdump(steps);
		optimize(tab, t, op, steps);
		//apply_steps(tab, t, steps);
		//t->top1--;
		ft_lstdel(steps, ft_eldel);
		*steps = NULL;
	}*/

	/*t1 = t->top1 / 2;
	while (t1 >= 12)
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
			move_elem(t, idx1, steps);
			move_elem(t, idx2, steps);
			ft_lstpushback(steps, "pb", 2);
			optimize(tab, t, op, steps);
			ft_lstdel(steps, ft_eldel);
			*steps = NULL;
		}
	}
	ft_selection_sort(tab, t, steps);
	while (t->top1 < t->top2)
		handler(tab, t, "pa", t->opt);
	move_elem(t, get_min(tab, 0, t->top1), steps);*/
}




int		inner_main(int argc, char **argv, t_ps *t)
{
	int			**tab;
	t_list		*steps;
	t_op		op;

	steps = NULL;
	if (!(tab = ft_checknumbers(argc, argv, t->opt)))
		return (ft_error(-1));
	t->top1 = (t->opt > -1 && **argv != 'x') ? argc - 3 : argc - 2;
	t->top2 = t->top1;
	if (!(ft_checkdoubles(tab, t->top2)))
		return (ft_error(-1));
	//./push_swap -cv 45 74 16 7 71 99 98 24
	/*if (t->top2 <= 2)
	  small_sort(tab, t, &steps);
	  else if (t->top2 <= 100)
	  ft_selection_sort(tab, t, &steps);*/
	/*handler(tab, t, "pb", t->opt); 
	  handler(tab, t, "pb", t->opt); 
	  handler(tab, t, "pb", t->opt); 
	  ft_printf("minidx : %d\n", getmininsertidx(tab, t->top1 + 1, t->top2, 3) + t->top1 + 1);*/
	//move_elem(t, 3, &steps);
	//apply_steps(tab, t, &steps);
	//ft_printf("minidx : %d\n", getmininsertidx(tab, t->top1 + 1, t->top2, 6));
	//ft_dispstk(tab, t->top1, t->top2);
	//handler(tab, t, "pb", t->opt); 
	//handler(tab, t, "pb", t->opt);
	//ft_printf("%d\n", getx(tab, t, 0));*/
	/*ft_lstpushback(&steps, "pb", 2);
	ft_lstpushback(&steps, "ra", 2);
	ft_lstpushback(&steps, "ra", 2);
	ft_lstpushback(&steps, "ra", 2);
	ft_lstpushback(&steps, "ra", 2);
	ft_lstpushback(&steps, "ra", 2);
	ft_lstpushback(&steps, "ra", 2);
	ft_lstpushback(&steps, "ra", 2);
	ft_lstpushback(&steps, "ra", 2);
	ft_lstpushback(&steps, "rb", 2);
	ft_lstpushback(&steps, "rb", 2);
	ft_lstpushback(&steps, "rb", 2);
	ft_lstpushback(&steps, "rb", 2);
	ft_lstpushback(&steps, "rb", 2);
	ft_lstpushback(&steps, "pb", 2);
	init_op(&op);
	optimize(tab, t, &op, &steps);*/
	//ft_printf("%d\n", op.ra);
	/*if (t->top2 <= 2)
		small_sort(tab, t, &steps);
	else if (t->top2 <= 45)
	  ft_selection_sort(tab, t, &steps);
	else*/
	/*ft_printf("%d\n", get_minmedcost(tab, t, 45));
	handler(tab, t, "pb", t->opt);
	ft_printf("%d\n", get_minmedcost(tab, t, 45));
	handler(tab, t, "ra", t->opt);
	handler(tab, t, "pb", t->opt);
	ft_printf("%d\n", get_minmedcost(tab, t, 45));
	handler(tab, t, "pb", t->opt);
	ft_printf("%d\n", get_minmedcost(tab, t, 45));*/
	/*handler(tab, t, "pb", t->opt);
	ft_printf("%d\n", get_minmedcost(tab, t, 45));
	handler(tab, t, "pb", t->opt);
	ft_printf("%d\n", get_minmedcost(tab, t, 45));*/
	neww_sort(tab, t, &op, &steps);
	//ft_printf("%d\n", ft_printf("{red}toto{eoc}\n"));
	/*int		med;

	med = getmedian(tab, t->top1); 
	ft_printf("%d\n", get_minmedcost(tab, t, med));*/
	//optimize(tab, t, &op, &steps);
	apply_steps(tab, t, &steps);
	/*handler(tab, &t, "pb", opt); 
	  handler(tab, &t, "pb", opt); 
	  handler(tab, &t, "pb", opt);
	  ft_printf("%d\n", get_mininsertcost(tab, &t));*/
	//move_elem(tab, &t, get_mininsertcost(tab, &t), opt);
	//move_elem(tab, &t, 5, opt);
	//move_elem(tab, &t, 6, opt);
	//move_elem(tab, &t, 7, opt);
	//move_elem(tab, &t, 1, opt);
	/*handler(tab, t, "pb", t->opt); 
	  handler(tab, t, "pb", t->opt); 
	  handler(tab, t, "pb", t->opt); 
	  handler(tab, t, "pb", t->opt); 
	  move_elem(t, 5, &steps);
	  apply_steps(tab, t, &steps);*/
	//move_elem(t, 2, &steps);
	//move_elem(t, 3, &steps);
	//move_elem(t, 4, &steps);
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
