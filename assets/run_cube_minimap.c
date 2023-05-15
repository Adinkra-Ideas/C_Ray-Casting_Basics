
#include "cub3d.h"

void	draw_minimap(t_cube *cube, int x, int y, unsigned int color)
{
	int	i;
	int	j;

	if (x != 0)
		x *= 4;
	if (y != 0)
		y *= 4;
	i = x + 4;
	j = y + 4;
	while (x < i)
	{
		y = j - 4;
		while (y < j)
		{
			cube->buf[x][y] = color;
			y++;
		}
		x++;
	}
}

void	render_minimap(t_cube *cube)
{
	int	i;
	int	j;

	i = -1;
	while (cube->map[++i])
	{
		j = -1;
		while (cube->map[i][++j])
		{
			if (cube->map[i][j] == '1')
				draw_minimap(cube, i, j, MMAP_WAL);
			else
				draw_minimap(cube, i, j, MMAP_NUL);
		}
	}
	draw_minimap(cube, (int)cube->ply.pos.x, (int)cube->ply.pos.y, MMAP_PLY);
}
