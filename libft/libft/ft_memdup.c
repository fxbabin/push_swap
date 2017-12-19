/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 22:08:51 by fbabin            #+#    #+#             */
/*   Updated: 2017/11/14 16:20:19 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *s)
{
	size_t	i;
	void	*str;

	if (!s)
		return (NULL);
	i = ft_strlen((char*)s);
	if ((str = (void*)malloc((i + 1) * sizeof(void))) == NULL)
		return (NULL);
	ft_memcpy(str, s, i);
	return (str);
}
