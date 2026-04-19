#include "cub3d.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
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
	int		len;

	fd = open(data->fn, O_RDONLY);
	if (fd < 0)
		error_exit("cannot open file", data);
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
			len = 0;
			while (line[len] && line[len] != '\n')
				len++;
			if (len > data->width)
				data->width = len;
			data->height++;
		}
		else
			data->map_start++;
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	if (data->height == 0)
		error_exit("no map found", data);
}

char	*trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static char	*pad_line(char *line, int target_width, t_game *data)
{
	char	*padded;
	int		len;
	int		j;

	len = ft_strlen(line);
	if (len >= target_width)
		return (line);
	padded = ft_calloc(target_width + 1, sizeof(char));
	if (!padded)
		error_exit("malloc failed", data);
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
		error_exit("cannot open file", data);
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
		error_exit("malloc failed", data);
	i = 0;
	line = ft_get_next_line(fd);
	while (line && i < data->height)
	{
		line = trim_newline(line);
		data->map[i] = pad_line(line, data->width, data);
		line = ft_get_next_line(fd);
		i++;
	}
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