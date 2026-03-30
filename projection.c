/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:54:25 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/30 20:48:17 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void set_limit(t_limit *limit)
{
	limit->left_limit = 2147483647;
	limit->right_limit = -2147483648;
	limit->upper_limit = 2147483647;
	limit->lower_limit = -2147483648;
	limit->width = 0;
	limit->height = 0;
}

static void set_scaling(t_scaling *scaling)
{
	scaling->zoom = 1;
	scaling->zoom_in = 1;
	scaling->offset_x = 0;
	scaling->offset_y = 0;
	scaling->exec_zoom = 0;
}

static void set_iso_coords_help(t_data	**data, t_scaling	scaling, int x, int y)
{
	float angle;

	angle = 0.523599;
	if(scaling.zoom_in)
	{
		data[y][x].iso_x = ((x*scaling.zoom-y*scaling.zoom) * cos(angle));
		data[y][x].iso_y = ((x*scaling.zoom+y*scaling.zoom) * sin(angle)
							-(data[y][x].height * (scaling.zoom / 2)));
	}
	else
	{
		data[y][x].iso_x = ((x/scaling.zoom-y/scaling.zoom) * cos(angle));
		data[y][x].iso_y = ((x/scaling.zoom+y/scaling.zoom) * sin(angle) 
							-(data[y][x].height /scaling.zoom));
	}
}

static void set_iso_coords(t_data	**data, t_input_size input_size, t_scaling scaling)
{
	int x;
	int y;
	float angle;

	y = 0;
	angle = 0.523599;
	while (y < input_size.height)
	{
		x = 0;
		while (x < input_size.width)
		{
			if(!scaling.exec_zoom)
			{
				data[y][x].iso_x = (x-y) * cos(angle);
				data[y][x].iso_y = (x+y) * sin(angle) -data[y][x].height;
			
			}
			else
				set_iso_coords_help(data, scaling, x, y);
			data[y][x].iso_x = data[y][x].iso_x + scaling.offset_x;
			data[y][x].iso_y = data[y][x].iso_y + scaling.offset_y;
			x++;
		}
		y++;
	}	
}

static void find_limits(t_data	**data, t_input_size input_size,t_limit *limits)
{
	int x;
	int y;

	y = 0;
	while (y < input_size.height)
	{
		x = 0;
		while (x < input_size.width)
		{
			if(data[y][x].iso_x > limits->right_limit)
				limits->right_limit = data[y][x].iso_x;
			if(data[y][x].iso_x < limits->left_limit)
				limits->left_limit = data[y][x].iso_x;
			if(data[y][x].iso_y < limits->upper_limit)
				limits->upper_limit = data[y][x].iso_y;
			if(data[y][x].iso_y > limits->lower_limit)
				limits->lower_limit = data[y][x].iso_y;
			x++;
		}
		y++;
	}
	limits->width = limits->right_limit - limits->left_limit;
	limits->height = limits->lower_limit - limits->upper_limit;
}

static void calc_zoom(t_scaling *scaling, t_limit limits)
{
	int i;
	int bigger;

	i = 1;
	if(limits.width == 0 || limits.height == 0)
		return ;
	if(limits.width > limits.height)
		bigger = limits.width;
	else
		bigger = limits.height;
	if(bigger > 600)
	{
		scaling->zoom_in = 0;
		while(bigger/i > 600)
			i++;
	}
	else
	{
		scaling->zoom_in = 1;
		while(bigger * i <= 600)
			i++;
	}
	scaling->zoom = i;
}

static void calc_offset(t_scaling *scaling, t_limit limits)
{
	int x; //x of center of map
	int y; //y of center of map

	x = limits.left_limit +(limits.right_limit -limits.left_limit) /2;
	y = limits.upper_limit +(limits.lower_limit - limits.upper_limit) /2;
	scaling->offset_x = 360 - x;
	scaling->offset_y = 360 - y;
	
}

static void calculations(t_data	**data, t_input_size input_size)
{
	t_scaling 	scaling;
	t_limit 	limit;
	
	set_limit(&limit);
	set_scaling(&scaling);
	set_iso_coords(data, input_size, scaling);
	find_limits(data, input_size,&limit);
	calc_zoom(&scaling, limit);
	scaling.exec_zoom = 1;
	set_iso_coords(data, input_size, scaling);
	set_limit(&limit);
	find_limits(data, input_size,&limit);
	calc_offset(&scaling, limit);
	set_iso_coords(data, input_size, scaling);
}

int	window_main(t_data	**data, t_input_size input_size)
{
	void		*mlx;
	void		*window;
	t_img_data	img;
	

	mlx = mlx_init();
	if(!mlx)
		return(perror("error with init func"), 0);
	window = mlx_new_window(mlx,720, 720, "FDF");
	if(!window)
		return(mlx_destroy_window(mlx, window), free(mlx), 0);
	img.img = mlx_new_image(mlx, 720, 720);
	if(!img.img)
		return(mlx_destroy_window(mlx, window), free(mlx), 0);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	calculations(data, input_size);
	draw_full_img(&img, input_size, data);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (1);
}
