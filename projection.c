/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:54:25 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/31 22:27:36 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_limit(t_limit *limit)
{
	limit->left_limit = 2147483647;
	limit->right_limit = -2147483648;
	limit->upper_limit = 2147483647;
	limit->lower_limit = -2147483648;
	limit->width = 0;
	limit->height = 0;
}

static void	set_scaling(t_scaling *scaling)
{
	scaling->zoom = 1;
	scaling->zoom_in = 1;
	scaling->offset_x = 0;
	scaling->offset_y = 0;
	scaling->exec_zoom = 0;
}

static void	set_iso_xy_help(t_data	**dat, t_scaling	scaling, int x, int y)
{
	float	angle;

	angle = 0.523599;
	if (scaling.zoom_in)
	{
		dat[y][x].iso_x = ((x * scaling.zoom - y * scaling.zoom) * cos(angle));
		dat[y][x].iso_y = ((x * scaling.zoom + y * scaling.zoom) * sin(angle)
				- (dat[y][x].height * (scaling.zoom / 2)));
	}
	else
	{
		dat[y][x].iso_x = ((x / scaling.zoom - y / scaling.zoom) * cos(angle));
		dat[y][x].iso_y = ((x / scaling.zoom + y / scaling.zoom) * sin(angle)
				- (dat[y][x].height / scaling.zoom));
	}
}

static void	set_iso_coords(t_data	**dat, t_input_size input_s, t_scaling scl)
{
	int		x;
	int		y;
	float	angl;

	y = 0;
	angl = 0.523599;
	while (y < input_s.height)
	{
		x = 0;
		while (x < input_s.width)
		{
			if (!scl.exec_zoom)
			{
				dat[y][x].iso_x = (x - y) * cos(angl) * 100;
				dat[y][x].iso_y = (x + y) * sin(angl) - dat[y][x].height * 100;
			}
			else
				set_iso_xy_help(dat, scl, x, y);
			dat[y][x].iso_x = dat[y][x].iso_x + scl.offset_x;
			dat[y][x].iso_y = dat[y][x].iso_y + scl.offset_y;
			x++;
		}
		y++;
	}
}

static void	find_limits(t_data	**data, t_input_size input_size, t_limit *lim)
{
	int	x;
	int	y;

	y = 0;
	while (y < input_size.height)
	{
		x = 0;
		while (x < input_size.width)
		{
			if (data[y][x].iso_x > lim->right_limit)
				lim->right_limit = data[y][x].iso_x;
			if (data[y][x].iso_x < lim->left_limit)
				lim->left_limit = data[y][x].iso_x;
			if (data[y][x].iso_y < lim->upper_limit)
				lim->upper_limit = data[y][x].iso_y;
			if (data[y][x].iso_y > lim->lower_limit)
				lim->lower_limit = data[y][x].iso_y;
			x++;
		}
		y++;
	}
	lim->width = lim->right_limit - lim->left_limit;
	lim->height = lim->lower_limit - lim->upper_limit;
}

static void	calc_zoom(t_scaling *scaling, t_limit limits)
{
	int	i;
	int	bigger;

	i = 1;
	if (limits.width == 0 && limits.height == 0)
		return ;
	bigger = limits.width;
	if (limits.height > bigger)
		bigger = limits.height;
	if (bigger <= 0)
		i = 30;
	else if (bigger > 60000)
	{
		scaling->zoom_in = 0;
		while (bigger / i > 60000)
			i++;
	}
	else
	{
		scaling->zoom_in = 1;
		while (bigger * i <= 60000 && i < 60)
			i++;
	}
	scaling->zoom = i;
}

static void	calc_offset(t_scaling *scaling, t_limit limits)
{
	int	x;
	int	y;

	x = limits.left_limit + (limits.right_limit - limits.left_limit) / 2;
	y = limits.upper_limit + (limits.lower_limit - limits.upper_limit) / 2;
	scaling->offset_x = 360 - x;
	scaling->offset_y = 360 - y;
}

static void	calculations(t_data	**data, t_input_size input_size)
{
	t_scaling	scaling;
	t_limit		limit;

	set_limit(&limit);
	set_scaling(&scaling);
	set_iso_coords(data, input_size, scaling);
	find_limits(data, input_size, &limit);
	calc_zoom(&scaling, limit);
	scaling.exec_zoom = 1;
	set_iso_coords(data, input_size, scaling);
	set_limit(&limit);
	find_limits(data, input_size, &limit);
	calc_offset(&scaling, limit);
	set_iso_coords(data, input_size, scaling);
}

/*int	close_win(void *mlx, void *window)
{
	exit(0);
	return (0);
}*/

int	window_main(t_data	**data, t_input_size input_size)
{
	void		*mlx;
	void		*window;
	t_img_data	img;

	mlx = mlx_init();
	if (!mlx)
		return (perror("error with init func"), 0);
	window = mlx_new_window(mlx, 720, 720, "FDF");
	if (!window)
		return (mlx_destroy_window(mlx, window), free(mlx), 0);
	img.img = mlx_new_image(mlx, 720, 720);
	if (!img.img)
		return (mlx_destroy_window(mlx, window), free(mlx), 0);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	calculations(data, input_size);
	draw_full_img(&img, input_size, data);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	//mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(mlx);
	//mlx_hook(window, 17, 0, close_win(mlx, window), mlx);
	return (1);
}
