#include "cub3d.h"


static void	free_window(t_game *data)
{
	if (data->win)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
	}
}

int main()
{
	t_game game;

	game.planeX = 22;
	game.playerY = 12;
	game.dirX = -1;
	game.dirY = 0;
	game.planeX = 0;
	game.planeY = 0.66;

	//if (ac == 2 && av)
	//{
		game.mlx = mlx_init();
		//game.win = mlx_new_window(game.mlx, game.width * 40, game.height * 40, "cub3D");
		game.win = mlx_new_window(game.mlx, 640, 480, "cub3D");
		mlx_loop(game.mlx);
		free_window(&game);
		//free_display(game);
		exit(EXIT_SUCCESS);
		return (0);
	//}
}

