/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cube_utils0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:10:30 by euyi              #+#    #+#             */
/*   Updated: 2022/12/13 14:13:05 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_cube *cube)
{
	render_bg(cube);
	raycast(cube);
	render_minimap(cube);
	render_window(cube);
	return (0);
}
