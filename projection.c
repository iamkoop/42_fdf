/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:54:25 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/25 19:06:42 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Formulas for ismometric projection
	x = (x-y) * cos(0.523599)
	y = (x+y) * sin(0.523599) -z */
static void set_iso_coords(t_data	**data, t_input_size input_size, int zoom)
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
			data[y][x].iso_x = (x*zoom-y*zoom) * cos(angle) 
								+ 360;
			data[y][x].iso_y = (x*zoom+y*zoom) * sin(angle) -data[y][x].height
								+ 180;
			x++;
		}
		y++;
	}	
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
	
	//TODO: find the outer most points of the iso coordinates and calculate based on that how much zoom should be done
	set_iso_coords(data, input_size, 20);
	draw_full_img(&img, input_size, data);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (1);
}
 