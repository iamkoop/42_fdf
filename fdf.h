/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:08:07 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/23 17:27:13 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include "libft_lib/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_data
{
	int	height;
	int	colour;
}		t_data;

typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct s_line_data
{
	int	x_start;
	int	y_start;
	int x_end;
	int y_end;
}		t_line_data;

void draw_line(t_img_data *img, t_line_data *line_data, int color);
int		window_main(t_data	**data);
void	free_the_data(void **data, int until_where);
t_data	**create_2d_data_arr(char *file, int height, int width);
t_data	**extract_data(char *file, int *s);
int		main(int argc, char **argv);
#endif