/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:05:08 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/08 12:34:43 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 720 || y < 0 || y >= 720)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	set_vars(t_plot_line_vars	*vars, t_line_data *l_data)
{
	vars->dx = abs(l_data->x2 - l_data->x1);
	if (l_data->x1 < l_data->x2)
		vars->sx = 1;
	else
		vars->sx = -1;
	vars->dy = -abs(l_data->y2 - l_data->y1);
	if (l_data->y1 < l_data->y2)
		vars->sy = 1;
	else
		vars->sy = -1;
	vars->error = vars->dx + vars->dy;
	vars->e2 = 0;
}

static void	bresenham_line_algo(t_img_data *img, t_line_data *l_data, int colr)
{
	t_plot_line_vars	vars;

	set_vars(&vars, l_data);
	while (1)
	{
		my_mlx_pixel_put(img, l_data->x1, l_data->y1, colr);
		if (l_data->x1 == l_data->x2 && l_data->y1 == l_data->y2)
			break ;
		vars.e2 = 2 * vars.error;
		if (vars.e2 >= vars.dy)
		{
			vars.error = vars.error + vars.dy;
			l_data->x1 = l_data->x1 + vars.sx;
		}
		if (vars.e2 <= vars.dx)
		{
			vars.error = vars.error + vars.dx;
			l_data->y1 = l_data->y1 + vars.sy;
		}
	}
}

void	draw_line(t_img_data *img, t_line_data *line_data, int color)
{
	bresenham_line_algo(img, line_data, color);
}
