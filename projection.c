/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:54:25 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/23 17:26:52 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	draw_line(&img, &line_data, 0x00FF0000);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);

	return (1);
}
 