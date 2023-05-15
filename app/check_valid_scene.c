#include "../assets/cub3d.h"

// **************************************************************
// function to run initial checks on the CMD input(param 2).	*
// If the CMD input is valid, it initializes necessary			*
// values to each of the member vars of the cube object			*
// pointer(param 1) and returns 1. 								*
// Else if the CMD input is not valid, it returns false			*
// **************************************************************
int	check_valid_scene(t_cube *cube, char *argv)
{
	int		fd;
	char	**rawdata;

	fd = open(argv, O_RDONLY);
	if (fd == -1 || ft_strncmp(argv + (ft_strlen(argv) -4), ".cub", 4))
		return (0);
	rawdata = (char **)malloc(MAX_LINES * sizeof(char *));
	mem_switch(rawdata, MAX_LINES);
	if (data_from_infile(cube, rawdata, fd))
		return ((mem_switch(rawdata, 0), 1));
	return ((mem_switch(rawdata, 0), 0));
}
