#ifndef MAP_PARSING_H
#define MAP_PARSING_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_data {
	char	*north_path;
	char	*south_path;
	char	*west_past;
	char	*east_path;
	int		ceiling_color;
	int		floor_color;
	int		floor_color;
} t_data;

#endif



