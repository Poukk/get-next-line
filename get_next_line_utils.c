/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:54:22 by alexanfe          #+#    #+#             */
/*   Updated: 2024/10/22 19:54:30 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

t_buffer	init_clean_buffer(t_buffer *buffer, int fd)
{
	if (buffer->string)
	{
		clear_string(buffer->string);
		buffer->string = NULL;
	}
	if (fd < 0)
	{
		buffer->total_read = -1;
		return (*buffer);
	}
	buffer->position = 0;
	while (buffer->position < BUFFER_SIZE)
		buffer->buffer[buffer->position++] = '\0';
	buffer->position = 0;
	buffer->string = NULL;
	buffer->length = 0;
	buffer->fd = fd;
	buffer->total_read = read(fd, buffer->buffer, BUFFER_SIZE);
	return (*buffer);
}

void	clear_string(t_string *str)
{
	t_string	*temp;

	while (str)
	{
		temp = str->next;
		free(str);
		str = temp;
	}
	temp = NULL;
}

void	build_string(t_string **string_head, char character)
{
	t_string	*new_character;
	t_string	*current;

	new_character = (t_string *)malloc(sizeof(t_string));
	if (!new_character)
	{
		clear_string(*string_head);
		*string_head = NULL;
		return ;
	}
	new_character->character = character;
	new_character->next = NULL;
	if (!*string_head)
	{
		*string_head = new_character;
		return ;
	}
	current = *string_head;
	while (current->next)
		current = current->next;
	current->next = new_character;
}

char	*alloc_line(t_buffer *buffer)
{
	t_string	*current;
	char		*line;
	int			i;

	line = (char *)malloc(buffer->length + 1);
	if (!line)
		return (NULL);
	i = 0;
	current = NULL;
	while (buffer->string)
	{
		current = buffer->string->next;
		line[i] = buffer->string->character;
		free(buffer->string);
		buffer->string = current;
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_current_line(t_buffer *buffer)
{
	buffer->length = 0;
	while (buffer->total_read > 0)
	{
		build_string(&buffer->string, buffer->buffer[buffer->position]);
		if (buffer->buffer[buffer->position] == '\n')
			break ;
		buffer->position++;
		buffer->length++;
		if (buffer->position >= buffer->total_read)
		{
			buffer->position = 0;
			buffer->total_read = read(buffer->fd, buffer->buffer, BUFFER_SIZE);
			if (buffer->total_read < 0)
			{
				clear_string(buffer->string);
				buffer->string = NULL;
				return (NULL);
			}
		}
	}
	buffer->position++;
	buffer->length++;
	return (alloc_line(buffer));
}
