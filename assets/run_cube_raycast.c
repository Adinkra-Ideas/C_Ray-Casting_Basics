/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cube_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:48:58 by juzoanya          #+#    #+#             */
/*   Updated: 2022/12/18 13:06:42 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/cub3d.h"

void	raycast_init(t_cube *cube)
{
	cube->tex_widt = 64;
	cube->tex_hght = 64;
	cube->win.x = WIN_WIDTH;
	cube->win.y = WIN_HEIGHT;
	cube->rays.move_speed = 0.1;
	cube->rays.rot_speed = 0.1;
}

//******************************************************************************
// This functionn computes the direction x or y that the player steps into	   *
// based on the x or y direction of the rays. If the ray direction has a 	   *
// negative x/y-component, step.x/y is -1, if it has a positive x/y-component, *
// step.x/y is 1. If it is 0, step.x/y value is not used. If the ray direction *
// has a negative x-component, SideDistance.x is the distance from the ray's   *
// starting point to the left, if the ray direction has a positive x-component,*
// SideDistance.x is the first side to the right. Same applies for the 		   *
// y-component but the first side is above or below the position.			   *
//******************************************************************************
void	compute_steps(t_cube *cube)
{
	if (cube->rays.ray_dir.x < 0)
	{
		cube->ply.step.x = -1;
		cube->rays.side_dist.x = (cube->ply.pos.x - cube->rays.map.x)
			* cube->rays.delta_dist.x;
	}
	else
	{
		cube->ply.step.x = 1;
		cube->rays.side_dist.x = (cube->rays.map.x + 1.0 - cube->ply.pos.x)
			* cube->rays.delta_dist.x;
	}
	if (cube->rays.ray_dir.y < 0)
	{
		cube->ply.step.y = -1;
		cube->rays.side_dist.y = (cube->ply.pos.y - cube->rays.map.y)
			* cube->rays.delta_dist.y;
	}
	else
	{
		cube->ply.step.y = 1;
		cube->rays.side_dist.y = (cube->rays.map.y + 1.0 - cube->ply.pos.y)
			* cube->rays.delta_dist.y;
	}
}

//******************************************************************************
// The Digital Differential Analyser is a loop that increaments the ray in 	   *
// x-direction (with step.x) or y-direction (with step.y) by jumping x or y    *
// square on map until it hits a wall. Side Distance gets incremented with 	   *
// every with Delta Distance on every jump. When a wall is hit, the distance of*
// the ray to the wall is calculated. This is not a real only a perpendicular  *
// distance so as to avoid a fisheye effect.								   *
//******************************************************************************
void	compute_dda(t_cube *cube)
{
	while (cube->rays.hit == 0)
	{
		if (cube->rays.side_dist.x < cube->rays.side_dist.y)
		{
			cube->rays.side_dist.x += cube->rays.delta_dist.x;
			cube->rays.map.x += cube->ply.step.x;
			cube->rays.w_side = 0;
		}
		else
		{
			cube->rays.side_dist.y += cube->rays.delta_dist.y;
			cube->rays.map.y += cube->ply.step.y;
			cube->rays.w_side = 1;
		}
		if (cube->map[cube->rays.map.x][cube->rays.map.y] == '1')
			cube->rays.hit = 1;
	}
	if (cube->rays.w_side == 0)
		cube->rays.perp_wall_dist = (cube->rays.map.x - cube->ply.pos.x
				+ (1 - cube->ply.step.x) / 2) / cube->rays.ray_dir.x;
	else
		cube->rays.perp_wall_dist = (cube->rays.map.y - cube->ply.pos.y
				+ (1 - cube->ply.step.y) / 2) / cube->rays.ray_dir.y;
}

void	raycast(t_cube *cube)
{
	int		x;
	double	camera;

	x = 0;
	while (x < cube->win.x)
	{
		cube->rays.hit = 0;
		camera = 2 * x / (double)cube->win.x - 1;
		cube->rays.ray_dir.x = cube->ply.dir.x + cube->rays.plane.x * camera;
		cube->rays.ray_dir.y = cube->ply.dir.y + cube->rays.plane.y * camera;
		cube->rays.map.x = (int)cube->ply.pos.x;
		cube->rays.map.y = (int)cube->ply.pos.y;
		cube->rays.delta_dist.x = fabs(1 / cube->rays.ray_dir.x);
		cube->rays.delta_dist.y = fabs(1 / cube->rays.ray_dir.y);
		compute_steps(cube);
		compute_dda(cube);
		select_texture(cube);
		texture_calc(cube);
		compute_ray_color(cube, x);
		x++;
	}
}
