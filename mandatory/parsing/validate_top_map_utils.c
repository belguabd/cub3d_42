/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_top_map_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:43:35 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/29 13:56:35 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (true);
	return (false);
}

void	check_newline(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (!map[y][0])
		{
			ft_malloc(0, FREE);
			ft_putendl_fd_color("Error\nInvalid map", 2, RED_E);
		}
		y++;
	}
}
