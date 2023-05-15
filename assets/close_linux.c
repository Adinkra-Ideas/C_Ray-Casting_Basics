
#include "cub3d.h"

int	close_cube(t_cube *cube)
{
	free_texture(cube);
	destroy_map(cube);
	mlx_destroy_image(cube->mlx, cube->img.img);
	mlx_clear_window(cube->mlx, cube->window);
	mlx_loop_end(cube->mlx);
	mlx_destroy_window(cube->mlx, cube->window);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit(1);
}
