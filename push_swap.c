/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:54:52 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/04 22:06:01 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		ft_error(int nb)
{
	ft_fprintf(2, "Error\n");
	return (nb);
}

int		**ft_checknumbers(int argc, char **argv)
{
	int		**tab;
	int		i;
	int		nb;

	i = 0;
	tab = NULL;
	if (!(tab = (int**)ft_memalloc2(argc - 1, 1)))
		return (NULL);
	tab[argc - 1] = NULL;
	while (++i < argc)
	{
		nb = (argv[i][0] == '-') ? 1 : 0;
		if (!ft_strbspn(argv[i] + nb, "0123456789"))
			return (NULL);
		nb = ft_atoi(argv[i]);
		if (nb != ft_atol(argv[i]))
			return (NULL);
		*tab[i - 1] = nb;
	}
	return (tab);
}

int		ft_checkdoubles(int **tab, int argc)
{
	int		i;
	int		y;

	i = -1;
	while (++i < argc - 2) 
	{
		y = i;
		while (++y < argc - 1)
		{
			if (*tab[i] == *tab[y])
				return (0);
		}
	}
	return (1);
}

void	ft_dispstk(int **tab, int top1, int top2)
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
	ft_printf("\n");
}

void	rotate_t(int **tab, int top1, int top2, int b)
{
	int		tmp;

	if ((b == 0 || b == 1) && top1 > 0)
	{
		ft_swap(tab[0], tab[top1]);
		tmp = -1;
		if (top1 > 1)
			while (++tmp < top1 - 1)
				ft_swap(tab[tmp], tab[tmp + 1]);
	}
	if ((b == 0 || b == 2) && top2 > 0 && (top1 + 1) <= top2)
	{
		ft_swap(tab[top1 + 1], tab[top2]);
		tmp = top1;
		if ((top2 - top1) > 1)
			while (++tmp < top2 - 1)
				ft_swap(tab[tmp], tab[tmp + 1]);
	}
}

void	rotate_b(int **tab, int top1, int top2, int b)
{
	int		tmp;

	if ((b == 0 || b == 1) && top1 > 0)
	{
		ft_swap(tab[0], tab[top1]);
		tmp = top1;
		if (top1 > 1)
			while (--tmp >= 1)
				ft_swap(tab[tmp], tab[tmp + 1]);
	}
	if ((b == 0 || b == 2) && top2 > 0 && (top1 + 1) < top2)
	{
		ft_swap(tab[top1 + 1], tab[top2]);
		tmp = top2;
		if ((top2 - top1) > 1)
			while (--tmp > top1 + 1)
				ft_swap(tab[tmp], tab[tmp + 1]);
	}
}

void	push(int **tab, int *top1, int top2, int b)
{
	int		tmp;

	if ((b == 0 || b == 1) && *top1 >= 0)
	{
		rotate_t(tab, *top1, top2, 1);
		*top1 -= 1;
	}
	if ((b == 0 || b == 2) && *top1 + 1 <= top2)
	{
		*top1 += 1;
		rotate_b(tab, *top1, top2, 1);
	}
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
	//ft_dispstk(tab, top1, top2);
	if (max == 0)
	{
		rotate_t(tab, top1, top2, 1);
		ft_printf("ra\n");
	}
	else if (max == 1)
	{
		rotate_b(tab, top1, top2, 1);
		ft_printf("rra\n");
	}
	//ft_dispstk(tab, top1, top2);
	if (*tab[0] > *tab[1])
	{
		ft_swap(tab[0], tab[1]);
		ft_printf("sa\n");
	}
	//ft_dispstk(tab, top1, top2);
	return (0);
}
int		main(int argc, char **argv)
{
	int			**tab;
	int			top1;
	int			top2;

	top1 = argc - 2;
	top2 = argc - 2;
	if (argc < 2)
		return (ft_error(-1));
	if (!(tab = ft_checknumbers(argc, argv)))
		return (ft_error(-1));
	if (!(ft_checkdoubles(tab, argc)))
		return (ft_error(-1));
	//ft_dispstk(tab, top1, top2);
	small_sort(tab, top1, top2);
	//ft_dispstk(tab, top1, top2);
	return (0);
}
