/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:42:54 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/10 17:35:58 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	cnt_words2(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] != c && ((s[i + 1] == c) || s[i + 1] == '\0'))
			cnt++;
		i++;
	}
	return (cnt);
}

int	find_size(int *height, int *width, char *file, int cmp)
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
		cmp = cnt_words2(line, ' ');
		if (((*height > 0) && (*width != cmp)))
			return (perror("invalid map"), free(line),
				get_next_line(-42), close(fd), 0);
		*width = cmp;
		free(line);
		line = get_next_line(fd);
		*height += 1;
	}
	if (errno != 0)
		return (get_next_line(-42), close(fd), perror("error with GNL"), 0);
	get_next_line(-42);
	close(fd);
	return (1);
}

t_data	**extract_data(char *file, int *s, t_input_size *input_size)
{
	t_data	**data;

	if (!find_size(&input_size->height, &input_size->width, file, 0))
		return (NULL);
	data = create_2d_data_arr(file, input_size->height, input_size->width);
	if (!data)
		return (NULL);
	*s = input_size->height;
	return (data);
}
