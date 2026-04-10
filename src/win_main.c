/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:38:11 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/10 20:39:10 by nildruon         ###   ########.fr       */
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

static int	close_win(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (vars->data)
		free_the_data(vars->data, vars->input_size.height - 1);
	if (vars->img && vars->img->img && vars->mlx)
		mlx_destroy_image(vars->mlx, vars->img->img);
	if (vars->window && vars->mlx)
		mlx_destroy_window(vars->mlx, vars->window);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	if (vars->mlx)
		free(vars->mlx);	
	exit(0);
}

static int	key_hook(int keycode, void *param)
{
	if (keycode == XK_Escape)
	{
		close_win(param);
	}
	return (0);
}

static int	hookers(t_vars	*vars)
{
	mlx_hook(vars->window, KeyPress, KeyPressMask, key_hook, (void *)vars);
	mlx_hook(vars->window, DestroyNotify, StructureNotifyMask,
		close_win, (void *)vars);
	mlx_loop(vars->mlx);
	return (1);
}

int	window_main(t_data	**data, t_input_size input_size, t_vars *vars)
{
	t_img_data	img;

	vars->data = data;
	vars->input_size = input_size;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (close_win(vars), perror("error with init func"),0);
	vars->window = mlx_new_window(vars->mlx, 720, 720, "FDF");
	if (!vars->window)
		return (close_win(vars));
	img.img = mlx_new_image(vars->mlx, 720, 720);
	if (!img.img)
		return (close_win(vars));
	vars->img = &img;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	if (!img.addr)
		return (close_win(vars));
	calculations(data, input_size);
	draw_full_img(&img, input_size, data);
	mlx_put_image_to_window(vars->mlx, vars->window, img.img, 0, 0);
	return (hookers(vars));
}
