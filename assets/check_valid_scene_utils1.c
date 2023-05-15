#include "cub3d.h"

// ******************************************************
// Function to simply check if the rdata string is		*
// empty(contains no value or only space values).		*
// If the rdata string is empty, function returns TRUE,	*
// else it returns FALSE								*
// ******************************************************
int	line_is_empty(char *rdata)
{
	int	i;

	i = 0;
	while (rdata && rdata[i] && rdata[i] == ' ')
		i++;
	if (rdata && rdata[i] == '\0')
		return (1);
	return (0);
}

// ******************************************
// This function receives all the lines		*
// of the map elements from input file.		*
// each line is an array in rawdata. It		*
// then runs several validations to verify	*
// if the map characters makes up a valid	*
// input map. If yes, it returns 1, else	*
// it returns 0								*
// ******************************************
int	map_is_valid(t_cube *cube, char **rawdata)
{
	int	i;
	int	validity;
	int	*nsew;

	i = 0;
	validity = 0;
	nsew = (int []){0, 0, 0, 0};
	while (*rawdata && line_is_empty(*rawdata))
		rawdata++;
	if (rawdata[i] && valid_top_bottom_map(rawdata[i++]))
		validity += 1;
	while (rawdata[i] && valid_middle_map(rawdata[i], nsew))
		i++;
	if (rawdata[i - 1] && valid_top_bottom_map(rawdata[i - 1]))
		validity += 1;
	if (validity == 2 && i >= 3)
		validity += valid_walls(rawdata + 1, i - 2);
	while (rawdata[i] && line_is_empty(rawdata[i]))
		i++;
	if (!rawdata[i])
		validity += 1;
	if (validity != 4 && write(2, "Error\nInvalid Map\n", 18))
		return (0);
	return (copy_map(cube, rawdata));
}

// **************************************************
// Simply checks rdata value if it matches with		*
// the top and bottom line requirements for the		*
// map element.										*
// If yes, it returns TRUE, else it returns FALSE	*
// **************************************************
int	valid_top_bottom_map(char *rdata)
{
	int	i;

	i = 0;
	while (rdata && rdata[i] && (rdata[i] == ' ' || rdata[i] == '1'))
		i++;
	if (rdata && rdata[i] == '\0')
		return (1);
	return (0);
}

// **************************************************
// Simply checks rdata(param) value if it matches 	*
// the topline, bottom line, mid lines and player's	*
// NSEW requirements for the map element			*
// If yes, it returns TRUE, else it returns FALSE	*
// **************************************************
int	valid_middle_map(char *rdata, int *nsew)
{
	int	i;
	int	validity;

	i = 0;
	validity = 0;
	validity += wall_char_is_valid(rdata);
	while (rdata[i])
	{
		if (rdata[i] == ' ' || rdata[i] == '1' || rdata[i] == '0')
			i++;
		else if (rdata[i] == 'N' && ++i)
			nsew[0] += 1;
		else if (rdata[i] == 'S' && ++i)
			nsew[1] += 1;
		else if (rdata[i] == 'E' && ++i)
			nsew[2] += 1;
		else if (rdata[i] == 'W' && ++i)
			nsew[3] += 1;
		else if (rdata[i])
			return (0);
	}
	if (validity && !rdata[i] && !nsew_val_overflow(nsew))
		return (1);
	return (0);
}

// **********************************************************************
// If char '1' is found to be the first non-space char in  both the 	*
// beginning and end of S, it returns true.								*
// Else it returns false.												*
// **********************************************************************
int	wall_char_is_valid(const char *s)
{
	int	i;
	int	validity;

	i = 0;
	validity = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '1')
		validity += 1;
	i = ft_strlen((char *)s) - 1;
	if (i > 0)
	{
		while (i > 0 && s[i] != '1' && s[i] == ' ')
			i--;
	}
	if (i >= 0 && s[i] == '1' && validity)
		return (1);
	return (0);
}
