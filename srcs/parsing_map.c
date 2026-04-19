#include "cub3d.h"

void	ft_validate_map(t_game *data)
{
	int		y;
	int		x;
	int		spawn_count;
	char	c;

	spawn_count = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			c = data->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				spawn_count++;
				data->playerX = x;
				data->playerY = y;
				data->spawn_dir = c;
				data->map[y][x] = '0';
			}
			else if (c != '0' && c != '1' && c != ' ')
			{
				ft_printf("Error\nInvalid char '%c' in map\n", c);
				free_game(data);
				exit(EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
	if (spawn_count == 0)
		error_exit("no spawn point", data);
	if (spawn_count > 1)
		error_exit("multiple spawn points", data);
}

static void	check_borders(t_game *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width)
	{
		if (data->map[0][x] != '1')
			error_exit("map border not closed (top)", data);
		if (data->map[data->height - 1][x] != '1')
			error_exit("map border not closed (bottom)", data);
		x++;
	}
	y = 0;
	while (y < data->height)
	{
		if (data->map[y][0] != '1')
			error_exit("map border not closed (left)", data);
		if (data->map[y][data->width - 1] != '1')
			error_exit("map border not closed (right)", data);
		y++;
	}
}

static void	check_spaces(t_game *data)
{
	int	dx[4];
	int	dy[4];
	int	y;
	int	x;
	int	i;
	int	nx;
	int	ny;

	dx[0] = 0; dx[1] = 0; dx[2] = 1; dx[3] = -1;
	dy[0] = 1; dy[1] = -1; dy[2] = 0; dy[3] = 0;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->map[y][x] == '0')
			{
				i = 0;
				while (i < 4)
				{
					nx = x + dx[i];
					ny = y + dy[i];
					if (ny < 0 || ny >= data->height
						|| nx < 0 || nx >= data->width
						|| data->map[ny][nx] == ' ')
						error_exit("space adjacent to walkable cell", data);
					i++;
				}
			}
			x++;
		}
		y++;
	}
}

static void	flood_fill(t_game *data, char **copy, int x, int y)
{
	int	queue[10000][2];
	int	head;
	int	tail;
	int	dx[4];
	int	dy[4];
	int	cx;
	int	cy;
	int	i;

	dx[0] = 0; dx[1] = 0; dx[2] = 1; dx[3] = -1;
	dy[0] = 1; dy[1] = -1; dy[2] = 0; dy[3] = 0;
	head = 0;
	tail = 0;
	queue[tail][0] = x;
	queue[tail][1] = y;
	tail++;
	while (head < tail)
	{
		cx = queue[head][0];
		cy = queue[head][1];
		head++;
		if (cy < 0 || cy >= data->height || cx < 0 || cx >= data->width)
			error_exit("map not closed", data);
		if (copy[cy][cx] == ' ' || copy[cy][cx] == '\0')
			error_exit("map not closed", data);
		if (copy[cy][cx] == '1' || copy[cy][cx] == 'V')
			continue ;
		copy[cy][cx] = 'V';
		i = 0;
		while (i < 4)
		{
			queue[tail][0] = cx + dx[i];
			queue[tail][1] = cy + dy[i];
			tail++;
			i++;
		}
	}
}

void	ft_check_map(t_game *data)
{
	char	**copy;
	int		i;

	check_borders(data);
	check_spaces(data);
	copy = malloc(sizeof(char *) * (data->height + 1));
	if (!copy)
		error_exit("malloc failed", data);
	i = 0;
	while (data->map[i])
	{
		copy[i] = ft_strdup(data->map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			error_exit("malloc failed", data);
		}
		i++;
	}
	copy[i] = NULL;
	flood_fill(data, copy, data->playerX, data->playerY);
	i = 0;
	while (copy[i])
		free(copy[i++]);
	free(copy);
}