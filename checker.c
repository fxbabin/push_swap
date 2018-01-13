/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:44:39 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/13 16:03:22 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		main(int argc, char **argv)
{
	int			**tab;
	int			top1;
	int			top2;
	char		*line;

	line = NULL;
	if (argc < 2)
		return (ft_error(-1));
	argv = modif_argv(argc, argv, -1);
	argc = (argc != tabsize(argv)) ? tabsize(argv) : argc;
	top1 = argc - 2;
	top2 = argc - 2;
	if (!(tab = ft_checknumbers(argc, argv, -1)))
		return (ft_error(-1));
	if (!(ft_checkdoubles(tab, top2)))
		return (ft_error(-1));
	while (get_next_line(0, &line) > 0)
		if (!ft_checkins(line, tab, &top1, top2))
			return (ft_error(-1));
	free(line);
	if (argv[0][0] == 'x')
		free2((void**)argv, tabsize(argv));
	(is_sorted(tab, top1, top2)) ? ft_printf("OK\n") : ft_printf("KO\n");
	free2((void**)tab, top2);
	return (0);
}
