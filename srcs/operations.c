/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 22:14:03 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/14 15:29:44 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		rotate_t(int **tab, int top1, int top2, int b)
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

void		rotate_b(int **tab, int top1, int top2, int b)
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

void		push(int **tab, int *top1, int top2, int b)
{
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
