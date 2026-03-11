/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:42:54 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/11 12:47:16 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int find_line_len(char *curr_line)
{
	
}

static int find_size(int *height, int *length, char *file)
{
	int fd;
	char *l;
	int i;
	int r;
	
	r = 1;
	fd = open(file, O_RDONLY);
	if(!fd)
		return(0);
	i = 0;
	while (1)
	{
		l = get_next_line(fd);
		if(!l)
			break;
		if((i != 0) && (find_line_len(l) != l))
			r = 0;
		*height++;
		i++;
	}
	close(fd);
	return(r);
}

t_data	**extract_data(char *file)
{
	t_data	**data;
	int		*size;

	size = malloc(sizeof(int) * 2);
	size[0] = 0;
	size[1] = 0;
	if(!find_size(size[0], size[1], file))
		return(NULL);
}