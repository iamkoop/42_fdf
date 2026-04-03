/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:38:11 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/03 19:04:47 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

int	close_win(int keypres, void *vars)
{
	if(keypres == XK_Escape)
		printf("ESCAPE!\n");
	else
		printf("X");
	free_the_data((void **)(((t_vars *)vars)->data), ((t_vars *)vars)->input_size.height -1);
	exit(0);
}

int	window_main(t_data	**data, t_input_size input_size)
{
	void		*mlx;
	void		*window;
	t_img_data	img;
	t_vars		vars = {0};

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
	vars.mlx = mlx;
	vars.window = window;
	vars.data = &data;
	vars.input_size = input_size;
	printf("%d", input_size.width);
	mlx_hook(window, KeyPress, KeyPressMask, close_win, (void *)&vars);
	mlx_hook(window, DestroyNotify, StructureNotifyMask, close_win, (void *)&vars);
	mlx_loop(mlx);
	return (1);
}

