/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:54:52 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/05 23:01:52 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_coldisp2(const char *s)
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

void	ft_coldisp(const char *s)
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

int		small_sort(int **tab, int top1, int top2)
{
	int		max;
	int		i;

	i = 0;
	max = 0;
	while (++i <= top2)
	{
		if (*tab[i] > *tab[max])
			max = i;
	}
	if (max == 0)
	{
		rotate_t(tab, top1, top2, 1);
		ft_coldisp("ra");
	}
	else if (max == 1)
	{
		rotate_b(tab, top1, top2, 1);
		ft_coldisp("rra");
	}
	if (*tab[0] > *tab[1])
	{
		ft_swap(tab[0], tab[1]);
		ft_coldisp("sa");
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int			**tab;
	int			top1;
	int			top2;

	if (argc < 2)
		return (ft_error(-1));
	argv = modif_argv(argc, argv);
	argc = (argc != tabsize(argv)) ? tabsize(argv) : argc;
	top1 = argc - 2;
	top2 = argc - 2;
	if (!(tab = ft_checknumbers(argc, argv)))
		return (ft_error(-1));
	if (!(ft_checkdoubles(tab, argc)))
		return (ft_error(-1));
	//ft_char2dump(argv);
	//ft_printf("\033[22;31mOOOKKK{eoc}\n");
	//ft_printf("\033[01;31mOOOKKK{eoc}\n");
	small_sort(tab, top1, top2);
	/*ft_coldisp("pa");
	ft_coldisp("pa");*/
	if (argv[0][0] == 'x')
		free2((void**)argv, tabsize(argv));
	free2((void**)tab, top2);
	//(is_sorted(tab, top1, top2)) ? ft_printf("OK\n") : ft_printf("KO\n");
	return (0);
}
