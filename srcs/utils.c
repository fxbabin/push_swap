/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 22:05:02 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/14 15:31:10 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			ft_error(int nb)
{
	ft_fprintf(2, "Error\n");
	return (nb);
}

int			ft_wordnb(char *str, char *charset)
{
	int		w;
	int		i;

	w = 0;
	i = -1;
	while (str[++i])
		if ((ft_charinset(str[i], charset) == 0) &&
			((ft_charinset(str[i + 1], charset) == 1) || str[i + 1] == '\0'))
			w++;
	return (w);
}

int			tabsize(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

void		free2(void **tab, int size)
{
	int		i;

	i = size;
	while (i >= 0)
		free(tab[i--]);
	free(tab);
}

char		**modif_argv(int argc, char **argv, int opt)
{
	char	*tmp;
	int		idx;

	tmp = NULL;
	idx = (opt > -1) ? 2 : 1;
	if (argc == (idx + 1) && ft_wordnb(argv[idx], " ") > 1)
		argc = -1;
	if (argc == -1)
		tmp = ft_strjoinclr("x ", argv[idx], 3);
	if (argc == -1)
		argv = ft_strsplit(tmp, ' ');
	if (tmp)
		free(tmp);
	return (argv);
}
