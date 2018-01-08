/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:54:52 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/08 21:55:05 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*typedef struct		s_top
  {
  int				top1;
  int				top2;
  }					t_top;
  */
/*void	top_init(t_top *t)
  {
  t->top1 = 0;
  t->top2 = 0;
  }*/

void		handler(int **tab, t_top *t, const char *s, int opt)
{
	if (s[0] == 's')
	{
		(s[1] == 'a' || s[1] == 's') ? ft_swap(tab[0], tab[1]) : 0;
		if (s[1] == 'b' || s[1] == 's')
			ft_swap(tab[t->top1 + 1], tab[t->top1 + 2]);
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

int		small_sort(int **tab, t_top *t, int opt)
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
		handler(tab, t, "ra", opt); 
	else if (max == 1 && t->top1 == 2)
		handler(tab, t, "rra", opt); 
	if (*tab[0] > *tab[1])
		handler(tab, t, "sa", opt); 
	return (0);
}

int		**cpytab(int **tab, int size)
{
	int		**new;
	int		i;

	i = -1;
	(void)tab;
	if (!(new = (int**)ft_memalloc2(size + 1, 1)))
		return (NULL);
	new[size + 1] = NULL;
	while (++i <= size)
		*new[i] = *tab[i];
	return (new);
}

/*void	medium_sort(int **tab, t_top *t, int opt)
{
	int		**stab;

	(void)opt;
	stab = cpytab(tab, t->top2);
	ft_int2dump(stab, t->top2);
	ft_quicksort(stab, 0, t->top2);
	ft_int2dump(stab, t->top2);
	free2((void**)stab, t->top2 - 1);
}*/

/*void	medium_sort(int **tab, t_top *t, int opt)
{
	int		**stab;

	(void)opt;
	stab = cpytab(tab, t->top2);
	ft_int2dump(stab, t->top2);
	ft_quicksort(stab, 0, t->top2);
	ft_int2dump(stab, t->top2);
	free2((void**)stab, t->top2 - 1);
}*/


/*int		get_mincost(int **tab, t_top *t)
{
	int		score;
	int		min;
	int		i;

	i = -1;
	min = t->top2;
	(void)tab;
	while (++i < t->top1)
	{
		score = (i < t->top1 / 2) ? i + 1 : t->top1 - i + 1;
		//score++;
		if (score < min)
			min = score;
	}
	return (min);
}*/

int		getopts(const char *opt)
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

int		getmedian(int **tab, int top)
{
	int		**stab;
	int		med;

	stab = cpytab(tab, top);
	ft_quicksort(stab, 0, top);
	//ft_int2dump(stab, t->top2);
	//ft_printf("%d\n", *stab[t->top2 / 2]);
	med = *stab[top / 2];
	free2((void**)stab, top - 1);
	return (med);
}

/*int		get_pushcost(int idx, t_top *t)
{
	int		i;
	int		med;

	med = t->top1 / 2;
	i =  med;
	if (idx < med)
		i = idx;
	else if (idx > med)
		i = (t->top1 + 1) - idx;
	return (i);
}*/

/*int		getmin(int **tab, t_top *t, int med)
{
	int		min;
	int		midx;
	int		i;

	i = -1;
	min = t->top1;
	midx = min;
	//ft_printf("%d\n", med);
	while (++i <= t->top1)
	{
		if (*tab[i] < med)
		{
			//ft_printf("%d %d\n", *tab[i], i);
			if (get_pushcost(i, t) < min)
			{	
				//ft_printf("min %d\n", min);
				min = get_pushcost(i, t);
				midx = i;
				//ft_printf("min %d idx %d\n", min, i);
			}
		}
	}
	//ft_printf("midx %d min %d\n", midx, min);
	return (midx);
}*/

void	swap2b(int **tab, t_top *t, int idx, int opt)
{

	//(void)t;
	/*if (idx == 0)
		ft_printf("prev %d\n", *tab[t->top1]);
	else
		ft_printf("prev %d\n", *tab[idx - 1]);
	ft_printf("curr %d\n", *tab[idx]);
	if (idx == t->top1)
		ft_printf("next %d\n", *tab[0]);
	else
		ft_printf("next %d\n", *tab[idx + 1]);*/

	while (idx > 0)
	{
		if (idx <= t->top1 / 2)
		{
			handler(tab, t, "ra", opt);
			idx = (idx == t->top1) ? 0 : idx + 1;
		}
		if (idx <= t->top1 / 2)
		{
			handler(tab, t, "rra", opt);
			idx--;
		}
	}
}

int		get_min(int **tab, int start, int end)
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

int		get_max(int **tab, int start, int end)
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

/*int		get_mincost(int **tab, t_top *t)
{
	int		midx;
	int		min;
	int		i;

	i = 0;
	min = *tab[0];

	while (++i <= t->top1)
	{
		if (*tab[i] < min)
		{
			min = *tab[i];
			midx = i;
		}
	}
	return (midx);
}*/

void	move_min(int **tab, t_top *t, int min, int opt)
{
	if (min == 1 && *tab[0] > *tab[1])
		handler(tab, t, "sa", opt);
	else if (min > 1)
	{
		if (min <= t->top1 / 2)
		{
			while (min--)
				handler(tab, t, "ra", opt);
		}
		else if (min > t->top1 / 2)
		{
			while (min <= t->top1 && min++)
				handler(tab, t, "rra", opt);
		}
	}
}

void	move_elem(int **tab, t_top *t, int idx, int opt)
{
	//if (min == 1 && *tab[0] > *tab[1])
	//	handler(tab, t, "sa", opt);
	//else if (min > 1)
	//{
	int		start;
	int		end;

	end = (idx <= t->top1) ? t->top1 : t->top2;
	start = (idx <= t->top1) ? 0 : t->top1 + 1;
	if (idx <= (end - start) / 2)
	{
		while (idx-- > start)
			(end == t->top1) ? 
				handler(tab, t, "ra", opt) : handler(tab, t, "rb", opt);
	}
	else if (idx > (end - start) / 2)
	{
		while (idx <= t->top1 && idx++)
			(end == t->top1) ? 
				handler(tab, t, "rra", opt) : handler(tab, t, "rrb", opt);
	}
}
/*void	ft_selection_sort(int **tab, t_top *t, int opt)
{
	int		min;

	while (t->top1 > 2)
	{
		min = get_min(tab, t);
		move_min(tab, t, min, opt);
		if (is_sorted(tab, t->top1, t->top2))
			break ;
		handler(tab, t, "pb", opt); 
	}
	if (t->top1 == 2)
		small_sort(tab, t, opt);
	while (t->top1 < t->top2)
		handler(tab, t, "pa", opt); 
}*/

/*int		get_minsortcost(int **tab, t_top *t)
{
	int		midx;
	int		min;
	int		i;

	i = 0;
	min = *tab[0];
	while (++i <= t->top1)
	{
		if (*tab[i] < min)
		{
			min = *tab[i];
			midx = i;
		}
	}
	return (midx);
}*/

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

int		getinsertidx(int **tab, int start, int end, int elem)
{
	int		i;
	int		max;

	i = start;
	max = get_max(tab, start, end);
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
}

int		inner_main(int argc, char **argv, int opt)
{
	int			**tab;
	t_top		t;
	char		*line;
	//int			med;

	(void)opt;
	line = NULL;
	if (!(tab = ft_checknumbers(argc, argv, opt)))
		return (ft_error(-1));
	t.top1 = (opt > -1 && **argv != 'x') ? argc - 3 : argc - 2;
	t.top2 = t.top1;
	if (!(ft_checkdoubles(tab, t.top2)))
		return (ft_error(-1));
	//med = getmedian(tab, t.top1);
	/*if (t.top2 <= 2)
		small_sort(tab, &t, opt);
	else if (t.top2 <= 100)
		ft_selection_sort(tab, &t, opt);*/
	//ft_printf("%d\n", get_min(tab, 0, 2));
	//ft_printf("%d\n", get_max(tab, 0, 2));
	//ft_printf("%d\n", getinsertidx(tab, 0, t.top1, 3));
	
	move_elem(tab, &t, getinsertidx(tab, 0, t.top1, 4), opt);
	//ft_printf("%d\n", is_relsorted(tab, 0, 2));
	//ft_printf("%d\n", is_relrsorted(tab, 0, 2));
	//handler (tab, &t, "pb", opt);
	//handler (tab, &t, "pb", opt);
	//handler (tab, &t, "pb", opt);
	//handler (tab, &t, "pb", opt);
	//ft_printf("%d\n", is_relrsorted(tab, t.top1 + 1, t.top2));
	
	//wheretoinsert(tab, &t, 4);
	//ft_printf("%d %d\n", med, getmin(tab, &t, med));
	//ft_dispstk(tab, t.top1, t.top2);
	//ft_printf("%d\n", get_min(tab, &t));
	//move_min(tab, &t, get_min(tab, &t), opt);
	//ft_dispstk(tab, t.top1, t.top2);
	
	//swap2b(tab, &t, 2, opt);
	//get
	//getmedian(tab, &t);
	//prot(tab, &t, opt);
	/*ft_dispstk(tab, t.top1, t.top2);
	prot(tab, &t, opt);
	handler(tab, &t, "pb", opt);
	ft_dispstk(tab, t.top1, t.top2);
	prot(tab, &t, opt);
	handler(tab, &t, "pb", opt); 
	ft_dispstk(tab, t.top1, t.top2);
	prot(tab, &t, opt);
	handler(tab, &t, "pb", opt);
	ft_dispstk(tab, t.top1, t.top2);*/
	//prot(tab, &t, opt);
	//handler(
	//ft_printf("%d\n", get_mincost(tab, &t));
	//
	//medium_sort(tab, &t, opt);
	if (**argv == 'x')
		free2((void**)argv, tabsize(argv));
	free2((void**)tab, t.top2);
	return (0);
}

int		main(int argc, char **argv)
{
	//int			**tab;
	//int			top1;
	//int			top2;
	int			opt;

	if (argc < 2)
		return (ft_error(-1));
	opt = getopts(argv[1]);
	argv = modif_argv(argc, argv, opt);
	argc = (argc != tabsize(argv)) ? tabsize(argv) : argc;
	inner_main(argc, argv, opt);
	/*  top1 = argc - 2;
		top2 = argc - 2;
		if (!(tab = ft_checknumbers(argc, argv)))
		return (ft_error(-1));
		if (!(ft_checkdoubles(tab, argc)))
		return (ft_error(-1));*/

	//ft_printf("\033[22;31mOOOKKK{eoc}\n");
	//ft_printf("\033[01;31mOOOKKK{eoc}\n");
	//
	/*ft_coldisp("pa");
	  ft_coldisp("pa");*/
	/*if (argv[0][0] == 'x')
	  free2((void**)argv, tabsize(argv));
	  free2((void**)tab, top2);*/
	//(is_sorted(tab, top1, top2)) ? ft_printf("OK\n") : ft_printf("KO\n");
	return (0);
}
