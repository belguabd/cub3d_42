/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clrs_dirs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:23:02 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/29 14:16:02 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	count_lines(t_data *data)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(data->map_path, O_RDONLY, 0666);
	if (fd < 0)
	{
		ft_malloc(FREE, FREE);
		ft_putendl_fd_color("Error\nOpen failure", 2, RED_E);
	}
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	find_dirs(char **data)
{
	char	*line;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (data[i])
	{
		line = ft_strtrim(data[i], " ");
		if (check_dirs(line, "NO")
			|| check_dirs(line, "SO")
			|| check_dirs(line, "WE")
			|| check_dirs(line, "EA"))
			count++;
		i++;
	}
	if (count != 4)
		return (-1);
	return (0);
}

int	find_longest_line_index(t_data *data)
{
	int	current_length;
	int	lg_line;
	int	to_find;
	int	i;

	i = 0;
	to_find = 0;
	lg_line = ft_strlen(data->map.layout[i]);
	while (data->map.layout[i])
	{
		current_length = ft_strlen(data->map.layout[i]);
		if (lg_line < current_length)
		{
			to_find = i;
			lg_line = current_length;
		}
		i++;
	}
	return (to_find);
}

void	set_directions(t_data *data)
{
	char	**out;
	int		i;

	i = 0;
	while (data->dirs[i])
	{
		out = ft_split(data->dirs[i], ' ');
		if (!ft_strcmp(out[0], "NO"))
			data->no = out[1];
		else if (!ft_strcmp(out[0], "SO"))
			data->so = out[1];
		else if (!ft_strcmp(out[0], "WE"))
			data->we = out[1];
		else
			data->ea = out[1];
		i++;
	}
}

void	init_clrs_dirs(t_data *data)
{
	char	*clr;
	char	**clrs;
	int		i;

	i = -1;
	set_directions(data);
	while (data->clrs[++i])
	{
		clr = ft_strtrim(data->clrs[i], " ");
		if (clr[ft_strlen(clr) - 1] == ',')
			(ft_malloc(FREE, FREE), print_error("Error\nInvalid color"));
		clrs = ft_split(clr + 1, ',');
		if (clr[0] == 'F')
		{
			data->floor.red = ft_atoi(clrs[0]);
			data->floor.green = ft_atoi(clrs[1]);
			data->floor.blue = ft_atoi(clrs[2]);
		}
		else if (clr[0] == 'C')
		{
			data->ceiling.red = ft_atoi(clrs[0]);
			data->ceiling.green = ft_atoi(clrs[1]);
			data->ceiling.blue = ft_atoi(clrs[2]);
		}
	}
}
