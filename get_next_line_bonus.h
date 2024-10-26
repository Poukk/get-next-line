/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:29:17 by alexanfe          #+#    #+#             */
/*   Updated: 2024/10/22 20:30:30 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_string
{
	char			character;
	struct s_string	*next;
}	t_string;

typedef struct s_buffer
{
	int			position;
	int			total_read;
	int			length;
	int			fd;
	char		buffer[BUFFER_SIZE];
	t_string	*string;
}	t_buffer;

char		*get_next_line(int fd);

t_buffer	init_clean_buffer(t_buffer *buffer, int fd);
void		clear_string(t_string *str);
void		build_string(t_string **string_head, char character);
char		*alloc_line(t_buffer *buffer);
char		*get_current_line(t_buffer *buffer);

#endif
