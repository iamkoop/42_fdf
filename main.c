/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:43:46 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/10 18:10:48 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_data	**data;
	
	if(argc != 2)
		return (ft_putstr_fd("Usage : ./fdf <filename>",2), 0);	
	data = extract_data(argv[1]);
	if(!data)
		return(0);
}
