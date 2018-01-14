/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:54:52 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/14 23:11:45 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	if (is_sorted(tab, t->top1, t->top2))
		return (0);
	if (t->top2 <= 2)
		small_sort(tab, t, &steps);
	else if (t->top2 <= 5)
		ft_selection_sort(tab, t, 5, &steps);
	else if (t->top2 <= 45)
		advselection_sort(tab, t, &op, &steps);
	else
		opti_sort(tab, t, &op, &steps);
	if (**argv == 'x')
		free2((void**)argv, tabsize(argv));
	free2((void**)tab, t->top2);
	(steps) ? ft_lstdel(&steps, ft_eldel) : 0;
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
