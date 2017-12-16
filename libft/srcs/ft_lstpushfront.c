/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:58:48 by fbabin            #+#    #+#             */
/*   Updated: 2017/11/14 13:45:06 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstpushfront(t_list **begin_list, void *content)
{
	t_list	*t;

	if (!begin_list)
		return ;
	if (*begin_list)
	{
		t = ft_lstcreate(content);
		t->next = (*begin_list);
		(*begin_list) = t;
	}
	else
	{
		t = ft_lstcreate(content);
		(*begin_list) = t;
	}
}
