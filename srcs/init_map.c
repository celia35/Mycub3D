# include "cub3d.h"

void	ft_map_height(t_game *data)
{
	char	*line;
	int		fd;

	fd = open(data->fn, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("je suis  dans fd < 0 \n");
		ft_printf("Error opening file \n");
		exit(EXIT_FAILURE);
	}

	line = ft_get_next_line(fd);
	if (!line)
	{
		ft_printf("Error : file empty\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	data->width = 0;
	while (line[data->width] && line[data->width] != '\n')
		data->width++;

	while (line)
	{
		int len = 0;
		while (line[len] && line[len] != '\n')
			len++;

		if (len != data->width)
		{
			ft_printf("Error: invalid lign (len=%d au lieu de %d)\n", len, data->width);
			free(line);
			close(fd);
			exit(EXIT_FAILURE);
		}

		data->height++;
		free(line);
		line = ft_get_next_line(fd);
	}

	close(fd);
}




char	*trim_newline(char *line)
{
	int	len = ft_strlen(line);

	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}


void	ft_read_map(t_game *data)
{
	int		fd;
	char	*line = 0;
	int		i;

	fd = open(data->fn, O_RDONLY);
	line = ft_get_next_line(fd);
	data->map = (char **)malloc(sizeof(char *) * (data->height + 1));
	i = 0;
	while (line)
	{
		line = trim_newline(line);
		data->map[i] = line;
		line = ft_get_next_line(fd);
		i++;
	}
	data->map[i] = NULL;
	free(line);
	line = NULL;
	close(fd);
}

void	ft_find_player_position(t_game *data)
{
	int i = 0;
	while (data->map[i])
	{
		int j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'P')
			{
				data->playerX = j;
				data->playerY = i;
				ft_printf("Initial player position: (%d, %d)\n", data->playerX, data->playerY);
				return;
			}
			j++;
		}
		i++;
	}
}