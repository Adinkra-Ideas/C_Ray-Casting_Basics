/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:14:11 by juzoanya          #+#    #+#             */
/*   Updated: 2022/12/18 15:58:17 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/cub3d.h"

void	run_cube(t_cube *cube)
{	
	cube->mlx = mlx_init();
	if (!cube->mlx)
		printf("MLX initialization failed!\n");
	orientation_init(cube);
	raycast_init(cube);
	texture_init(cube);
	cube->window = mlx_new_window(cube->mlx, cube->win.x, cube->win.y, "Cub3D");
	if (!cube->window)
		printf("Window initialization failed!\n");
	cube->img.img = mlx_new_image(cube->mlx, cube->win.x, cube->win.y);
	if (!cube->img.img)
		printf("Image initialization failed!\n");
	cube->img.addr = (int *)mlx_get_data_addr(cube->img.img, &cube->img.bpp,
			&cube->img.size_l, &cube->img.endian);
	mlx_loop_hook(cube->mlx, &main_loop, cube);
	mlx_hook(cube->window, 2, 1L << 0, &key_press, cube);
	mlx_hook(cube->window, 17, 0L, close_cube, cube);
	mlx_loop(cube->mlx);
}
