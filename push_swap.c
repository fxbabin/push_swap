/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:54:52 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/10 23:24:29 by fbabin           ###   ########.fr       */
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
	else if (elem == 0 && elem > *tab[start] && elem < *tab[end])
		return (0);
	else
	{
		while (++i <= end)
		{
			if (elem < *tab[i - 1] && elem > *tab[i])
				return (i - start);
		}
	}
	return (-1);
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
	//(void)tab;
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
	//ft_printf("%d %d\n", score, midx);
	return (midx);
}

void	new_sort(int **tab, t_ps *t, t_list **steps)
{
	int		idx1;
	int		idx2;

	while (t->top1 >= 0)
	{
		idx1 = get_mininsertcost(tab, t);
		if (t->top2 - t->top1 > 0)
			idx2 = getmininsertidx(tab, t->top1 + 1, t->top2, *tab[idx1]);
		else
			idx2 = 0;
		move_elem(t, idx1, steps);
		move_elem(t, idx2 + t->top1, steps);
		ft_lstpushback(steps, "pb", 2);
		apply_steps(tab, t, steps);
		ft_lstdel(steps, ft_eldel);
		*steps = NULL;
	}
	while (t->top1 < t->top2)
		handler(tab, t, "pa", t->opt);
	move_elem(t, get_min(tab, 0, t->top1), steps);
}

int		inner_main(int argc, char **argv, t_ps *t)
{
	int			**tab;
	t_list		*steps;

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
	ft_dispstk(tab, t->top1, t->top2);
	new_sort(tab, t, &steps);
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
