/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:40:47 by alexanfe          #+#    #+#             */
/*   Updated: 2024/10/22 19:40:49 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer	buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer.position >= buffer.total_read || buffer.position == 0)
	{
		buffer = init_clean_buffer(&buffer, fd);
		if (buffer.total_read <= 0)
		{
			if (buffer.string)
				clear_string(buffer.string);
			return (NULL);
		}
	}
	return (get_current_line(&buffer));
}
