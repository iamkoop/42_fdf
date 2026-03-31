/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:43:46 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/31 21:15:07 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_the_data(void **data, int until_where)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	if (until_where == -1)
	{
		while (data[i])
		{
			free(data[i]);
			i++;
		}
		free(data);
		return ;
	}
	else
	{
		while (i <= until_where)
		{
			if (data[i])
				free(data[i]);
			i++;
		}
	}
	free(data);
}

int	main(int argc, char **argv)
{
	t_data			**data;
	int				size;
	int				win;
	t_input_size	input_size;

	if (argc != 2)
		return (ft_putstr_fd("Usage : ./fdf <filename>", 2), 0);
	input_size.height = 0;
	input_size.width = 0;
	data = extract_data(argv[1], &size, &input_size);
	if (!data)
		return (0);
	win = window_main(data, input_size);
	if (!win)
		return (0);
	free_the_data((void **)data, size -1);
	return (1);
}
