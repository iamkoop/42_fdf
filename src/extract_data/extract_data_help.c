/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:27:18 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/08 12:37:32 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (!(s[0] == '-' || ft_isdigit(s[0])))
			return (0);
		if (i > 0 &&!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	colour_is_valid(char *s)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		len--;
	if (len > 8 || len <= 2)
		return (0);
	if (!(s[0] == '0' && (s[1] == 'x' || s[1] == 'X')))
		return (0);
	i = 2;
	while (s[i] && s[i] != '\n')
	{
		if ((s[i] >= 'A' && s[i] <= 'F') || (s[i] >= 'a' && s[i] <= 'f'))
			i++;
		else if (ft_isdigit(s[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

static t_data	fill_with_data(char *s, int	*valid)
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
	if (!is_num(splitted[0]))
	{
		*valid = 0;
		return (free_the_split(splitted), data);
	}
	data.height = ft_atoi(splitted[0]);
	if (len == 2)
		data.colour = 16777215;
	else
		data.colour = 16777215;
	if ((len == 2 && (splitted[1] && !colour_is_valid(splitted[1]))))
		*valid = 0;
	free_the_split(splitted);
	return (data);
}

static t_data	*data_from_line(char	*line, int width)
{
	char	**data;
	t_data	*data_from_l;
	int		i;
	int		valid;

	if (!line)
		return (NULL);
	data = ft_split(line, ' ');
	if (!data)
		return (NULL);
	data_from_l = malloc(sizeof(t_data) * width);
	if (!data_from_l)
		return (free_the_split(data), NULL);
	i = 0;
	valid = 1;
	while (i < width && data[i])
	{
		data_from_l[i] = fill_with_data(data[i], &valid);
		i++;
	}
	free_the_split(data);
	errno = EINVAL;
	if (valid == 0)
		return (perror("In the given file there is a: "), NULL);
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
			return (free_the_data(data, size), close(fd), NULL);
		data[size] = data_from_line(gnl, width);
		if (!data[size])
			return (free_the_data(data, size),
				free(gnl), close(fd), get_next_line(-42), NULL);
		free(gnl);
		size++;
	}
	return (get_next_line(-42), close(fd), data);
}
