/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 15:47:25 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/14 17:53:20 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			init_op(t_op *op)
{
	op->ra = 0;
	op->rb = 0;
	op->rra = 0;
	op->rrb = 0;
	op->rr = 0;
	op->rrr = 0;
}

void			optimize_op(t_op *op)
{
	while (op->ra > 0 && op->rb > 0)
	{
		op->rr++;
		op->ra--;
		op->rb--;
	}
	while (op->rra > 0 && op->rrb > 0)
	{
		op->rrr++;
		op->rra--;
		op->rrb--;
	}
}

static void		apply_op2(int **tab, t_ps *t, t_op *op)
{
	while (op->rra > 0 && op->rrb > 0)
	{
		handler(tab, t, "rrr", t->opt);
		op->rra--;
		op->rrb--;
	}
	while (op->rra > 0)
	{
		handler(tab, t, "rra", t->opt);
		op->rra--;
	}
	while (op->rrb > 0)
	{
		handler(tab, t, "rrb", t->opt);
		op->rrb--;
	}
}

void			apply_op(int **tab, t_ps *t, t_op *op)
{
	while (op->ra > 0 && op->rb > 0)
	{
		handler(tab, t, "rr", t->opt);
		op->ra--;
		op->rb--;
	}
	while (op->ra > 0)
	{
		handler(tab, t, "ra", t->opt);
		op->ra--;
	}
	while (op->rb > 0)
	{
		handler(tab, t, "rb", t->opt);
		op->rb--;
	}
	apply_op2(tab, t, op);
}

void			optimize(int **tab, t_ps *t, t_op *op, t_list **list)
{
	t_list		*l;

	if (!list || !*list)
		return ;
	l = *list;
	init_op(op);
	while ((*list))
	{
		if ((*list)->content)
		{
			if (ft_strequ((char*)(*list)->content, "pb"))
			{
				apply_op(tab, t, op);
				init_op(op);
				handler(tab, t, "pb", t->opt);
			}
			op->ra += (ft_strequ((char*)(*list)->content, "ra")) ? 1 : 0;
			op->rb += (ft_strequ((char*)(*list)->content, "rb")) ? 1 : 0;
			op->rra += (ft_strequ((char*)(*list)->content, "rra")) ? 1 : 0;
			op->rrb += (ft_strequ((char*)(*list)->content, "rrb")) ? 1 : 0;
		}
		*list = (*list)->next;
	}
	*list = l;
	ft_lstdel(list, ft_eldel);
}
