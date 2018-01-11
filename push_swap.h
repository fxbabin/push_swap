/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:52:45 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/11 13:55:59 by fbabin           ###   ########.fr       */
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
** -------------------------------- STRUCTURES -------------------------------
*/

typedef struct		s_ps
{
	int				top1;
	int				top2;
	int				opt;
}					t_ps;

typedef struct		s_op
{
	int				ra;
	int				rra;
	int				rb;
	int				rrb;
}					t_op;

/*
** ----------------------------------------------------------------------------
** ---------------------------------- SOURCES ---------------------------------
** ----------------------------------------------------------------------------
*/

/*
** ------------------------------- SORT FUNCTIONS -----------------------------
*/

int				small_sort(int **tab, t_ps *t, t_list **steps);
void			ft_selection_sort(int **tab, t_ps *t, t_list **steps);

void			move_elem(t_ps *t, int idx, t_list **steps);
int				is_relsorted(int **tab, int start, int end);
int				is_relrsorted(int **tab, int start, int end);

/*
** ------------------------------ CHECKS FUNCTIONS -----------------------------
*/

int				**ft_checknumbers(int argc, char **argv, int opt);
int				ft_checkdoubles(int **tab, int argc);
int				ft_checkinr(char *line, int **tab, int *top1, int top2);
int				ft_checkins(char *line, int **tab, int *top1, int top2);
int				is_sorted(int **tab, int top1, int top2);

/*
** ---------------------------- OPERATIONS FUNCTIONS ---------------------------
*/

void			rotate_t(int **tab, int top1, int top2, int b);
void			rotate_b(int **tab, int top1, int top2, int b);
void			push(int **tab, int *top1, int top2, int b);

/*
** ----------------------------- DISPLAY FUNCTIONS -----------------------------
*/

void			ft_dispstk(int **tab, int top1, int top2);
int				ft_disp(int **tab, t_ps *t, const char *s, int opt);
void			handler(int **tab, t_ps *t, const char *s, int opt);

/*
** ------------------------------ GETS FUNCTIONS -------------------------------
*/

int				getopts(const char *opt);
int				getmedian(int **tab, int top);
int				get_min(int **tab, int start, int end);
int				get_max(int **tab, int start, int end);

/*
** ------------------------------ UTILS FUNCTIONS -----------------------------
*/

int				ft_error(int nb);
int				ft_wordnb(char *str, char *charset);
int				tabsize(char **tab);
void			free2(void **tab, int size);
char			**modif_argv(int argc, char **argv, int opt);
int				**cpytab(int **tab, int size);
void			ft_eldel(void *content, size_t content_size);
void			apply_steps(int **tab, t_ps *t, t_list **list);

#endif
