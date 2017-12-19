/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llutoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:18:46 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/02 21:58:33 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_llutoa(unsigned long long nb)
{
	char				*str;
	int					i;
	unsigned long long	tmp;

	i = 1;
	tmp = nb;
	while (tmp >= 10 && (tmp /= 10) && i++)
		;
	if ((str = (char*)malloc((i + 1) * sizeof(char))) == NULL)
		return (NULL);
	tmp = 1;
	nb *= tmp;
	str[i] = '\0';
	while (i-- && (str[i] = nb % 10 + 48))
		nb /= 10;
	return (str);
}
