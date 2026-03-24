/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:54:25 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/24 19:44:25 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void set_iso_coords(t_data	**data)
{
	/*int i;
	int j;

	i = 0;
	j = 0;

	while (data[i])
	{
		while (data[i][j])
		{
			j++;
		}
		
		i++;
	}
	x = (x-y) * cos(0.523599)
	y = (x+y) * sin(0.523599) -z
	*/
}

int	window_main(t_data	**data)
{
	void	*mlx;
	void	*window;
	t_img_data	img;
	t_line_data line_data;

	data = NULL;
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
	set_iso_coords(&data);
	line_data.x1 = 600;
	line_data.x2 = 10;
	line_data.y1 = 10;
	line_data.y2 = 600;
	draw_line(&img, &line_data, 0x00FF0000);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (1);
}
 