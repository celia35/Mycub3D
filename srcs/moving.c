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

void		create_mov(t_game *game)
{
	int hit;
	int side;

	hit = 0;

	double sideDistX;
	double sideDistY;

	double deltaDistX;
	double deltaDistY;

	int mapX;
	int mapY;

	int stepX;
	int stepY;
	
	//perform DDA
	while (hit == 0)
	{
		//jump to n=next map square, either in x-direction, or in y-direction
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if (game->map[mapX][mapY] > 0)
			hit = 1;
	}
}

void	camera_dir(t_game *game)
{
	if (game->side == 0)
		game->perpWallDist = (game->sideDistX - game->deltaDistX);
	else
		game->perpWallDist = (game->sideDistY - game->deltaDistX);
}
void	ver_line(t_game *game, t_mlx *mlx, int x, int draw_start, int draw_end, int color)
{
	int y;

	y = draw_start;
	while(y <= draw_end)
	{
		my_pixel_put(mlx->mlx, mlx->win, x, y, color);
		y++;
	}
}

void	camera_init(t_game *game, t_mlx *mlx)
{
	int drawStart;
	int drawEnd;
	int lineHeight;
	int color;
	int h;

	//h = game->mapY + (1 - game->stepY) / 2;
	h = SCREEN_HEIGHT; // hauteur de l'écran, 

	//hauteur de la ligne a dessiner
	lineHeight = (int) (h / game->perpWallDist);

	//Pixel le plus bas et le plus haut
	drawStart = -lineHeight / 2 + h / 2;
	if (drawStart < 0) 
		drawStart = 0;

	drawEnd = lineHeight / 2 + h / 2;
	if (drawEnd >= h)
		drawEnd = h - 1;
	
	//choose wall color
      //ColorRGB color;
      switch(game->map[game->mapX][game->mapY])
      {
        case 1:  color = 0x00FF0000;  break; //red
        case 2:  color = 0x0000FF00;  break; //green
        case 3:  color = 0x000000FF;   break; //blue
        case 4:  color = 0x00FFFFFF;  break; //white
        default: color = 0x00FFFF00; break; //yellow
      }

      //give x and y sides different brightness => assombrir les faces Nord/Sud
      if (game->side == 1) 
	  {
		
		color =((color >> 1) & 0x007F7F7F); //divise R, G, B par 2
	  }

      //Dessiner la ligne verticale
      verLine(mlx->x, drawStart, drawEnd, color);
}

void	camera_rotate(t_game *game)
{
	
}
