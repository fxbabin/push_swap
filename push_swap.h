/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:52:45 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/05 22:43:24 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP

/*
** --------------------------------- INCLUDES -------------------------------
*/

# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line.h"

/*
** ----------------------------------------------------------------------------
** ---------------------------------- SOURCES ---------------------------------
** ----------------------------------------------------------------------------
*/

/*
** ------------------------------ CHECKS FUNCTIONS -----------------------------
*/

int			**ft_checknumbers(int argc, char **argv);
int			ft_checkdoubles(int **tab, int argc);
int			ft_checkinr(char *line, int **tab, int *top1, int top2);
int			ft_checkins(char *line, int **tab, int *top1, int top2);
int			is_sorted(int **tab, int top1, int top2);

/*
** ---------------------------- OPERATIONS FUNCTIONS ---------------------------
*/

void		rotate_t(int **tab, int top1, int top2, int b);
void		rotate_b(int **tab, int top1, int top2, int b);
void		push(int **tab, int *top1, int top2, int b);

/*
** ----------------------------- DISPLAY FUNCTIONS -----------------------------
*/

void			ft_dispstk(int **tab, int top1, int top2);

/*
** ------------------------------- UTILS FUNCTIONS -----------------------------
*/

int				ft_error(int nb);
int				ft_wordnb(char *str, char *charset);
int				tabsize(char **tab);
void			free2(void **tab, int size);
char			**modif_argv(int argc, char **argv);

#endif
