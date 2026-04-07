/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:43:46 by nildruon          #+#    #+#             */
/*   Updated: 2026/04/07 21:20:04 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_the_data(t_data **data, int until_where)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (i <= until_where)
		{
			if (data[i])
				free(data[i]);
			i++;
		}
	free(data);
}

void	free_the_split(char **data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}

static int file_valid(char *s)
{
	int len;

	len = ft_strlen(s);
	if(len < 5)
		return(0);
	s += len-4;
	if(ft_strncmp(s,".fdf", 4) != 0)
		return(0);
	return(1);
}

int	main(int argc, char **argv)
{
	t_data				**data;
	int					size;
	int					win;
	t_input_size		input_size;
	static t_vars		vars;
	
	errno = 22;
	if (argc != 2)
		return (perror("Incorrect amount of args, thats why: "), 0);
	input_size.height = 0;
	input_size.width = 0;
	if(!file_valid(argv[1]))
		return(perror("invalid file: "),0);
	data = extract_data(argv[1], &size, &input_size);
	if (!data)
		return (0);
	win = window_main(data, input_size, &vars);
	if (!win)
		return (0);
	free_the_data(data, size -1);
	return (1);
}
