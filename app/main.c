
#include "../assets/cub3d.h"

int	main(int argc, char *argv[])
{
	t_cube	cube;

	if (argc != 2 || !check_valid_scene(&cube, argv[1]))
		return (write(2, "Error\nCheck Input\n", 18));
	run_cube(&cube);
	return (0);
}
