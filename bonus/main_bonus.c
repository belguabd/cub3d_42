/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/29 15:02:52 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

void	ft_hook(void *param)
{
	t_player	*player;
	t_data		*data;
	t_map		map;

	data = (t_data *)param;
	map = data->map;
	player = &data->player;
	doors(data, map);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		player->walk_direction = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		player->walk_direction = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		player->walk_direction = -2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		player->walk_direction = 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		player->rotation_angle = degtorad(1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		player->rotation_angle = degtorad(-1);
	if (player->rotation_angle != 0 || player->walk_direction != 0)
		update_player(data);
}

int	render_map(t_data *data)
{
	t_map	map;
	size_t	i;
	size_t	j;

	i = 0;
	map = data->map;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (map.layout[i][j] == 'N' || map.layout[i][j] == 'S'
				|| map.layout[i][j] == 'W' || map.layout[i][j] == 'E')
			{
				set_player_direction(data, (t_index){i, j});
				return (update_player(data), 1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	parsing_part(t_data *data)
{
	load_map_data(data);
	validate_top_map(data);
	set_map(data);
	validate_all_dirs(data);
	validate_colors(data);
	parse_map(data);
	init_clrs_dirs(data);
	parsing_doors(data);
}

void	check_extension(char const *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
		ft_putendl_fd_color("Error\nInvalid file extension", 2, RED_E);
}

int	main(int ac, char const **av)
{
	t_data	data;

	if (ac != 2)
		ft_putendl_fd_color("Error\nInvalid number of arguments", 2, RED_E);
	check_extension(av[1]);
	data.map_path = ft_strdup(av[1]);
	parsing_part(&data);
	init_sprites(&data);
	data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D_bonus", false);
	if (data.mlx == NULL)
		return (free_and_exit(&data, NUM_IMAGES), EXIT_FAILURE);
	init_vars(&data);
	image_to_window(&data, data.background_img, 0, 0);
	image_to_window(&data, data.window_img, 0, 0);
	image_to_window(&data, data.minimap.img, 0, 0);
	image_to_window(&data, data.default_img, 300, 300);
	painting_background(data.background_img, data.ceiling, data.floor);
	render_map(&data);
	mlx_loop_hook(data.mlx, animation_sprite, &data);
	mlx_cursor_hook(data.mlx, move_mouse, &data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_DISABLED);
	mlx_loop(data.mlx);
	terminate_mlx(&data);
}
