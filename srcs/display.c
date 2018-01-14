/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 22:16:38 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/14 22:11:00 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			ft_dispstk(int **tab, int top1, int top2)
{
	int		i;

	i = 0;
	ft_putstr("stack_1 :");
	while (i <= top1)
		ft_printf(" [%d]", *tab[i++]);
	ft_printf("\nstack_2 :");
	i = top1;
	while (++i <= top2)
		ft_printf(" [%d]", *tab[i]);
	ft_printf("\n----------------------------------------------------------\n");
}

static void		ft_coldisp2(const char *s)
{
	if (s[0] == 'r' && ft_strlen(s) == 2)
	{
		if (s[1] == 'a')
			ft_printf("\033[22;32m%s{eoc}\n", s);
		else if (s[1] == 'b')
			ft_printf("\033[01;32m%s{eoc}\n", s);
		else if (s[1] == 'r')
			ft_printf("\033[22;33m%s{eoc}\n", s);
	}
	else if (s[0] == 'r' && s[1] == 'r' && ft_strlen(s) == 3)
	{
		if (s[2] == 'a')
			ft_printf("\033[22;36m%s{eoc}\n", s);
		else if (s[2] == 'b')
			ft_printf("\033[01;36m%s{eoc}\n", s);
		else if (s[2] == 'r')
			ft_printf("\033[01;34m%s{eoc}\n", s);
	}
}

static void		ft_coldisp(const char *s)
{
	if (s[0] == 's')
	{
		if (s[1] == 'a')
			ft_printf("\033[22;31m%s{eoc}\n", s);
		else if (s[1] == 'b')
			ft_printf("\033[01;31m%s{eoc}\n", s);
		else if (s[1] == 's')
			ft_printf("\033[01;33m%s{eoc}\n", s);
	}
	if (s[0] == 'p')
	{
		if (s[1] == 'a')
			ft_printf("\033[22;35m%s{eoc}\n", s);
		else if (s[1] == 'b')
			ft_printf("\033[01;35m%s{eoc}\n", s);
	}
	ft_coldisp2(s);
}

int				ft_disp(int **tab, t_ps *t, const char *s, int opt)
{
	if (opt == 1 || opt == 0)
		ft_coldisp(s);
	else
		ft_printf("%s\n", s);
	if (opt == 2 || opt == 0)
		ft_dispstk(tab, t->top1, t->top2);
	return (1);
}

void			handler(int **tab, t_ps *t, const char *s, int opt)
{
	if (s[0] == 's')
	{
		(t->top1 > 0 && (s[1] == 'a' || s[1] == 's'))
			? ft_swap(tab[0], tab[1]) : 0;
		((t->top2 - t->top1 + 1 > 1) && (s[1] == 'b' || s[1] == 's')) ?
			ft_swap(tab[t->top1 + 1], tab[t->top1 + 2]) : 0;
	}
	if (s[0] == 'p')
	{
		(s[1] == 'a') ? push(tab, &(t->top1), t->top2, 2) : 0;
		(s[1] == 'b') ? push(tab, &(t->top1), t->top2, 1) : 0;
	}
	if (s[0] == 'r' && ft_strlen(s) == 2)
	{
		(s[1] == 'a' || s[1] == 'r') ? rotate_t(tab, t->top1, t->top2, 1) : 0;
		(s[1] == 'b' || s[1] == 'r') ? rotate_t(tab, t->top1, t->top2, 2) : 0;
	}
	else if (s[0] == 'r' && s[1] == 'r' && ft_strlen(s) == 3)
	{
		(s[2] == 'a' || s[2] == 'r') ? rotate_b(tab, t->top1, t->top2, 1) : 0;
		(s[2] == 'b' || s[2] == 'r') ? rotate_b(tab, t->top1, t->top2, 2) : 0;
	}
	ft_disp(tab, t, s, opt);
}
