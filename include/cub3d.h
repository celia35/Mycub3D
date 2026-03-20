#ifndef CUB3D_H
#define CUB3D_H

#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_RELEASE 3
#define X_EVENT_KEY_EXIT 17

# define WALL		"./img/wall.xpm"
# define EMPTY		"./img/floor.xpm"
# define PLAYER		"./img/player-copie.xpm"
# define EXIT		"./img/exit.xpm"
# define COLLECT	"./img/floor-copie.xpm"
# define WIN		"./img/open-exit.xpm"


# define Q 113
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
//# define EXIT_SUCCESS 0

# include "mlx.h"
# include "../libft/libft.h" 
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_img{
	void	*mlx_img;
	void	*wall;
	void	*empty;
	void	*collect;
	void	*exit;
	void	*player;
	void	*winner;
}t_img;

typedef struct s_mlx{
	void	*win;
	void	*mlx;

	int		x;
	int		y;
	char	str[3];
}t_mlx;

typedef struct s_data{
	void	*mlx;
	void	*win;
	int		width;
	int		height;

	char	*fn;
	
	int		playerX;
	int		playerY;

	int		dirX;
	int		dirY;

	double	planeX;
	double	planeY;

	char	**map;

	int		on_exit;

	int		player;

	t_img	*image;
}t_game;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	void	**map;
	int		width;
	int		height;
}t_window;


//moving
int	ft_exit(t_game *data);
void	move_player(t_game *data, int new_x, int new_y);

void	move_w(t_game *data);
void	move_s(t_game *data);
void	move_a(t_game *data);
void	move_d(t_game *data);

int	press_key(int keycode, t_game *data);

//init_game
void	put_player_img(t_game *data, int *j, int *i);
void	put_wall_img(t_game *data, int *j, int *i);
void	put_empty_img(t_game *data, int *j, int *i);
void	ft_create_map(t_game *data);

//init_map
void	ft_map_height(t_game *data);
char	*trim_newline(char *line);
void	ft_read_map(t_game *data);
void	ft_find_player_position(t_game *data);

//main
void	ft_parse_map(t_game *data);
void	ft_map_data(t_game *data, char *name);
int		main(int ac, char **av);


#endif

