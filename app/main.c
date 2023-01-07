/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:14:57 by euyi              #+#    #+#             */
/*   Updated: 2022/12/13 13:25:14 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/cub3d.h"

int	main(int argc, char *argv[])
{
	t_cube	cube;

	if (argc != 2 || !check_valid_scene(&cube, argv[1]))
		return (write(2, "Error\nCheck Input\n", 18));
	run_cube(&cube);
	return (0);
}
