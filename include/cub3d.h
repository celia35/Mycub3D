#ifndef CUB3D_H
#define CUB3D_H

# define Q 113
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define EXIT_SUCCESS 0

# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_img{
	void	*mlx_img;
}t_img;

typedef struct s_mlx{
	void	*win;
	void	*mlx;
}t_mlx;

typedef struct s_data{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	
	int		playerX;
	int		playerY;

	int		dirX;
	int		dirY;

	double	planeX;
	double	planeY;
}t_game;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	void	**map;
	int		width;
	int		height;
}t_window;

#endif

