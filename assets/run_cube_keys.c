/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cube_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:45:28 by juzoanya          #+#    #+#             */
/*   Updated: 2022/12/18 15:57:55 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/cub3d.h"

void	move_player_y(t_cube *cube, char *str)
{
	if ((ft_strncmp(str, "FORWARD", ft_strlen(str))) == 0)
	{
		if (cube->map[(int)(cube->ply.pos.x + cube->ply.dir.x \
			* cube->rays.move_speed)][(int)(cube->ply.pos.y)] != '1')
			cube->ply.pos.x += cube->ply.dir.x * cube->rays.move_speed;
		if (cube->map[(int)(cube->ply.pos.x)][(int)(cube->ply.pos.y \
			+ cube->ply.dir.y * cube->rays.move_speed)] != '1')
			cube->ply.pos.y += cube->ply.dir.y * cube->rays.move_speed;
	}
	if ((ft_strncmp(str, "BACKWARD", ft_strlen(str))) == 0)
	{
		if (cube->map[(int)(cube->ply.pos.x - cube->ply.dir.x \
			* cube->rays.move_speed)][(int)(cube->ply.pos.y)] != '1')
			cube->ply.pos.x -= cube->ply.dir.x * cube->rays.move_speed;
		if (cube->map[(int)(cube->ply.pos.x)][(int)(cube->ply.pos.y \
			- cube->ply.dir.y * cube->rays.move_speed)] != '1')
			cube->ply.pos.y -= cube->ply.dir.y * cube->rays.move_speed;
	}
}

void	move_player_x(t_cube *cube, char *str)
{
	if ((ft_strncmp(str, "LEFT", ft_strlen(str))) == 0)
	{
		if (cube->map[(int)(cube->ply.pos.x - cube->rays.plane.x \
			* cube->rays.move_speed)][(int)(cube->ply.pos.y)] != '1')
			cube->ply.pos.x -= cube->rays.plane.x * cube->rays.move_speed;
		if (cube->map[(int)(cube->ply.pos.x)][(int)(cube->ply.pos.y \
			- cube->rays.plane.y * cube->rays.move_speed)] != '1')
			cube->ply.pos.y -= cube->rays.plane.y * cube->rays.move_speed;
	}
	if ((ft_strncmp(str, "RIGHT", ft_strlen(str))) == 0)
	{
		if (cube->map[(int)(cube->ply.pos.x + cube->rays.plane.x \
			* cube->rays.move_speed)][(int)(cube->ply.pos.y)] != '1')
			cube->ply.pos.x += cube->rays.plane.x * cube->rays.move_speed;
		if (cube->map[(int)(cube->ply.pos.x)][(int)(cube->ply.pos.y \
			+ cube->rays.plane.y * cube->rays.move_speed)] != '1')
			cube->ply.pos.y += cube->rays.plane.y * cube->rays.move_speed;
	}
}

void	rotate_left(t_cube *cube)
{
	cube->ply.old_dir.x = cube->ply.dir.x;
	cube->rays.old_plane.x = cube->rays.plane.x;
	cube->ply.dir.x = cube->ply.dir.x * cos(cube->rays.rot_speed)
		- cube->ply.dir.y * sin(cube->rays.rot_speed);
	cube->ply.dir.y = cube->ply.old_dir.x * sin(cube->rays.rot_speed)
		+ cube->ply.dir.y * cos(cube->rays.rot_speed);
	cube->rays.plane.x = cube->rays.plane.x * cos(cube->rays.rot_speed)
		- cube->rays.plane.y * sin(cube->rays.rot_speed);
	cube->rays.plane.y = cube->rays.old_plane.x * sin(cube->rays.rot_speed)
		+ cube->rays.plane.y * cos(cube->rays.rot_speed);
}

void	rotate_view(t_cube *cube, char *str)
{
	if ((ft_strncmp(str, "RIGHT", ft_strlen(str))) == 0)
	{
		cube->ply.old_dir.x = cube->ply.dir.x;
		cube->rays.old_plane.x = cube->rays.plane.x;
		cube->ply.dir.x = cube->ply.dir.x * cos(-cube->rays.rot_speed)
			- cube->ply.dir.y * sin(-cube->rays.rot_speed);
		cube->ply.dir.y = (cube->ply.old_dir.x * sin(-cube->rays.rot_speed))
			+ (cube->ply.dir.y * cos(-cube->rays.rot_speed));
		cube->rays.plane.x = cube->rays.plane.x * cos(-cube->rays.rot_speed)
			- cube->rays.plane.y * sin(-cube->rays.rot_speed);
		cube->rays.plane.y = cube->rays.old_plane.x * sin(-cube->rays.rot_speed)
			+ cube->rays.plane.y * cos(-cube->rays.rot_speed);
	}
	else if ((ft_strncmp(str, "LEFT", ft_strlen(str))) == 0)
		rotate_left(cube);
}

int	key_press(int key, t_cube *cube)
{
	if (key == 119 || key == 119 - 32)
		move_player_y(cube, "FORWARD");
	if (key == 115 || key == 115 - 32)
		move_player_y(cube, "BACKWARD");
	if (key == 97 || key == 65)
		move_player_x(cube, "LEFT");
	if (key == 100 || key == 68)
		move_player_x(cube, "RIGHT");
	if (key == 65361 && (cube->ply.orient == 'E' || cube->ply.orient == 'W'))
		rotate_view(cube, "RIGHT");
	else if (key == 65361)
		rotate_view(cube, "LEFT");
	if (key == 65363 && (cube->ply.orient == 'E' || cube->ply.orient == 'W'))
		rotate_view(cube, "LEFT");
	else if (key == 65363)
		rotate_view(cube, "RIGHT");
	if (key == 65307)
		close_cube(cube);
	mlx_clear_window(cube->mlx, cube->window);
	main_loop(cube);
	return (0);
}
