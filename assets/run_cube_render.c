
#include "../assets/cub3d.h"

void	render_window(t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y < cube->win.y)
	{
		x = 0;
		while (x < cube->win.x)
		{
			cube->img.addr[y * cube->win.x + x] = cube->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cube->mlx, cube->window, cube->img.img, 0, 0);
}

//******************************************************************************
// This function puts color value to the pixel array. Ceiling colour is passed *
// up to half the the window, and the lower windows half recieves the Floor	   *
// colour.																	   *
//******************************************************************************
void	render_bg(t_cube *cube)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cube->win.y / 2)
	{
		j = -1;
		while (++j < cube->win.x)
			cube->buf[i][j] = rgb_to_hex(cube->col_c);
	}
	while (++i < cube->win.y)
	{
		j = -1;
		while (++j < cube->win.x)
			cube->buf[i][j] = rgb_to_hex(cube->col_f);
	}
}

void	select_texture(t_cube *cube)
{
	if (cube->rays.w_side == 0)
	{
		if (cube->rays.ray_dir.x < 0)
			cube->tex_index = N;
		else
			cube->tex_index = S;
	}
	else
	{
		if (cube->rays.ray_dir.y < 0)
			cube->tex_index = W;
		else
			cube->tex_index = E;
	}
}

//******************************************************************************
// This function performs texture calculations. First it calculates the height *
// of the line that has to be drawn on the screen. Wall_x represents the exact *
// value where the ray hits the wall this is needed to compute the x-coordinate*
// of the texture we have to use. If the wall side is 1, it is the y-cordinate *
// of the wall but always the x-coordinate of the texture. This value of 	   *
// Wall_x is then used to calculate the x-cordinate of the texture.			   *
//******************************************************************************
void	texture_calc(t_cube *cube)
{
	cube->rays.line_height = (int)(cube->win.y / cube->rays.perp_wall_dist);
	if (cube->rays.w_side == 0)
		cube->rays.wall_x = cube->ply.pos.y + cube->rays.perp_wall_dist
			* cube->rays.ray_dir.y;
	else
		cube->rays.wall_x = cube->ply.pos.x + cube->rays.perp_wall_dist
			* cube->rays.ray_dir.x;
	cube->rays.wall_x -= floor(cube->rays.wall_x);
	cube->rays.tex.x = (int)(cube->rays.wall_x * (double)cube->tex_widt);
	if (cube->rays.w_side == 0 && cube->rays.ray_dir.x > 0)
		cube->rays.tex.x = cube->tex_widt - cube->rays.tex.x - 1;
	if (cube->rays.w_side == 1 && cube->rays.ray_dir.y < 0)
		cube->rays.tex.x = cube->tex_widt - cube->rays.tex.x - 1;
	cube->rays.step = 1.0 * cube->tex_hght / cube->rays.line_height;
}

//******************************************************************************
// This function.... Using the Line Height earlier computed, The start and end *
// position of the vertical line to be drawn on screen is calculated. The 	   *
// center of the wall is the center of the screen. If point lay outside the    *
// screen, they are referenced as 0 or height - 1. Having obtained the 		   *
// x-coordinate of the texture, we loop through the y-coordinate to give each  *
// pixel of the vertical stripe the correct y-coordinate of the texture (Tex.y)*
// knowing that the x-coordinate will remain the same. The color of pixel to be*
// drawn is obtained from the conbination of the tex_index, tex.x, tex.y. Pixel*
// is parsed to the relevant pixel array location.							   *
//******************************************************************************
void	compute_ray_color(t_cube *cube, int x)
{
	int	y;
	int	color;

	cube->rays.draw_start = -cube->rays.line_height / 2 + cube->win.y / 2;
	if (cube->rays.draw_start < 0)
		cube->rays.draw_start = 0;
	cube->rays.draw_end = cube->rays.line_height / 2 + cube->win.y / 2;
	if (cube->rays.draw_end >= cube->win.y)
		cube->rays.draw_end = cube->win.y - 1;
	cube->rays.tex_pos = (cube->rays.draw_start - cube->win.y / 2
			+ cube->rays.line_height / 2) * cube->rays.step;
	y = cube->rays.draw_start;
	while (y < cube->rays.draw_end)
	{
		cube->rays.tex.y = (int)cube->rays.tex_pos & (cube->tex_hght - 1);
		cube->rays.tex_pos += cube->rays.step;
		color = cube->textures[cube->tex_index][cube->tex_hght
			* cube->rays.tex.y + cube->rays.tex.x];
		cube->buf[y][x] = color;
		y++;
	}
}
