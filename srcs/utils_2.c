/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 13:36:42 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/15 15:33:41 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_exit(int nb)
{
	ft_fprintf(2, "Error\n");
	exit(nb);
}

void		*ft_free2(void **tab, int size)
{
	free2(tab, size);
	return (NULL);
}

int			**cpytab(int **tab, int size)
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

void		apply_steps(int **tab, t_ps *t, t_list **list)
{
	t_list		*l;

	if (!list || !*list)
		return ;
	l = *list;
	while ((*list))
	{
		if ((*list)->content)
			handler(tab, t, (char*)(*list)->content, t->opt);
		*list = (*list)->next;
	}
	*list = l;
	ft_lstdel(list, ft_eldel);
	*list = NULL;
}

void		ft_eldel(void *content, size_t content_size)
{
	(void)content_size;
	(void)content;
}
