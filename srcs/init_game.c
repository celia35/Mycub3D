# include "cub3d.h"

// int	ft_exit(void *param)
// {
// 	(void)param;
// 	exit(EXIT_SUCCESS);
// }

int	ft_exit(void *param)
{
	t_game	*data;

	data = (t_game *)param;
	free_game(data);
	exit(EXIT_SUCCESS);
}

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
// void	init_var(t_game *game)
// {
// 	int posX;
// 	int posY;

// 	//POUR SAVOIR DE QUELLE CASE DE LA GRILLE ON CE SITUE
// 	int mapX = posX;
// 	int mapY = posY;

// 	double sideDistX = game->sideDistX;
// 	double sideDistY = game->sideDistY;

// 	//distance entre 2 lignes verticles de la grille 
// 		//|| distance pour passer a la prochaine colonne
// 	double deltaDistX;
	
// 	//distance entre 2 lignes horizontales de la grille
// 		//distance pour passer a la prochaine ligne
// 	double deltaDistY;

// 	double rayDirX = game->rayDirX;
// 	double rayDirY = game->rayDirY;

// 	//DISTANCE D UN RAYON D'UN X SIDE OU Y SIDE JUSQU AU PROCHAIN X SIDE OU Y SIDE
// 	if (rayDirX == 0)
// 	{
// 		deltaDistX = 1e30;
// 		//1e30 sert d infini pratique, correspond a 10^30
// 	}
// 	else
// 	{
// 		deltaDistX = fabs(1 / rayDirX);
// 		//(1 / rayDirx) -> distance necessaire pour avancer d une unité sur l'axe X
// 	}
// 	if (rayDirY == 0)
// 	{
// 		deltaDistY = 1e30;
// 	}
// 	else
// 	{
// 		deltaDistY = fabs(1 / rayDirY);
// 	}                                           
// }

// void init_var_1(t_game *game)
// {
// 	//dans quelle direction bouger (faire un pas), vers x ou y directions (soit +1 ou -1)
// 	int	stepX;
// 	int stepY;

// 	double	rayDirX = game->rayDirX;
// 	double rayDirY = game->rayDirY;

// 	double sideDistX = game->sideDistX;
// 	double sideDistY = game->sideDistY;

// 	int posX;
// 	int posY;

// 	double deltaDistX;
// 	double deltaDistY;


// 	//POUR SAVOIR DE QUELLE CASE DE LA GRILLE ON CE SITUE
// 	int mapX = posX;
// 	int mapY = posY;

// 	//pour savoir si collision mur
// 	int hit = 0;

// 	//pour savoir si c est un mur NS ou un EW
// 	int side;

// 	//CALCULER LE DEPLACEMENT ET LA DISTANCE INITIALE JUSQU AU BORD
// 	if(rayDirX < 0)
// 	{
// 		stepX = -1;
// 		sideDistX = (posX - mapX) * deltaDistX;
// 	}
// 	else
// 	{
// 		stepX = 1;
// 		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
// 	}
// 	if (rayDirY < 0)
// 	{
// 		stepY = -1;
// 		sideDistY = (posY - mapY) * deltaDistY;
// 	}
// 	else
// 	{
// 		stepY = 1;
// 		sideDistY = (mapY = 1.0 - posY) * deltaDistY;
// 	}
// }


// int main_loop(t_game *game)
// {
// 	double x = 0;
// 	double y = 0;
// 	double w = 0;
// 	double rayDirX;
// 	double rayDirY;

// 	while (x < w)
// 	{
// 	//!camera_x (ou ici w), va de -1 (gauche) a +1(droite)!
// 		double cameraX = 2 * x / w - 1;
// 		//double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;

// 	//vecteur rayon = direction + plan de camera scalé
// 		rayDirX = game->dirX + game->planeX * cameraX;
// 		rayDirX = game->dirY + game->planeY * cameraX;
// 		x++;
// 	}
// }
