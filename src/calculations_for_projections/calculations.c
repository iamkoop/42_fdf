/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:22:05 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/03 07:23:55 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_iso_xy_help(t_data	**dat, t_scaling	scaling, int x, int y)
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

void	set_iso_coords(t_data	**dat, t_input_size input_s, t_scaling scl)
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

void	find_limits(t_data	**data, t_input_size input_size, t_limit *lim)
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

void	calc_zoom(t_scaling *scaling, t_limit limits)
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

void	calc_offset(t_scaling *scaling, t_limit limits)
{
	int	x;
	int	y;

	x = limits.left_limit + (limits.right_limit - limits.left_limit) / 2;
	y = limits.upper_limit + (limits.lower_limit - limits.upper_limit) / 2;
	scaling->offset_x = 360 - x;
	scaling->offset_y = 360 - y;
}
