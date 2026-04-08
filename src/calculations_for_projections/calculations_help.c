/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:28:45 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/08 12:32:08 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_limit(t_limit *limit)
{
	limit->left_limit = 2147483647;
	limit->right_limit = -2147483648;
	limit->upper_limit = 2147483647;
	limit->lower_limit = -2147483648;
	limit->width = 0;
	limit->height = 0;
}

void	set_scaling(t_scaling *scaling)
{
	scaling->zoom = 1;
	scaling->zoom_in = 1;
	scaling->offset_x = 0;
	scaling->offset_y = 0;
	scaling->exec_zoom = 0;
}
