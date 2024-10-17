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

#include "get_next_line.h"

char    *read_file(int fd, char *buffer)
{
    char	*temp;
	char	*new_buffer;
    ssize_t	bytes_read;

    temp = malloc(BUFFER_SIZE + 1);
    if (!temp)
		return (NULL);
	bytes_read = 1;
    while (!ft_strchr(temp, '\n') && bytes_read > 0)
    {
        bytes_read = read(fd, temp, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(temp);
            return (NULL);
        }
		temp[bytes_read] = '\0';
		new_buffer = ft_strjoin(buffer, temp);
		free(buffer);
		buffer = new_buffer;
		if (!buffer)
		{
			free(temp);
			return (NULL);
		}
	}
	free(temp);
    return (buffer);
}

char	*get_current_line(char	*buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i]  = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	line[i++] = '\0';
	return (line);
}

char	*trim_buffer(char *buffer, char *current_line)
{
	size_t	i;
	char	*new_buffer;

	i = 0;
	while (current_line[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	new_buffer = ft_strdup(buffer + i);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line; 

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	buffer = read_file(fd, buffer);
	line = get_current_line(buffer);
	buffer = trim_buffer(buffer, line);
	return line;
}
