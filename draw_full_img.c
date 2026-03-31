/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_full_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:01:42 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/31 21:24:41 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_line_data	*set_coords(t_data	p1, t_data	p2)
{
	t_line_data	*l_data;

	l_data = malloc(sizeof(*l_data));
	if (!l_data)
		return (NULL);
	l_data->x1 = p1.iso_x;
	l_data->y1 = p1.iso_y;
	l_data->x2 = p2.iso_x;
	l_data->y2 = p2.iso_y;
	return (l_data);
}

static void	draw_vert(t_img_data *img, t_input_size input_size, t_data	**data)
{
	t_line_data	*l_data;
	int			x;
	int			y;

	x = 0;
	while (x < input_size.width)
	{
		y = 0;
		while (y < input_size.height -1)
		{
			l_data = set_coords(data[y][x], data[y +1][x]);
			if (!l_data)
				return ;
			draw_line(img, l_data, data[y][x].colour);
			free(l_data);
			y++;
		}
		x++;
	}
}

static void	draw_horiz(t_img_data *img, t_input_size input_size, t_data	**data)
{
	t_line_data	*l_data;
	int			x;
	int			y;

	y = 0;
	while (y < input_size.height)
	{
		x = 0;
		while (x < input_size.width -1)
		{
			l_data = set_coords(data[y][x], data[y][x +1]);
			if (!l_data)
				return ;
			draw_line(img, l_data, data[y][x].colour);
			free(l_data);
			x++;
		}
		y++;
	}
}

void	draw_full_img(t_img_data *img, t_input_size input_size, t_data	**data)
{
	t_line_data	*l_data;

	if (input_size.height == 1 && input_size.width == 1)
	{
		l_data = set_coords(data[0][0], data[0][0]);
		if (!l_data)
			return ;
		draw_line(img, l_data, data[0][0].colour);
		free(l_data);
		return ;
	}
	draw_horiz(img, input_size, data);
	draw_vert(img, input_size, data);
}
