/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 22:09:03 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/16 15:29:55 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			**ft_checknumbers(int argc, char **argv, int opt)
{
	int		**tab;
	int		i;
	int		nb;
	int		b;

	tab = NULL;
	b = (opt > -1 && **argv != 'x') ? 2 : 1;
	if (!(tab = ft_int2alloc(argc - b, 1)))
		return (NULL);
	tab[argc - b] = NULL;
	i = b - 1;
	while (++i < argc)
	{
		nb = (argv[i][0] == '-') ? 1 : 0;
		if (!ft_strbspn(argv[i] + nb, "+0123456789"))
			return (ft_free2((void**)tab, argc - b - 1));
		nb = ft_atoi(argv[i]);
		if (nb != ft_atol(argv[i]))
		{
			free2((void**)tab, argc - b - 1);
			return (NULL);
		}
		*tab[i - b] = nb;
	}
	return (tab);
}

int			ft_checkdoubles(int **tab, int top2)
{
	int		i;
	int		y;

	i = -1;
	while (++i <= top2 - 1)
	{
		y = i;
		while (++y <= top2)
		{
			if (*tab[i] == *tab[y])
				return (0);
		}
	}
	return (1);
}

int			ft_checkinr(char *line, int **tab, int *top1, int top2)
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

int			ft_checkins(char *line, int **tab, int *top1, int top2)
{
	int		slen;
	int		b;

	b = 1;
	slen = ft_strlen(line);
	if (slen > 3 || !ft_strbspn(line, "sabrp"))
		b = 0;
	if (b && line[0] == 's' && slen == 2)
	{
		if ((line[1] == 'a' || line[1] == 's') && *top1 > 0)
			ft_swap(tab[0], tab[1]);
		if ((line[1] == 'b' || line[1] == 's') && *top1 < top2)
			ft_swap(tab[*top1 + 1], tab[top2]);
	}
	else if (b && line[0] == 'p' && slen == 2)
	{
		(line[1] == 'a' && *top1 < top2) ? push(tab, top1, top2, 2) : NULL;
		(line[1] == 'b' && *top1 >= 0) ? push(tab, top1, top2, 1) : NULL;
	}
	else if (line[0] == 'r' && ft_checkinr(line, tab, top1, top2))
		;
	else
		b = 0;
	free(line);
	return (b);
}

int			is_sorted(int **tab, int top1, int top2)
{
	int		**stab;
	int		i;

	i = -1;
	if (top1 < top2)
		return (0);
	if (top2 == 0)
		return (1);
	stab = cpytab(tab, top2);
	ft_quicksort(stab, 0, top2);
	while (++i <= top2)
	{
		if (*tab[i] != *stab[i])
		{
			free2((void**)stab, top2);
			return (0);
		}
	}
	free2((void**)stab, top2);
	return (1);
}
