/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_scene_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:04:31 by euyi              #+#    #+#             */
/*   Updated: 2022/12/05 22:20:20 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// **************************************************************
// Since we only need one player to start in position of either	*
// N || S || E || W, that means only one array element of nsew	*
// can have the value of 1, and the other three elements		*
// MUST have a value of 0. If less than three array element		*
// has a value of 0, or any of the array elements has a value	*
// greater than 1, then the nsew will overflow. Returning		*
// TRUE in that case. Else it returns false.					*
// **************************************************************
int	nsew_val_overflow(int *nsew)
{
	int	i;
	int	j;

	i = 3;
	j = 0;
	while (i >= 0)
	{
		if (nsew[i] == 0)
			j++;
		else if (nsew[i] > 1)
			return (1);
		i--;
	}
	if (j >= 3)
		return (0);
	return (1);
}

// ******************************************************************
// This function is guaranteed to receive a rawdata					*
// 2D array containing ONLY the mid-section(s) of a map 			*
// data(EXCLUDING the top and bottom wall arrays of the map).		*
// The param 2 is an int value of the max array within the rawdata	*
// arraws that we should validate.									*
// ******************************************************************
int	valid_walls(char **rawdata, int max_array)
{
	int	i;
	int	j;

	i = 0;
	while (i < max_array)
	{
		j = 0;
		while (rawdata[i][j])
		{
			if (map_chars(rawdata[i][j]) == 1 && !valid_surround(rawdata, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// **********************************************************
// Simply compares the char parameter against all the		*
// expected valid characters inside a map. 					*
// Return value is 2 if c == '1', 1 if c == 'N' || 'S'...	*
// 0 if c matches none.										*
// **********************************************************
int	map_chars(char c)
{
	char	*ptr;

	ptr = "NSWE01\0";
	while (*ptr)
	{
		if (*ptr == '1' && *ptr == c)
			return (2);
		else if (*ptr == c)
			return (1);
		ptr++;
	}
	return (0);
}

// **********************************************************************
// At anytime this function is called, we are guaranteed that			*
// rawdata[i] will never be the first or last array within **rawdata,	*
// rawdata[i][j] is a char that matches any char in "NSEW0",			*
// and rawdata[i][j] will not be the arr[0] or arr[last_ele_b4_null]	*
// array char element within the rawdata[i] array.						*
// **********************************************************************
int	valid_surround(char **rawdata, int i, int j)
{
	char	*pre;
	char	*post;
	char	*rdata;

	pre = rawdata[i - 1];
	rdata = rawdata[i];
	post = rawdata[i + 1];
	if (!map_chars(pre[j - 1]) || !map_chars(pre[j]) || !map_chars(pre[j + 1])
		|| !map_chars(rdata[j - 1]) || !map_chars(rdata[j + 1])
		|| !map_chars(post[j - 1]) || !map_chars(post[j])
		|| !map_chars(post[j + 1]))
		return (0);
	return (1);
}

// **********************************************
// Copies map element from rawdata to cube->map	*
// **********************************************
int	copy_map(t_cube *cube, char **rawdata)
{
	int	i;

	i = 0;
	cube->map = (char **) malloc(MAX_LINES * sizeof(char *));
	mem_switch(cube->map, MAX_LINES);
	while (rawdata[i] && !line_is_empty(rawdata[i]))
	{
		if (ft_strlen(rawdata[i]) + 1 >= MAX_CHARS)
		{
			mem_switch(cube->map, 0);
			write(2, "Error\nA Line Exceeds Limit\n", 27);
			return (0);
		}
		cube->map[i] = (char *) malloc(MAX_CHARS * sizeof(char));
		ft_strlcpy(cube->map[i], rawdata[i], ft_strlen(rawdata[i]) + 1);
		i++;
	}
	return (1);
}
