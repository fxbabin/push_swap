/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:44:39 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/04 20:33:25 by fbabin           ###   ########.fr       */
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

int		ft_checkinr(char *line, int **tab, int *top1, int top2)
{
	int		slen;

	slen = ft_strlen(line);
	if (slen == 2)
	{
		if ((line[1] == 'a' || line[1] == 'r') && *top1 > 0)
			rotate_t(tab, *top1, top2, 1);
		if ((line[1] == 'b' || line[1] == 'r') && *top1 < top2)
			rotate_t(tab, *top1, top2, 2);
	}
	else if (slen == 3 && line[1] == 'r')
	{
		if ((line[2] == 'a' || line[2] == 'r') && *top1 > 0)
			rotate_b(tab, *top1, top2, 1);
		if ((line[2] == 'b' || line[2] == 'r') && *top1 < top2)
			rotate_b(tab, *top1, top2, 2);
	}
	else
		return (0);
	return (1);
}

int		ft_checkins(char *line, int **tab, int *top1, int top2)
{
	int		slen;

	slen = ft_strlen(line);
	if (slen > 3 || !ft_strbspn(line, "sabrp"))
		return (0);
	if (line[0] == 's' && slen == 2)
	{
		if ((line[1] == 'a' || line[1] == 's') && *top1 > 0)
			ft_swap(tab[0], tab[1]);
		if ((line[1] == 'b' || line[1] == 's') && *top1 < top2)
			ft_swap(tab[*top1 + 1], tab[top2]);
	}
	else if (line[0] == 'p' && slen == 2)
	{
		if (line[1] == 'a' && *top1 < top2)
			push(tab, top1, top2, 2);
		if (line[1] == 'b' && *top1 >= 0)
			push(tab, top1, top2, 1);
	}
	else if (line[0] == 'r' && ft_checkinr(line, tab, top1, top2))
		;
	else
		return (0);
	return (1);
}

int		is_sorted(int **tab, int top1, int top2)
{
	int		i;

	i = 0;
	if (top1 < top2)
		return (0);
	if (top2 == 0)
		return (1);
	while (++i <= top2)
	{
		if (*tab[i - 1] >= *tab[i])
			return (0);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int			**tab;
	int			top1;
	int			top2;
	char		*line;

	top1 = argc - 2;
	top2 = argc - 2;
	if (argc < 2)
		return (ft_error(-1));
	if (!(tab = ft_checknumbers(argc, argv)))
		return (ft_error(-1));
	if (!(ft_checkdoubles(tab, argc)))
		return (ft_error(-1));
	while (get_next_line(0, &line) > 0)
	{
		if (!ft_checkins(line, tab, &top1, top2))
			return (ft_error(-1));
	}
	if (is_sorted(tab, top1, top2))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	return (0);
}
