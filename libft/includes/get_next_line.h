/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:09:10 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/17 21:18:06 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** -------------------------------- INCLUDES ---------------------------------
*/

# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

/*
** --------------------------------- MACROS ---------------------------------
*/

# define BUFF_SIZE 32

/*
** ------------------------------- STRUCTURES ---------------------------------
*/

typedef struct			s_gnl
{
	char				buff[BUFF_SIZE + 1];
	int					fd;
	struct s_gnl		*next;
}						t_gnl;

/*
** -------------------------------- SOURCES ---------------------------------
*/

int						get_next_line(const int fd, char **line);

#endif
