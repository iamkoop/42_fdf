/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:38:11 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/03 07:45:35 by nildruon         ###   ########.fr       */
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