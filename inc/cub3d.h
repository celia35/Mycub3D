#ifndef CUB3D_H
#define CUB3D_H

typedef struct s_window
{
	void	*mlx;
	void	*window;
	void	**map;
	int		width;
	int		height;

	double	x_player;
	double	y_player;
}t_window;

#endif

