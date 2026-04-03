/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:42:54 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/03 07:17:10 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

static int	find_size(int *height, int *width, char *file)
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
		if (((*height > 0) && (*width != find_line_len(line))))
			return (perror("invalid map"), free(line), get_next_line(-42), 0);
		*width = find_line_len(line);
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

t_data	**extract_data(char *file, int *s, t_input_size *input_size)
{
	t_data	**data;

	if (!find_size(&input_size->height, &input_size->width, file))
		return (NULL);
	data = create_2d_data_arr(file, input_size->height, input_size->width);
	if (!data)
		return (NULL);
	*s = input_size->height;
	return (data);
}
