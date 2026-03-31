/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:08:07 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/31 21:16:57 by nildruon         ###   ########.fr       */
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
# include <math.h>

typedef struct s_data
{
	int	height;
	int	colour;
	int	iso_x;
	int	iso_y;
}		t_data;

typedef struct s_input_size
{
	int	height;
	int	width;
}		t_input_size;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct s_line_data
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}		t_line_data;

typedef struct s_plot_line_vars
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;
	int	e2;
}		t_plot_line_vars;

typedef struct s_scaling
{
	int	offset_x;
	int	offset_y;
	int	zoom;
	int	zoom_in;
	int	height_scaling;
	int	exec_zoom;
}		t_scaling;

typedef struct s_limit
{
	int	upper_limit;
	int	lower_limit;
	int	left_limit;
	int	right_limit;
	int	width;
	int	height;
}		t_limit;

void	draw_full_img(t_img_data *img, t_input_size input_size, t_data	**data);
void	draw_line(t_img_data *img, t_line_data *line_data, int color);
int		window_main(t_data	**data, t_input_size input_size);
void	free_the_data(void **data, int until_where);
t_data	**create_2d_data_arr(char *file, int height, int width);
t_data	**extract_data(char *file, int *s, t_input_size *input_size);
int		main(int argc, char **argv);
#endif