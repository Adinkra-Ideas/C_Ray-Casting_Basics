
#include "cub3d.h"

int	main_loop(t_cube *cube)
{
	render_bg(cube);
	raycast(cube);
	render_minimap(cube);
	render_window(cube);
	return (0);
}
