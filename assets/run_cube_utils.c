
#include "cub3d.h"

void	destroy_map(t_cube *cube)
{
	int	i;

	i = 0;
	while (cube->map && cube->map[i])
	{
		free(cube->map[i]);
		i++;
	}
	if (cube->map)
		free(cube->map);
}

void	free_texture(t_cube *cube)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(cube->textures[i]);
	free(cube->textures);
}

void	set_orientation(t_cube *cube)
{
	cube->ply.dir.x = 0.0;
	cube->ply.dir.y = 0.0;
	cube->rays.plane.x = 0.0;
	cube->rays.plane.y = 0.0;
	if (cube->ply.orient == 'W')
	{
		cube->ply.dir.y = -1.0;
		cube->rays.plane.x = 0.66;
	}
	else if (cube->ply.orient == 'E')
	{
		cube->ply.dir.y = 1.0;
		cube->rays.plane.x = -0.66;
	}
	else if (cube->ply.orient == 'N')
	{
		cube->ply.dir.x = -1.0;
		cube->rays.plane.y = 0.66;
	}
	else if (cube->ply.orient == 'S')
	{
		cube->ply.dir.x = 1.0;
		cube->rays.plane.y = -0.66;
	}
}

void	orientation_init(t_cube *cube)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (cube->map[++i] && j < 0)
		j = ft_strstrchr(cube->map[i], "NSEW");
	cube->ply.pos.x = (double)(i - 1);
	cube->ply.pos.y = (double)j + 0.5;
	cube->ply.orient = cube->map[(int)cube->ply.pos.x][(int)cube->ply.pos.y];
	set_orientation(cube);
}

// **************************************
// Simple convertor function to return	*
// hex value of RGB dereferenced by		*
// param								*
// **************************************
size_t	rgb_to_hex(int *rgb)
{
	size_t	hex;

	hex = 0;
	hex += rgb[0] * 65536;
	hex += rgb[1] * 256;
	hex += rgb[2];
	return (hex);
}
