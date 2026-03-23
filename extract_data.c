/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:42:54 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/20 12:48:01 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static int	find_line_len(char *curr_line)
{
	char	**splitted;
	int		len;

	len = 0;
	splitted = ft_split(curr_line, ' ');
	if (!splitted)
		return (0);
	while (splitted[len] && splitted[len][0] != '\n')
	{
		free(splitted[len]);
		len++;
	}
	free(splitted);
	return (len);
}

static int	find_size(int *height, int *length, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 0);
	errno = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (((*height > 0) && (*length != find_line_len(line))))
			return (perror("invalid map"), free(line), get_next_line(-42), 0);
		*length = find_line_len(line);
		free(line);
		line = get_next_line(fd);
		*height += 1;
	}
	if (errno != 0)
		return (perror("error with GNL"), 0);
	get_next_line(-42);
	close(fd);
	return (1);
}

t_data	**extract_data(char *file, int *s)
{
	t_data	**data;
	int		*size;

	size = malloc(sizeof(int) * 2);
	if (!size)
		return (NULL);
	size[0] = 0;
	size[1] = 0;
	if (!find_size(&size[0], &size[1], file))
		return (free(size), NULL);
	data = create_2d_data_arr(file, size[0], size[1]);
	if (!data)
		return (free(size), NULL);
	*s = size[0];
	return (free(size), data);
}
