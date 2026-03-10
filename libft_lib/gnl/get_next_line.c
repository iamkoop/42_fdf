/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:30:43 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/10 14:16:19 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char	*buffer, char	**remainder)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (free(buffer), *remainder = NULL, NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	extract_line_help(buffer, line, remainder, i);
	if (buffer[i] == '\n' && !*remainder)
		return (free(line), free(buffer), NULL);
	free(buffer);
	return (line);
}

static char	*ft_strjoin(char *buffer, char **remainder)
{
	char	*concant;
	int		buffer_l;
	int		remainder_len;
	int		i;

	if (!*remainder)
		return (concant = ft_strdup(buffer));
	buffer_l = ft_strlen(buffer);
	remainder_len = ft_strlen(*remainder);
	concant = malloc(buffer_l + remainder_len + 1);
	if (!concant)
		return (free(*remainder),*remainder = NULL, NULL);
	i = 0;
	while ((*remainder)[i])
	{
		concant[i] = (*remainder)[i];
		i++;
	}
	buffer_l = 0;
	while (buffer[buffer_l])
		concant[i++] = buffer[buffer_l++];
	concant[i] = '\0';
	free(*remainder);
	*remainder = NULL;
	return (concant);
}

static char	*free_and_return(char **remainder)
{
	if (!*remainder || !**remainder)
	{
		free(*remainder);
		*remainder = NULL;
		return (NULL);
	}
	return (*remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*line;
	int			r;

	r = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (!found_new_line(remainder) && r > 0)
	{
		line = read_buffer(&r, fd);
		if (r <= 0)
			break ;
		if (!line)
			break ;
		remainder = ft_strjoin(line, &remainder);
		free(line);
		if (!remainder)
			break ;
	}
	if (!free_and_return(&remainder))
		return (NULL);
	return (extract_line(remainder, &remainder));
}
