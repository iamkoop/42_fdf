/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:08:07 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/09 15:41:04 by nildruon         ###   ########.fr       */
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
# include <X11/X.h>
# include <X11/keysym.h>

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

typedef struct s_vars
{
	void			*mlx;
	void			*window;
	t_data			***data;
	t_input_size	input_size;
	t_img_data		*img;
}		t_vars;

//calculations
void	set_iso_xy_help(t_data	**dat, t_scaling	scaling, int x, int y);
void	set_iso_coords(t_data	**dat, t_input_size input_s, t_scaling scl);
void	find_limits(t_data	**data, t_input_size input_size, t_limit *lim);
void	calc_zoom(t_scaling *scaling, t_limit limits);
void	calc_offset(t_scaling *scaling, t_limit limits);
void	set_limit(t_limit *limit);
void	set_scaling(t_scaling *scaling);

void	draw_full_img(t_img_data *img, t_input_size input_size, t_data	**data);
void	draw_line(t_img_data *img, t_line_data *line_data, int color);
int		window_main(t_data	**data, t_input_size input_size, t_vars *vars);
void	free_the_data(t_data **data, int until_where);
void	free_the_split(char **data);
t_data	**create_2d_data_arr(char *file, int height, int width);
t_data	**extract_data(char *file, int *s, t_input_size *input_size);
int		main(int argc, char **argv);
#endif