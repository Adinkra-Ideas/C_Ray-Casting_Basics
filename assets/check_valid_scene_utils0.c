/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_scene_utils0.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:05:09 by euyi              #+#    #+#             */
/*   Updated: 2022/12/05 22:10:13 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ******************************************************************
// This function is called from check_for()							*
// It skips through the space characters(if any) at the beginning	*
// of the string param, then checks non-space chars at the beginning*
// of the string to see if they are exactly the same as word param.	*
// return value is array position count of word parm if matched.	*
// If no match, it returns FALSE									*
// ******************************************************************
int	exist_in_start(char *string, char *word)
{
	int	i;

	i = 0;
	while (string && string[i])
	{
		if (string[i] == ' ')
			i++;
		else if (!ft_strncmp(string + i, word, ft_strlen(word)))
			return (i + ft_strlen(word));
		else
			break ;
	}
	return (0);
}

// **************************************************************
// rdata simply receives a pointer to the index point			*
// of a string that exist immediately after NO,SO,EA or WE		*
// chars. Then it checks if the string in rdata is a valid path.*
// Return value is TRUE if path is valid, else it returns 0		*
// **************************************************************
int	verify_path(char *txt, const char *rdata)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (rdata[i] && rdata[i] == ' ')
		i++;
	while (rdata[i] && rdata[i] != ' ')
	{
		if (j == PATH_LEN && write(2, "Error\nLL Texture Path\n", 22))
			return (0);
		txt[j] = rdata[i];
		j++;
		i++;
	}
	txt[j] = 0;
	j = open(txt, O_RDONLY);
	if (j < 0 && write(2, "Error\nCheck Texture Path(s)\n", 28))
		return (0);
	return (1);
}

// **************************************************************
// rdata simply receives a pointer to the index point			*
// of a string that exist immediately after NO,SO,EA or WE		*
// chars. 
// *word is guaranteed to either be 'F' or 'C'.
// The function checks if the string in rdata is a valid RGB	*
// color representation.
// Return value is TRUE if RGB is valid, else it returns 0		*
// **************************************************************
int	verify_rgb(int *color, const char *rdata)
{
	int		j;
	int		i;

	j = 0;
	while (j < 3)
	{
		i = next_dec_point(rdata);
		if (i == -1 && write(2, "Error\nCheck F or C RGB\n", 23))
			return (0);
		else
			i = ft_atoi(rdata);
		if ((i < 0 || i > 255) && write(2, "Error\nInvalid RGB\n", 18))
			return (0);
		while (*rdata && *rdata != ',')
			rdata++;
		if (*rdata && *rdata == ',')
			rdata++;
		color[j] = i;
		j++;
	}
	return (1);
}

// ******************************************************
// returns the array position of the first decimal char	*
// found in rdata. If no decimal char found, it returns	*
// -1													*
// ******************************************************
int	next_dec_point(const char *rdata)
{
	int	i;

	i = 0;
	while (rdata[i] && (rdata[i] < 48 || rdata[i] > 57))
		i++;
	if (rdata[i] > 47 && rdata[i] < 58)
		return (i);
	return (-1);
}

// **********************************************************
// This function loops through rawdata 2D array from		*
// rawdata[0] up to rawdata[max_arr_pos], counting the		*
// number of empty lines. Then it subtracts the empty line	*
// count from max_arr_pos to see if it == 5.				*
// If yes, it returns TRUE, else returns FALSE.				*
// Note that 5 means array[5] because the NO,SO,EA,WE,F,C	*
// value are supposed to occupy rawdata[0] to rawdata[5]	*
// with only empty spaces allowed in between lines.			*
// Therefore this is supposed to check for garbage values	*
// in the input file.										*
// **********************************************************
int	no_wrong_element(char **rawdata, int arr_pos)
{
	int	i;
	int	empty_lines;

	i = 0;
	empty_lines = 0;
	while (rawdata && rawdata[i] && (i <= arr_pos))
	{
		if (line_is_empty(rawdata[i]))
			empty_lines++;
		i++;
	}
	if ((arr_pos - empty_lines) == 5)
		return (1);
	return (0);
}
