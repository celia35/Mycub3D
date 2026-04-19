#include "cub3d.h"


// void	ft_parse_map(t_game *data)
// {
// 	int	img_hight;
// 	int	img_width;

// 	data->image = malloc(sizeof(t_img));
// 	if (!data->image)
// 		error_exit("allocation image failed", data);
// 	data->image->player = mlx_xpm_file_to_image(data->mlx, PLAYER, &img_width, &img_hight);
// 	if (!data->image->player)
// 		error_exit("failed to load PLAYER image", data);
// 	data->image->wall = mlx_xpm_file_to_image(data->mlx, WALL, &img_width, &img_hight);
// 	if (!data->image->wall)
// 		error_exit("failed to load WALL image", data);
// 	data->image->empty = mlx_xpm_file_to_image(data->mlx,
// 			EMPTY, &img_width, &img_hight);
// 	if (!data->image->empty)
// 		error_exit("failed to load EMPTY image", data);
// 	data->image->exit = mlx_xpm_file_to_image(data->mlx,
// 			EXIT, &img_width, &img_hight);
// 	if (!data->image->exit)
// 		error_exit("failed to load EXIT image", data);
// 	data->image->collect = mlx_xpm_file_to_image(data->mlx,
// 			COLLECT, &img_width, &img_hight);
// 	if (!data->image->collect)
// 		error_exit("failed to load COLLECT image", data);
// 	data->image->winner = mlx_xpm_file_to_image(data->mlx,
// 			WIN, &img_width, &img_hight);
// 	if (!data->image->winner)
// 		error_exit("failed to load WINNER image", data);
// }

// static void	free_window(t_game *data)
// {
// 	if (data->win)
// 	{
// 		mlx_clear_window(data->mlx, data->win);
// 		mlx_destroy_window(data->mlx, data->win);
// 	}
// }

void	ft_map_data(t_game *data, char *name)
{
	data->height = 0;
	data->width = 0;
	// data->escape = 0;
	// data->count = 0;
	// data->step = 0;
	data->playerX = 0;
	data->playerY = 0;
	data->player = 0;
	data->fn = name;
	// ft_parse_map(data);
}



// int main(int ac, char **av)
// {
// 	t_game game;

// 	// game.playerX = 22;
// 	// game.playerY = 12;

// 	game.dirX = -1;
// 	game.dirY = 0;

// 	game.planeX = 0;
// 	game.planeY = 0.66;

// 	if (ac == 2 && av)
// 	{
// 		game.mlx = mlx_init();
// 		//game.win = mlx_new_window(game.mlx, game.width * 40, game.height * 40, "cub3D");
// 		ft_map_data(&game, av[1]);
// 		ft_map_height(&game);
// 		ft_read_map(&game);
// 		// game.win = mlx_new_window(game.mlx, 640, 480, "cub3D");
// 		ft_printf("height %d/n", game.height);
// 		ft_printf("width %d/n", game.width);
// 		game.win = mlx_new_window(game.mlx, game.width * 40, game.height * 40, "cub3D");
// 		if (!game.win)
// 		{
// 			ft_printf("Error: Failed to create window");
// 		}
// 		ft_create_map(&game);
// 		mlx_hook(game.win, 17, 0, ft_exit, &game);
// 		mlx_key_hook(game.win, press_key, &game);
// 		mlx_loop(game.mlx);
// 		// free_window(&game);
// 		//free_display(game);
// 		// exit(EXIT_SUCCESS);
// 		// return (0);
// 	}
// }

// int main(int ac, char **av)
// {
// 	t_game game;

// 	ft_memset(&game, 0, sizeof(t_game));
// 	if (ac != 2 || !av[1])
// 	{
// 		ft_printf("Error\nUsage: ./cub3D <map.cub>\n");
// 		return (1);
// 	}
// 	ft_map_data(&game, av[1]);
// 	ft_map_height(&game);
// 	ft_parse_identifiers(&game);
// 	ft_read_map(&game);
// 	ft_validate_map(&game);
// 	// ft_printf("Spawn: (%d,%d) dir=%c\n",
//     // game.playerX, game.playerY, game.spawn_dir);
// 	// ft_printf("dirX=%.2f dirY=%.2f planeX=%.2f planeY=%.2f\n",
//     // game.dirX, game.dirY, game.planeX, game.planeY);
// 	// ft_init_player_dir(&game);
// 	ft_check_map(&game);
// 	// ft_printf("height %d\n", game.height);
// 	// ft_printf("width %d\n", game.width);
// 	// ft_printf("NO: %s\n", game.conf.tex_no);
// 	// ft_printf("SO: %s\n", game.conf.tex_so);
// 	// ft_printf("WE: %s\n", game.conf.tex_we);
// 	// ft_printf("EA: %s\n", game.conf.tex_ea);
// 	// ft_printf("Floor: %d,%d,%d\n", game.conf.floor[0], game.conf.floor[1], game.conf.floor[2]);
// 	// ft_printf("Ceil:  %d,%d,%d\n", game.conf.ceil[0], game.conf.ceil[1], game.conf.ceil[2]);
// 	// game.mlx = mlx_init();
// 	game.win = mlx_new_window(game.mlx, game.width * 40, game.height * 40, "cub3D");
// 	if (!game.win)
// 	{
// 		ft_printf("Error\nFailed to create window\n");
// 		return (1);
// 	}
// 	ft_parse_map(&game);
// 	ft_create_map(&game);
// 	// mlx_hook(game.win, 17, 0, ft_exit, &game);
// 	// mlx_hook(game.win, 17, 0, (int (*)(void))ft_exit, &game);
// 	mlx_hook(game.win, 17, 0, (int (*)(void))(void *)ft_exit, &game);
// 	mlx_key_hook(game.win, press_key, &game);
// 	mlx_loop(game.mlx);
// 	return (0);
// }

int main(int ac, char **av)
{
	t_game game;

	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2 || !av[1])
	{
		ft_printf("Error\nUsage: ./cub3D <map.cub>\n");
		return (1);
	}
	ft_map_data(&game, av[1]);
	ft_map_height(&game);
	ft_parse_identifiers(&game);
	ft_read_map(&game);
	ft_validate_map(&game);
	// ft_init_player_dir(&game);
	ft_check_map(&game);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.width * 40, game.height * 40, "cub3D");
	if (!game.win)
	{
		ft_printf("Error\nFailed to create window\n");
		return (1);
	}
	// ft_parse_map(&game);
	ft_create_map(&game);
	// mlx_hook(game.win, 17, 0, ft_exit, &game);
	// mlx_hook(game.win, 17, 0, (int (*)(void))ft_exit, &game);
	mlx_hook(game.win, 17, 0, (int (*)(void))(void *)ft_exit, &game);
	mlx_key_hook(game.win, press_key, &game);
	mlx_loop(game.mlx);
	return (0);
}