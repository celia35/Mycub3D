# include "cub3d.h"

static int is_map_line(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' 
			&& line[i] != 'E' && line[i] != 'W' )
			return (0);
		i++;
	}
	return (i > 0);
}

void	ft_map_height(t_game *data)
{
	char	*line;
	int		fd;
	int		in_map;

	fd = open(data->fn, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nopening file \n");
		exit(EXIT_FAILURE);
	}
	in_map = 0;
	data->height = 0;
	data->map_start = 0;
	data->width = 0;
	line = ft_get_next_line(fd);
	while (line)
	{
		if (!in_map && is_map_line(line))
			in_map = 1;
		if (in_map)
		{
			int len = 0;
			while (line[len] && line[len] != '\n')
				len++;

			if (len > data->width)
				data->width = len;
			data ->height++;
		}
		else
			data ->map_start++;
		free(line);
		line = ft_get_next_line(fd);
	}
	if (data->height == 0)
	{
		ft_printf("Error\nno map found\n");
		exit(EXIT_FAILURE);
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

static char *get_tex_path(char *line, char *prefix)
{
    int     plen;
    int     start;
    char    *path;

    plen = ft_strlen(prefix);
    start = plen;
    // Sauter les espaces après le préfixe
    while (line[start] == ' ' || line[start] == '\t')
        start++;
    // Copier jusqu'au \n ou \0
    int end = start;
    while (line[end] && line[end] != '\n')
        end++;
    path = ft_substr(line, start, end - start);
	if (!path)
    	error_exit("malloc failed", NULL);
    return (path);
}

static void parse_rgb(char *str, int rgb[3])
{
    char    **parts;
    int     i;

    // Sauter les espaces avant
    while (*str == ' ' || *str == '\t')
        str++;
    parts = ft_split(str, ',');
    if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
    {
        ft_printf("Error\ninvalid RGB format\n");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while (i < 3)
    {
        // Trim espaces autour de chaque valeur
        char *trimmed = parts[i];
        while (*trimmed == ' ' || *trimmed == '\t')
            trimmed++;
        // Vérifier numérique
		int j = 0;
		while (trimmed[j] && trimmed[j] != '\n')
		{
    		if (trimmed[j] < '0' || trimmed[j] > '9')
    		{
        		ft_printf("Error\nRGB must be numeric (spaces not allowed)\n");
        		exit(EXIT_FAILURE);
    		}
    	j++;
		}
        rgb[i] = ft_atoi(trimmed);
        if (rgb[i] < 0 || rgb[i] > 255)
        {
            ft_printf("Error\nRGB value out of range [0-255]\n");
            exit(EXIT_FAILURE);
        }
        free(parts[i]);
        i++;
    }
    free(parts);
}

void    ft_parse_identifiers(t_game *data)
{
    char    *line;
    int     fd;
    int     i;

    fd = open(data->fn, O_RDONLY);
    if (fd < 0)
    {
        ft_printf("Error\ncannot open file\n");
        exit(EXIT_FAILURE);
    }
    data->conf.tex_parsed = 0;
    i = 0;
    line = ft_get_next_line(fd);
    while (line && i < data->map_start)
    {
        // Sauter les lignes vides
        int j = 0;
        while (line[j] == ' ' || line[j] == '\t')
            j++;
        if (line[j] == '\n' || line[j] == '\0')
        {
            free(line);
            line = ft_get_next_line(fd);
            i++;
            continue ;
        }
        // Parser selon le préfixe
        if (ft_strncmp(line + j, "NO ", 3) == 0)
        {
            if (data->conf.tex_parsed & 1)
            { ft_printf("Error\nduplicate NO\n"); exit(EXIT_FAILURE); }
            data->conf.tex_no = get_tex_path(line + j + 2, "");
            data->conf.tex_parsed |= 1;
        }
        else if (ft_strncmp(line + j, "SO ", 3) == 0)
        {
            if (data->conf.tex_parsed & 2)
            { ft_printf("Error\nduplicate SO\n"); exit(EXIT_FAILURE); }
            data->conf.tex_so = get_tex_path(line + j + 2, "");
            data->conf.tex_parsed |= 2;
        }
        else if (ft_strncmp(line + j, "WE ", 3) == 0)
        {
            if (data->conf.tex_parsed & 4)
            { ft_printf("Error\nduplicate WE\n"); exit(EXIT_FAILURE); }
            data->conf.tex_we = get_tex_path(line + j + 2, "");
            data->conf.tex_parsed |= 4;
        }
        else if (ft_strncmp(line + j, "EA ", 3) == 0)
        {
            if (data->conf.tex_parsed & 8)
            { ft_printf("Error\nduplicate EA\n"); exit(EXIT_FAILURE); }
            data->conf.tex_ea = get_tex_path(line + j + 2, "");
            data->conf.tex_parsed |= 8;
        }
        else if (ft_strncmp(line + j, "F ", 2) == 0)
        {
            if (data->conf.tex_parsed & 16)
            { ft_printf("Error\nduplicate F\n"); exit(EXIT_FAILURE); }
            parse_rgb(line + j + 2, data->conf.floor);
            data->conf.tex_parsed |= 16;
        }
        else if (ft_strncmp(line + j, "C ", 2) == 0)
        {
            if (data->conf.tex_parsed & 32)
            { ft_printf("Error\nduplicate C\n"); exit(EXIT_FAILURE); }
            parse_rgb(line + j + 2, data->conf.ceil);
            data->conf.tex_parsed |= 32;
        }
        else
        {
            ft_printf("Error\nunknown identifier: %s\n", line + j);
            free(line);
            close(fd);
            exit(EXIT_FAILURE);
        }
        free(line);
        line = ft_get_next_line(fd);
        i++;
    }
    free(line);
    close(fd);
    // Vérifier que les 6 identifiants sont présents
    if (data->conf.tex_parsed != 63)  // 0b111111 = 63
    {
        ft_printf("Error\nmissing identifier(s) ");
        ft_printf("(parsed mask: %d/63)\n", data->conf.tex_parsed);
        exit(EXIT_FAILURE);
    }
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


static char	*pad_line(char *line, int target_width)
{
	char	*padded;
	int		len;
	int		j;

	len = ft_strlen(line);
	if (len >= target_width)
		return (line);
	padded = ft_calloc(target_width + 1, sizeof(char));
	if (!padded)
		exit(EXIT_FAILURE);
	j = 0;
	while (j < len)
	{
		padded[j] = line[j];
		j++;
	}
	while (j < target_width)
		padded[j++] = ' ';
	free(line);
	return (padded);
}

static int	open_and_skip(t_game *data)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(data->fn, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\ncannot open file\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < data->map_start)
	{
		line = ft_get_next_line(fd);
		free(line);
		i++;
	}
	return (fd);
}
static void	fill_map(t_game *data, int fd)
{
	char	*line;
	int		i;

	data->map = (char **)malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		exit(EXIT_FAILURE);
	i = 0;
	line = ft_get_next_line(fd);
	while (line && i < data->height)
	{
		line = trim_newline(line);
		// ft_printf("map[%d] len=%d : '%s'\n", i, (int)ft_strlen(line), line); // DEBUG
		data->map[i] = pad_line(line, data->width);
		line = ft_get_next_line(fd);
		i++;
	}
	// ft_printf("total lines read: %d / expected: %d\n", i, data->height); // DEBUG
	data->map[i] = NULL;
	if (line)
		free(line);
}

void	ft_read_map(t_game *data)
{
	int	fd;

	fd = open_and_skip(data);
	fill_map(data, fd);
	close(fd);
}
void	ft_validate_map(t_game *data)
{
	int	y;
	int	x;
	int	spawn_count;
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
				exit(EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
	if (spawn_count == 0)
	{ ft_printf("Error\nNo spawn point\n"); exit(EXIT_FAILURE); }
	if (spawn_count > 1)
	{ ft_printf("Error\nMultiple spawn points\n"); exit(EXIT_FAILURE); }
}

static void	flood_fill(t_game *data, char **copy, int x, int y)
{
	int	queue[10000][2];
	int	head;
	int	tail;
	int	dx[4];
	int	dy[4];

	dx[0] = 0; dx[1] = 0; dx[2] = 1; dx[3] = -1;
	dy[0] = 1; dy[1] = -1; dy[2] = 0; dy[3] = 0;
	head = 0;
	tail = 0;
	queue[tail][0] = x;
	queue[tail][1] = y;
	tail++;
	while (head < tail)
	{
		int cx = queue[head][0];
		int cy = queue[head][1];
		int i = 0;
		head++;
		if (cy < 0 || cy >= data->height || cx < 0 || cx >= data->width)
		{ ft_printf("Error\nMap not closed\n"); exit(EXIT_FAILURE); }
		if (copy[cy][cx] == ' ' || copy[cy][cx] == '\0')
		{ ft_printf("Error\nMap not closed\n"); exit(EXIT_FAILURE); }
		if (copy[cy][cx] == '1' || copy[cy][cx] == 'V')
			continue ;
		copy[cy][cx] = 'V';
		while (i < 4)
		{
			queue[tail][0] = cx + dx[i];
			queue[tail][1] = cy + dy[i];
			tail++;
			i++;
		}
	}
}

//appele dans le check_map
static void	check_borders(t_game *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width)
	{
		if (data->map[0][x] != '1')
		{
			ft_printf("Error\nMap border not closed (top)\n");
			exit(EXIT_FAILURE);
		}
		if (data->map[data->height - 1][x] != '1')
		{
			ft_printf("Error\nMap border not closed (bottom)\n");
			exit(EXIT_FAILURE);
		}
		x++;
	}
	y = 0;
	while (y < data->height)
	{
		if (data->map[y][0] != '1')
		{
			ft_printf("Error\nMap border not closed (left)\n");
			exit(EXIT_FAILURE);
		}
		if (data->map[y][data->width - 1] != '1')
		{
			ft_printf("Error\nMap border not closed (right)\n");
			exit(EXIT_FAILURE);
		}
		y++;
	}
}

//appele dans check map aussi
static void	check_spaces(t_game *data)
{
	int	y;
	int	x;
	int	dx[4];
	int	dy[4];
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
					{
						ft_printf("Error\nSpace adjacent to walkable cell\n");
						exit(EXIT_FAILURE);
					}
					i++;
				}
			}
			x++;
		}
		y++;
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

void	ft_init_player_dir(t_game *data)
{
	if (data->spawn_dir == 'N')
	{
		data->dirX = 0;
		data->dirY = -1;
		data->planeX = 0.66;
		data->planeY = 0;
	}
	else if (data->spawn_dir == 'S')
	{
		data->dirX = 0;
		data->dirY = 1;
		data->planeX = -0.66;
		data->planeY = 0;
	}
	else if (data->spawn_dir == 'E')
	{
		data->dirX = 1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = 0.66;
	}
	else if (data->spawn_dir == 'W')
	{
		data->dirX = -1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = -0.66;
	}
}





