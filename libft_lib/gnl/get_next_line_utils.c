/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:30:43 by nildruon          #+#    #+#             */
/*   Updated: 2025/12/06 17:04:44 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	if (!s)
		return (0);
	while (s[size])
	{
		size++;
	}
	return (size);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*cpy;
	size_t	i;

	len = ft_strlen(s);
	cpy = (char *)malloc(len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		cpy[i] = s[i];
		i++;
	}
	return (cpy);
}

char	*read_buffer(int *read_r, int fd)
{
	char	*buffer;
	char	*result;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		*read_r = -1;
		return (NULL);
	}
	*read_r = read(fd, buffer, BUFFER_SIZE);
	if (*read_r <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[*read_r] = '\0';
	result = ft_strdup(buffer);
	free(buffer);
	return (result);
}

int	found_new_line(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	extract_line_help(char *buffer, char *line, char **remainder, int i)
{
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
		*remainder = ft_strdup(buffer + i + 1);
	}
	else
	{
		line[i] = '\0';
		*remainder = NULL;
	}
}
