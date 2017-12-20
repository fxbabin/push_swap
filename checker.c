/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:44:39 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/20 23:29:10 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

/*check instructions*/
/*check numbers, pas de doublons*/
/*stack functions*/

void		ft_exit(int fd)
{
	ft_fprintf(fd, "Error\n");
	exit(fd);
}

/*typedef struct		s_stk
  {
  int				*stk;
  int				top1;
  int				top2;
  }					t_stk;*/

void	ft_intdump(int *array, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		ft_putstr("[");
		ft_putnbr(array[i]);
		ft_putstr("] ");
	}
	ft_putstr("\n");
}

int		*ft_checknumbers(int argc, char **argv)
{
	int		*tab;
	int		i;
	int		nb;

	i = 0;
	if (!(tab = (int*)ft_memalloc(argc)))
		return (NULL);
	while (++i < argc)
	{
		nb = (argv[i][0] == '-') ? 1 : 0;
		if (!ft_strbspn(argv[i] + nb, "0123456789"))
			return (NULL);
		nb = ft_atoi(argv[i]);
		if (nb != ft_atol(argv[i]))
			return (NULL);
		tab[i - 1] = nb;
	}
	return (tab);
}

void	*ft_memmdup(const void *s, size_t i)
{
	void	*str;

	if (!s)
		return (NULL);
	if (!(str = malloc((i + 1))))
		return (NULL);
	ft_memcpy(str, s, i + 1);
	return (str);
}

int		ft_checkdoubles(int *tab, int argc)
{
	int		*tmp;
	int		i;

	i = -1;
	ft_intdump(tab, argc - 1);
	tmp = ft_memmdup(tab, sizeof(int) * (argc - 1));
	ft_intdump(tab, argc - 1);
	ft_intdump(tmp, argc - 1);
	ft_quicksort(tmp, 0, argc - 2);
	ft_intdump(tmp, argc - 1);
	while (++i < argc - 3)
	{
		if (tmp[i] == tmp[i + 1])
		{
			free(tmp);
			return (0);
		}
	}
	free(tmp);
	return (1);
}

int		main(int argc, char **argv)
{
	int		*stk;

	if (argc < 2)
		ft_exit(2);
	if (!(stk = ft_checknumbers(argc, argv)))
		ft_exit(2);
	ft_intdump(stk, argc - 1);
	int		*tmp;

	tmp = ft_memmdup(stk, sizeof(int) * (argc));
	ft_intdump(stk, argc - 1);
	ft_intdump(tmp, argc - 1);
	//if (!ft_checkdoubles(stk, argc))
	//	printf("ok\n");
	//ft_quicksort(stk, 0, argc - 2);
	//ft_intdump(ft_memdup(stk, sizeof(int) * (argc - 1)), argc - 1);
	//ft_intdump(stk, argc - 1);
	/*char	*line;
	  get_next_line(0, &line);
	  printf("%s\n", line);*/
	//printf("%d\n", ft_strbspn(argv[1], "0123456789"));
	//ft_checknumbers(argc, argv);
	/*int		i;

	  i = 0;
	  while (++i < argc)
	  ft_printf("%s\n", argv[i]);*/
	/*int		**stk;

	  stk = get_numbers(argc, argv);
	  ft_int2dump(stk, argc - 2);*/

	return (0);
}
