#ifndef CUB3D_H
#define CUB3D_H

#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_RELEASE 3
#define X_EVENT_KEY_EXIT 17

#define SCREEN_WIDTH 800 //640
#define SCREEN_HEIGHT 600 //480

#define NO	1
#define S0	2
#define WE	3
#define EA	4

#define TEX_NO 0
#define TEX_SO 1
#define TEX_WE 2
#define TEX_EA 3

#define RED		0x00FF0000
#define GREEN	0x0000FF00
#define BLUE 	0x000000FF
#define WHITE	0x00FFFFFF
#define YELLOW	0x00FFFF00

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
# include <math.h>

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

typedef	struct s_conf{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor[3];
	int		ceil[3];
	int		tex_parsed; //bitmask : 1=NO 2=SO 4=WE 8=EA 16=F 32=C
}t_conf;
typedef struct s_data{
	//void	*mlx;
	void	*win;
	int		width;
	int		height;
	int		map_start;

	char	*fn;
	
	int		playerX;
	int		playerY;

	int		dirX;
	int		dirY;

	int		stepX;
	int		stepY;

	double	deltaDistX;
	double	deltaDistY;

	double	perpWallDist;

	double	planeX;
	double	planeY;

	double rayDirX;
	double rayDirY;

	double sideDistX;
	double sideDistY;

	double  posX;
	double  posY;
	//double  dirX;
	//double  dirY;
	//double  planeX;
	//double  planeY;
	double  frameTime;
	long    time;
	long    oldTime;

	//for camera
	int		side;

	char	**map;
	int		mapX;
	int		mapY;

	int		on_exit;

	int		player;

	t_conf	conf;
	t_img	*image;
	t_mlx	*mlx;
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
int		ft_exit(void *param);
void	move_player(t_game *data, int new_x, int new_y);

void	move_w(t_game *data);
void	move_s(t_game *data);
void	move_a(t_game *data);
void	move_d(t_game *data);

int	press_key(int keycode, void *data);

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

//parsing
void	ft_check_format(t_game *game);
void    ft_parse_identifiers(t_game *data);


#endif

