/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:44:39 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/19 22:13:00 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

/*check instructions*/
/*check numbers, pas de doublons*/
/*stack functions*/

typedef struct		s_stack
{
	t_list			*lst;
	int				top;
}					t_stack;

/*int		check_numbers(int **tab);
{

}*/

int			ft_isstrdigit(char *str)
{
	int		i;

	i = -1;
	while (str[++i] && ft_isdigit(str[i]))
		;
	if (!str[i])
		return (1);
	return (0);
}

int		**get_numbers(int argc, char **argv)
{
	int			**stk;
	int			i;

	i = 0;
	stk = (int**)ft_memalloc2(argc, 1);
	while (++i < argc)
	{
		if (!ft_isstrdigit(argv[i]))
			return (NULL);
		*stk[i - 1] = ft_atoi(argv[i]);
		//ft_lstpushfront(&lst, argv[i]);
	}
	return (stk);
}

int		main(int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
		ft_printf("%s\n", argv[i]);
	/*int		**stk;

	stk = get_numbers(argc, argv);
	ft_int2dump(stk, argc - 2);*/

	return (0);
}
