/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:27:18 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/03 08:06:00 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static t_data	fill_with_data(char *s)
{
	t_data	data;
	char	**splitted;
	int		len;

	len = 0;
	data.height = 16777215;
	splitted = ft_split(s, ',');
	if (!splitted)
		return (data);
	while (splitted[len])
		len++;
	data.height = ft_atoi(splitted[0]);
	if (len == 2)
		data.colour = 16777215;
	else
		data.colour = 16777215;
	free_the_data((void **)splitted, len -1);
	return (data);
}

static t_data	*data_from_line(char	*line, int width)
{
	char	**data;
	t_data	*data_from_l;
	int		i;

	if (!line)
		return (NULL);
	data = ft_split(line, ' ');
	if (!data)
		return (NULL);
	data_from_l = malloc(sizeof(t_data) * width);
	if (!data_from_l)
		return (free_the_data((void **)data, -1), NULL);
	i = 0;
	while (i < width && data[i])
	{
		data_from_l[i] = fill_with_data(data[i]);
		i++;
	}
	free_the_data((void **)data, -1);
	return (data_from_l);
}

t_data	**create_2d_data_arr(char *file, int height, int width)
{
	t_data	**data;
	char	*gnl;
	int		size;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("open"), NULL);
	data = ft_calloc(height, sizeof(t_data *));
	if (!data)
		return (close(fd), NULL);
	size = 0;
	while (size < height)
	{
		gnl = get_next_line(fd);
		if (!gnl)
			return (free_the_data((void **)data, size), close(fd), NULL);
		data[size] = data_from_line(gnl, width);
		if (!data[size])
			return (free_the_data((void **)data, size),
				free(gnl), close(fd), get_next_line(-42), NULL);
		free(gnl);
		size++;
	}
	return (get_next_line(-42), close(fd), data);
}
