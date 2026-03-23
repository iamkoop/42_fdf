/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:43:46 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/22 18:57:03 by nildruon         ###   ########.fr       */
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
	t_data	**data;
	int		size;
	int		win;

	if (argc != 2)
		return (ft_putstr_fd("Usage : ./fdf <filename>", 2), 0);
	data = extract_data(argv[1], &size);
	if (!data)
		return (0);
	free_the_data((void **)data, size -1);
	win = window_main(data);
	if (!win)
		return (0);
	return (1);
}
