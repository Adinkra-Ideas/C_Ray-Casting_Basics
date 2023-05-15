#include "cub3d.h"

// **************************************************
// This function is called from check_valid_scene()	*
// It acts as an on-off switch.						*
// When flag is TRUE, it means rawdata has been		*
// allocated memory capable of holding FLAG number	*
// of sub arrays. It simply NULLs out all the sub	*
// arrays to prevent undefined behaviour that might	*
// in case malloc returned memory area with garbage	*
// non-NULL values.									*
// But if flag is FALSE, it frees up all memory in	*
// rawdata.											*
// **************************************************
void	mem_switch(char **rawdata, int flag)
{
	int	i;

	i = flag;
	if (flag)
	{
		while (i > 0)
		{
			rawdata[i - 1] = NULL;
			i--;
		}
	}
	else
	{
		while (rawdata && rawdata[i] && (free(rawdata[i]), 1))
			i++;
		if (rawdata)
			free(rawdata);
	}
}

// **************************************************
// This function copies each line from FD to		*
// a new arraw within rawdata. Then it checks		*
// the data in rawdata to see if it is a valid scene*
// If yes, it returns TRUE, else FALSE.				*
// **************************************************
int	data_from_infile(t_cube *cube, char **rawdata, int fd)
{
	char	*tmp;
	int		i;
	int		j;

	j = 1;
	while (j > 0)
	{
		i = 0;
		tmp = (char *) malloc((MAX_CHARS + 1) * sizeof(char));
		while (j > 0)
		{
			j = read(fd, &tmp[i], 1);
			if (j <= 0 || tmp[i] == '\n' || (i >= MAX_CHARS \
				&& write(2, "Error\n Line\n", 12)))
				break ;
			if (j > 0)
				i += j;
		}
		tmp[i] = 0;
		copy_to_rawdata(rawdata, tmp);
		free(tmp);
	}
	if (scene_is_valid(cube, rawdata))
		return (1);
	return (0);
}

// **************************************************
// This function is called from copy_from_infile()	*
// It simply copies the data from tmp to the next	*
// available array in rawdata						*
// **************************************************
void	copy_to_rawdata(char **rawdata, char *tmp)
{
	int	i;

	i = 0;
	while (rawdata[i])
		i++;
	if (i >= MAX_LINES)
		write(2, "Error\n input file exceeds max expected lines\n", 45);
	else if (ft_strlen(tmp))
	{
		rawdata[i] = (char *) malloc(MAX_CHARS * sizeof(char));
		ft_strlcpy(rawdata[i], tmp, ft_strlen(tmp) + 1);
	}	
}

// **************************************************
// rawdata holds all the lines from our input file	*
// this function checks all the arrays in rawdata	*
// to see if it is a valid scene. 					*
// If valid scene, it will return 1, else 0			*
// **************************************************
int	scene_is_valid(t_cube *cube, char **rawdata)
{
	int	i;
	int	max_arr_pos;

	max_arr_pos = 0;
	i = check_for(cube->tex_n, rawdata, "NO", &max_arr_pos);
	i += check_for(cube->tex_s, rawdata, "SO", &max_arr_pos);
	i += check_for(cube->tex_w, rawdata, "WE", &max_arr_pos);
	i += check_for(cube->tex_e, rawdata, "EA", &max_arr_pos);
	i += check_for(cube->col_f, rawdata, "F", &max_arr_pos);
	i += check_for(cube->col_c, rawdata, "C", &max_arr_pos);
	if (i == 6 && no_wrong_element(rawdata, max_arr_pos) \
		&& map_is_valid(cube, rawdata + max_arr_pos + 1))
		return (1);
	return (0);
}

// **************************************************************
// This function is called from scene_is_valid()				*
// It searches each of the arrays in rawdata(param) to			*
// see which one(s) have the ptr(param) string at its			*
// beginnings. It then returns the count of arrays whose		*
// beginning chars matches with the ptr string.					*
// arr_pos(param 3) is a pointer to an int. If the array		*
// position within rawdata(param) that matches the ptr(param)	*
//  string is greater than the current value					*
// referenced by arr_pos, then the value of arr_pos gets		*
// replaced by the array position within rawdata(param)			*
// **************************************************************
int	check_for(void *dest, char **rawdata, char *ptr, int *arr_pos)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (rawdata && rawdata[i])
	{
		if (exist_in_start(rawdata[i], ptr))
		{
			flag = (int)ft_strlen(ptr);
			if (i > *arr_pos)
				*arr_pos = i;
			break ;
		}
		i++;
	}
	if ((flag == 2 && verify_path((char *)dest, rawdata[i] \
		+ exist_in_start(rawdata[i], ptr))) || (flag == 1 \
		&& verify_rgb((int *)dest, rawdata[i] \
		+ exist_in_start(rawdata[i], ptr))))
		return (1);
	return (0);
}
