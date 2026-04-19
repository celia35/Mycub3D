#include "cub3d.h"

static char	*get_tex_path(char *line)
{
	int		start;
	int		end;
	char	*path;

	start = 0;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	end = start;
	while (line[end] && line[end] != '\n')
		end++;
	path = ft_substr(line, start, end - start);
	if (!path)
		return (NULL);
	return (path);
}

static void	parse_rgb(char *str, int rgb[3], t_game *data)
{
	char	**parts;
	int		i;
	int		j;
	char	*trimmed;

	while (*str == ' ' || *str == '\t')
		str++;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		error_exit("invalid RGB format (expected R,G,B)", data);
	i = 0;
	while (i < 3)
	{
		trimmed = parts[i];
		while (*trimmed == ' ' || *trimmed == '\t')
			trimmed++;
		j = 0;
		while (trimmed[j] && trimmed[j] != '\n')
		{
			if (trimmed[j] < '0' || trimmed[j] > '9')
			{
				free(parts[i]);
				free(parts);
				error_exit("RGB must be numeric", data);
			}
			j++;
		}
		rgb[i] = ft_atoi(trimmed);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free(parts[i]);
			free(parts);
			error_exit("RGB value out of range [0-255]", data);
		}
		free(parts[i]);
		i++;
	}
	free(parts);
}

static void	parse_line(char *line, int j, t_game *data, int fd)
{
	if (ft_strncmp(line + j, "NO ", 3) == 0)
	{
		if (data->conf.tex_parsed & 1)
			error_exit("duplicate NO", data);
		data->conf.tex_no = get_tex_path(line + j + 3);
		data->conf.tex_parsed |= 1;
	}
	else if (ft_strncmp(line + j, "SO ", 3) == 0)
	{
		if (data->conf.tex_parsed & 2)
			error_exit("duplicate SO", data);
		data->conf.tex_so = get_tex_path(line + j + 3);
		data->conf.tex_parsed |= 2;
	}
	else if (ft_strncmp(line + j, "WE ", 3) == 0)
	{
		if (data->conf.tex_parsed & 4)
			error_exit("duplicate WE", data);
		data->conf.tex_we = get_tex_path(line + j + 3);
		data->conf.tex_parsed |= 4;
	}
	else if (ft_strncmp(line + j, "EA ", 3) == 0)
	{
		if (data->conf.tex_parsed & 8)
			error_exit("duplicate EA", data);
		data->conf.tex_ea = get_tex_path(line + j + 3);
		data->conf.tex_parsed |= 8;
	}
	else if (ft_strncmp(line + j, "F ", 2) == 0)
	{
		if (data->conf.tex_parsed & 16)
			error_exit("duplicate F", data);
		parse_rgb(line + j + 2, data->conf.floor, data);
		data->conf.tex_parsed |= 16;
	}
	else if (ft_strncmp(line + j, "C ", 2) == 0)
	{
		if (data->conf.tex_parsed & 32)
			error_exit("duplicate C", data);
		parse_rgb(line + j + 2, data->conf.ceil, data);
		data->conf.tex_parsed |= 32;
	}
	else
	{
		free(line);
		close(fd);
		error_exit("unknown identifier", data);
	}
}

void	ft_parse_identifiers(t_game *data)
{
	char	*line;
	int		fd;
	int		i;
	int		j;

	fd = open(data->fn, O_RDONLY);
	if (fd < 0)
		error_exit("cannot open file", data);
	data->conf.tex_parsed = 0;
	i = 0;
	line = ft_get_next_line(fd);
	while (line && i < data->map_start)
	{
		j = 0;
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (line[j] != '\n' && line[j] != '\0')
			parse_line(line, j, data, fd);
		free(line);
		line = ft_get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	if (data->conf.tex_parsed != 63)
	{
		ft_printf("Error\nMissing identifier(s) (mask: %d/63)\n",
			data->conf.tex_parsed);
		free_game(data);
		exit(EXIT_FAILURE);
	}
}