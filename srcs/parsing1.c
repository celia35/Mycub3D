#include "cub3d.h"

void	ft_check_format(t_game *game)
{
	char	*cub;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	cub = "cub";
	len = ft_strlen(game->fn);
	if(len < 3)
	{
		ft_printf("Error: Check file extansion");
		exit(EXIT_FAILURE);
	}
	i = len - 3;
	while (game->fn[i] != '\0' && cub[j] != '\0')
	{
		if (game->fn[i] != cub[j])
		{
			ft_printf("Error: Check file extansion");
			exit(EXIT_FAILURE);
		}
		i++;
		j++;
	}
}