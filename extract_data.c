/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:42:54 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/17 18:15:58 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static int find_line_len(char *curr_line)
{
	char **splitted;
	int len;

	len = 0;

	splitted = ft_split(curr_line, ' ');
	if(!splitted)
		return(0);
	while(splitted[len])
	{
		free(splitted[len]);
		len++;
	}
	free(splitted);
	return(len);
}

static int find_size(int *height, int *length, char *file)
{
	int fd;
	char *line;
	int len;
	int r;
	
	r = 0;
	len = 0;
	fd = open(file, O_RDONLY);
	if(fd < 0)
		return(perror("open"),0);
	errno = 0;
	while ((line = get_next_line(fd)))
	{
		if(((*height > 0) && (len != find_line_len(line))))
			return(perror("invalid map"), free(line), get_next_line(-42), 0);
		len = find_line_len(line);
		free(line);
		*height += 1;
	}
	if(errno != 0)
		return(perror("error with GNL"), 0);
	get_next_line(-42);
	*length = len;
	close(fd);
	return(1);
}
static void    print_data(t_data **data, int rows, int cols)
{
    int	i;
	int	j;

	if (!data)
		return;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			// Print the height value
			printf("%d", data[i][j].height);
			
			// Print a space after every element
			// Note: Your example shows a trailing space at the end of lines
			printf(" ");
			j++;
		}
		// Newline at the end of every row
		printf("\n");
		i++;
	}
}

t_data	**extract_data(char *file, int *s)
{
	t_data	**data;
	int		*size;

	size = malloc(sizeof(int) * 2);
	if(!size)
		return(NULL);
	size[0] = 0;
	size[1] = 0;
	if(!find_size(&size[0], &size[1], file))
		return(free(size),NULL);
	data = create_2d_data_arr(file, size[0], size[1]);
	if(!data)
		return(free(size),NULL);
	print_data(data,size[0],size[1]);
	*s = size[0];
	return(free(size), data);
}
