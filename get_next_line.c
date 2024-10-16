/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:20:01 by alexanfe          #+#    #+#             */
/*   Updated: 2024/10/16 15:22:01 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// remove the line read from buffer
//char	*remove_past_line(char *buffer);
//char *get_next_line(int fd);

#include "get_next_line.h"

char	*read_file(int fd)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		ft_strjoin(buffer, temp);
		
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}

char	*get_line(char *buffer)
{
	char	*line;
	ssize_t	i;

	line = NULL;
	i = 0;
	while (*buffer != '\n' && *buffer != '\0')
	{
		line[i] = buffer[i];
		i++;
	}

	return line;
}
