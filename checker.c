/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:44:39 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/03 23:00:35 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

/*check instructions*/
/*check numbers, pas de doublons*/
/*stack functions*/

void		ft_exit(int fd)
{
	ft_fprintf(2, "Error\n");
	exit(fd);
}

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

void	rotate(int **tab, int top1, int top2, int b)
{
	int		tmp;

	if (b == 1 && top1 > 0)
	{
		ft_swap(tab[0], tab[top1]);
		tmp = -1;
		if (top1 > 1)
			while (++tmp < top1 - 1)
				ft_swap(tab[tmp], tab[tmp + 1]);
	}
	if (b == 2 && top2 > 0 && (top1 + 1) <= top2)
	{
		ft_swap(tab[top1 + 1], tab[top2]);
		tmp = top1;
		if ((top2 - top1) > 1)
			while (++tmp < top2 - 1)
				ft_swap(tab[tmp], tab[tmp + 1]);
	}
}

void	push(int **tab, int *top1, int top2, int b)
{
	int		tmp;

	if (b == 1 && *top1 >= 0)
	{
		rotate(tab, *top1, top2, 1);
		*top1 -= 1;
	}
	if (b == 2 && *top1 + 1 <= top2)
	{
		*top1 += 1;
		if (*top1 < top2 - 1)
			rotate(tab, *top1, top2, 1);
	}
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
	//ft_int2dump(tab, argc - 2);
	ft_dispstk(tab, top1, top2);
	//ft_swap(tab[0], tab[1]);
	rotate(tab, top1, top2, 1);
	ft_dispstk(tab, top1, top2);
	rotate(tab, top1, top2, 1); 
	ft_dispstk(tab, top1, top2);
	rotate(tab, top1, top2, 1); 
	ft_dispstk(tab, top1, top2);
	rotate(tab, top1, top2, 1); 
	ft_dispstk(tab, top1, top2);
	push(tab, &top1, top2, 1); 
	ft_dispstk(tab, top1, top2);
	push(tab, &top1, top2, 1); 
	ft_dispstk(tab, top1, top2);
	push(tab, &top1, top2, 1); 
	ft_dispstk(tab, top1, top2);
	printf("%d %d\n", top1, top2);
	/*rotate(tab, top1, top2, 2); 
	ft_dispstk(tab, top1, top2);*/
	push(tab, &top1, top2, 2); 
	ft_dispstk(tab, top1, top2);
	push(tab, &top1, top2, 2); 
	ft_dispstk(tab, top1, top2);
	push(tab, &top1, top2, 2); 
	ft_dispstk(tab, top1, top2);

	//ft_int2dump(tab, argc - 2);
	//ft_int2dump(tab, argc - 2);
	return (0);
}
