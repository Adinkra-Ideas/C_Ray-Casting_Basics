
#include "../assets/cub3d.h"

void	load_image(t_cube *cube, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	img->img = mlx_xpm_file_to_image(cube->mlx, path, &img->img_width,
			&img->img_height);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->size_l, &img->endian);
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->addr[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(cube->mlx, img->img);
}

void	texture_init(t_cube *cube)
{
	int		i;
	int		tex_cnt;
	t_img	img;

	tex_cnt = 4;
	i = 0;
	cube->textures = (int **)malloc(sizeof(int *) * tex_cnt);
	if (!cube->textures)
		return ;
	while (i < tex_cnt)
	{
		cube->textures[i] = (int *)malloc(sizeof(int)
				* (cube->tex_hght * cube->tex_widt));
		if (!cube->textures[i])
			return ;
		i++;
	}
	load_image(cube, cube->textures[N], cube->tex_n, &img);
	load_image(cube, cube->textures[S], cube->tex_s, &img);
	load_image(cube, cube->textures[W], cube->tex_w, &img);
	load_image(cube, cube->textures[E], cube->tex_e, &img);
}
