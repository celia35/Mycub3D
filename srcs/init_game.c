# include "cub3d.h"

void	put_player_img(t_game *data, int *j, int *i)
{
	mlx_put_image_to_window(data->mlx, data->win,
		data->image->player, (*j) * 40, (*i) * 40);
	if (!data->image->player)
	{
		ft_printf("Failed to load player image");
	}
		
}

void	put_wall_img(t_game *data, int *j, int *i)
{
	mlx_put_image_to_window(data->mlx, data->win,
		data->image->wall, (*j) * 40, (*i) * 40);
}

void	put_empty_img(t_game *data, int *j, int *i)
{
	mlx_put_image_to_window(data->mlx, data->win,
		data->image->empty, (*j) * 40, (*i) * 40);
}

void	ft_create_map(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			put_empty_img(data, &j, &i); // toujours dessiner le fond d’abord
	
			if (data->map[i][j] == '1')
				put_wall_img(data, &j, &i);
			else if (data->map[i][j] == 'P')
			{
				if (data->on_exit && i == data->playerX && j == data->playerY)
				{
					// Dessine la sortie sous le joueur
					mlx_put_image_to_window(data->mlx, data->win,
					data->image->exit, j * 40, i * 40);
				}
				put_player_img(data, &j, &i);
			}
			else if (data->map[i][j] == 'E')
				mlx_put_image_to_window(data->mlx, data->win,
					data->image->exit, j * 40, i * 40);
			else if (data->map[i][j] == 'C')
				mlx_put_image_to_window(data->mlx, data->win,
					data->image->collect, j * 40, i * 40);
			j++;
		}
		i++;
	}
}