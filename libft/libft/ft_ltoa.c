/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 22:03:35 by fbabin            #+#    #+#             */
/*   Updated: 2017/11/08 22:03:39 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa(long nb)
{
	char	*str;
	int		i;
	long	tmp;

	i = (nb < 0) ? 2 : 1;
	tmp = (nb < 0) ? -nb : nb;
	while (tmp >= 10 && (tmp /= 10) && i++)
		;
	if ((str = (char*)malloc((i + 1) * sizeof(char))) == NULL)
		return (NULL);
	tmp = (nb < 0) ? -1 : 1;
	nb *= tmp;
	str[i] = '\0';
	while (i-- && (str[i] = nb % 10 + 48))
		nb /= 10;
	if (tmp < 0)
		str[0] = '-';
	return (str);
}
