# include "cub3d.h"

int	ft_exit(t_game *data)
{
	(void) *data;
	exit(EXIT_SUCCESS);
}

void	move_player(t_game *data, int new_x, int new_y)
{
	char next_tile = data->map[new_y][new_x];

	if (next_tile == '1') // mur
		return ;

	// if (next_tile == 'C') // collectible
	// {
	// 	data->count--;
	// }
	else if (next_tile == 'E')
	{
		// if (data->count == 0)
		// {
		// 	data->escape = 1;
			data->on_exit = 1;
	}
		else
			return; // empêche d'aller sur la sortie si collectibles restants
	// else
	data->on_exit = 0;

	data->map[data->playerY][data->playerX] = data->on_exit ? 'E' : '0';// ancienne position
	data->map[new_y][new_x] = 'P';          // nouvelle position
	data->playerX = new_x;
	data->playerY = new_y;
	// data->step++;

	// ft_printf("Steps: %d\n", data->step);
}

void	move_w(t_game *data)
{
	move_player(data, data->playerX, data->playerY - 1);
}

void	move_s(t_game *data)
{
	move_player(data, data->playerX, data->playerY + 1);
}

void	move_a(t_game *data)
{
	move_player(data, data->playerX - 1, data->playerY);
}

void	move_d(t_game *data)
{
	move_player(data, data->playerX + 1, data->playerY);
}


int	press_key(int keycode, t_game *data)
{
	ft_printf("Touche pressée : %d\n", keycode);
	if (keycode == ESC)
		ft_exit(data);
	else if (keycode == Q)
		ft_exit(data);
	else if (keycode == W)
		move_w(data);
	else if (keycode == A)
		move_a(data);
	else if (keycode == S)
		move_s(data);
	else if (keycode == D)
		move_d(data);

	mlx_clear_window(data->mlx, data->win); 
	// ft_create_map(data);                    

	// if (data->count == 0 && data->on_exit == 1)
	// 	ft_game_result(data);

	return (0);
}