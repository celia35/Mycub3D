#include "cub3d.h"

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
		ft_printf("Error opening file \n");
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
		ft_printf("Error: no map found\n");
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


void	ft_read_map(t_game *data)
{
	int		fd;
	char	*line = 0;
	int		i;

	fd = open(data->fn, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: cannot open file\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	line = ft_get_next_line(fd);
	while (line && i < data->map_start)
	{
		free (line);
		line = ft_get_next_line(fd);
		i++;
	}
	data->map = (char **)malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
        exit(EXIT_FAILURE);
    i = 0;
    while (line && i < data->height)
    {
        line = trim_newline(line);
        data->map[i] = line;
        line = ft_get_next_line(fd);
        i++;
    }
    data->map[i] = NULL;
    if (line)
        free(line);
    close(fd);
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
        ft_printf("Error: invalid RGB format\n");
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
        		ft_printf("Error: RGB must be numeric (spaces not allowed)\n");
        		exit(EXIT_FAILURE);
    		}
    	j++;
		}
        rgb[i] = ft_atoi(trimmed);
        if (rgb[i] < 0 || rgb[i] > 255)
        {
            ft_printf("Error: RGB value out of range [0-255]\n");
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
        ft_printf("Error: cannot open file\n");
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
            { ft_printf("Error: duplicate NO\n"); exit(EXIT_FAILURE); }
            data->conf.tex_no = get_tex_path(line + j + 2, "");
            data->conf.tex_parsed |= 1;
        }
        else if (ft_strncmp(line + j, "SO ", 3) == 0)
        {
            if (data->conf.tex_parsed & 2)
            { ft_printf("Error: duplicate SO\n"); exit(EXIT_FAILURE); }
            data->conf.tex_so = get_tex_path(line + j + 2, "");
            data->conf.tex_parsed |= 2;
        }
        else if (ft_strncmp(line + j, "WE ", 3) == 0)
        {
            if (data->conf.tex_parsed & 4)
            { ft_printf("Error: duplicate WE\n"); exit(EXIT_FAILURE); }
            data->conf.tex_we = get_tex_path(line + j + 2, "");
            data->conf.tex_parsed |= 4;
        }
        else if (ft_strncmp(line + j, "EA ", 3) == 0)
        {
            if (data->conf.tex_parsed & 8)
            { ft_printf("Error: duplicate EA\n"); exit(EXIT_FAILURE); }
            data->conf.tex_ea = get_tex_path(line + j + 2, "");
            data->conf.tex_parsed |= 8;
        }
        else if (ft_strncmp(line + j, "F ", 2) == 0)
        {
            if (data->conf.tex_parsed & 16)
            { ft_printf("Error: duplicate F\n"); exit(EXIT_FAILURE); }
            parse_rgb(line + j + 2, data->conf.floor);
            data->conf.tex_parsed |= 16;
        }
        else if (ft_strncmp(line + j, "C ", 2) == 0)
        {
            if (data->conf.tex_parsed & 32)
            { ft_printf("Error: duplicate C\n"); exit(EXIT_FAILURE); }
            parse_rgb(line + j + 2, data->conf.ceil);
            data->conf.tex_parsed |= 32;
        }
        else
        {
            ft_printf("Error: unknown identifier: %s\n", line + j);
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
        ft_printf("Error: missing identifier(s) ");
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