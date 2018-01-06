/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:54:52 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/06 23:02:21 by fbabin           ###   ########.fr       */
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
		(s[1] == 'a') ? push(tab, &(t->top1), t->top2, 1) : 0;
		(s[1] == 'b') ? push(tab, &(t->top1), t->top2, 2) : 0;
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
	while (++i <= t->top2)
		if (*tab[i] > *tab[max])
			max = i;
	if (max == 0)
		handler(tab, t, "ra", opt); 
	else if (max == 1)
		handler(tab, t, "rra", opt); 
	if (*tab[0] > *tab[1])
		handler(tab, t, "sa", opt); 
	return (0);
}

/*int		**cpytab(int **tab, int size)
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

int		get_mincost(int **tab, t_top *t)
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
}

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

int		inner_main(int argc, char **argv, int opt)
{
	int			**tab;
	t_top		t;
	char		*line;

	(void)opt;
	line = NULL;
	if (!(tab = ft_checknumbers(argc, argv, opt)))
		return (ft_error(-1));
	t.top1 = (opt > -1 && **argv != 'x') ? argc - 3 : argc - 2;
	t.top2 = t.top1;
	if (!(ft_checkdoubles(tab, t.top2)))
		return (ft_error(-1));
	ft_printf("%d\n", get_mincost(tab, &t));
	//small_sort(tab, &t, opt);
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
