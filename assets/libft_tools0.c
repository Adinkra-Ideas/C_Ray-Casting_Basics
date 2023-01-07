/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:55:31 by euyi              #+#    #+#             */
/*   Updated: 2022/12/13 13:55:48 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_intcol(int a, int b)
{
	if (b == 0)
		a *= 10;
	else if (b < 10)
		a = (a * 10) + b;
	else if (b < 100)
		a = (a * 100) + b;
	else if (b < 1000)
		a = (a * 1000) + b;
	else if (b < 10000)
		a = (a * 10000) + b;
	else if (b < 100000)
		a = (a * 100000) + b;
	else if (b < 1000000)
		a = (a * 1000000) + b;
	else if (b < 10000000)
		a = (a * 10000000) + b;
	else if (b < 100000000)
		a = (a * 100000000) + b;
	else if (b < 1000000000)
		a = (a * 1000000000) + b;
	else if (b < 2147483647)
		a = (a * 1000000000) + b;
	return (a);
}

int	ft_atoi(const char *nptr)
{
	int	bank;
	int	flag;

	bank = 0;
	flag = 0;
	while ((*nptr >= 9 && *nptr <= 13) || (*nptr == 32))
		nptr++;
	if (*nptr == 45 || *nptr == 43)
	{
		if (*nptr == 45)
			flag = 1;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		bank = ft_intcol(bank, *nptr - '0');
		nptr++;
	}
	if (flag == 1 && bank > 0)
		return (bank - (bank + bank));
	return (bank);
}
