#include "../includes/cub3d.h"

int check_args(char *map_name){
	int fd;

	if (ft_strnstr(map_name + ft_strlen(map_name) - 4, ".cub", 4) == NULL)
	{
		printf("Wrong map extension proper map name: map_name.cub\n");
		exit(0);
	}

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(-1);
	}
	close(fd);
	return 1;		
}
