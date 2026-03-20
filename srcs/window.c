#include "cub3d.h"

void		param_init(t_mlx *mlx)
{
	mlx->x = 3;
	mlx->y = 4;
	mlx->str[0] = 'a';
	mlx->str[1] = 'b';
	mlx->str[2] = '\0';
}



int		key_press(int keycode, t_mlx *param)
{
	//static int a = 0;
	

	if (keycode == W)//Action when W key pressed
		param->x++;
	else if (keycode == S) //Action when S key pressed
		param->x--;
	else if (keycode == ESC) //Quit the program when ESC key pressed
		exit(0);
	printf("x: %d\n", param->x);
	return (0);
}

int		main(void)
{
	void	*mlx;
	void	*win;
	t_mlx	data;

	param_init(&data);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "mlx_project");
	printf("-------------------------------\n");
	printf("'W key': Add 1 to x.\n");
	printf("'S key': Subtract 1 from x\n");
	printf("'ESC key': Exit this program\n");
	printf("'Other keys': print current x \n");
	printf("-------------------------------\n");
	printf("Current x = 3\n");
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &data);
	mlx_loop(mlx);
	mlx_loop(mlx);
}
