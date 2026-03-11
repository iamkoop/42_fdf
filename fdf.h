/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:08:07 by nildruon          #+#    #+#             */
/*   Updated: 2026/03/10 18:10:10 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include "libft_lib/libft.h"
# include <fcntl.h>

typedef struct s_data
{
	int		height;
	char	*colour;
}		t_data;

t_data	**extract_data(char *file);
int	main(int argc, char **argv);
#endif