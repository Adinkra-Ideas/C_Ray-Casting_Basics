
#ifndef CUB3D_H
# define CUB3D_H

# define PATH_LEN	1000
# define MAX_LINES	10000
# define MAX_CHARS	10000

# define WIN_WIDTH	1080
# define WIN_HEIGHT	600

# define MMAP_WAL	0x0
# define MMAP_PLY	0x0000ff
# define MMAP_NUL	0xececec

# define ERR_INIT "mlx_init Error!\n"
# define ERR_NW "mlx_new_window initialization failed!\n"

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# ifdef __linux__
#  define OS_LINUX 1
#  include "./gcamerli/linux/mlx.h"
# elif __APPLE__
#  define OS_LINUX 0
#  include "./gcamerli/mlx.h"
# endif

enum e_texture
{
	N = 0,
	S,
	W,
	E
};

typedef struct s_vect
{
	double	x;
	double	y;
}				t_vect;

typedef struct s_axis
{
	int	x;
	int	y;
}				t_axis;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_player
{
	char	orient;
	t_vect	pos;
	t_axis	step;
	t_vect	dir;
	t_vect	old_dir;
}				t_player;

typedef struct s_rays
{
	int		w_side;
	int		hit;
	t_vect	plane;
	t_vect	old_plane;
	t_vect	ray_dir;
	t_vect	side_dist;
	t_vect	delta_dist;
	t_axis	map;
	double	perp_wall_dist;
	double	line_height;
	int		draw_start;
	int		draw_end;
	t_axis	tex;
	double	tex_pos;
	double	wall_x;
	double	step;
	double	move_speed;
	double	rot_speed;
}				t_rays;

typedef struct s_cube
{
	void		*mlx;
	void		*window;
	char		tex_n[PATH_LEN];
	char		tex_s[PATH_LEN];
	char		tex_w[PATH_LEN];
	char		tex_e[PATH_LEN];
	int			col_f[4];
	int			col_c[4];
	int			tex_index;
	t_axis		win;
	t_img		img;
	int			tex_widt;
	int			tex_hght;
	t_player	ply;
	t_rays		rays;
	char		**map;
	int			buf[WIN_HEIGHT][WIN_WIDTH];
	int			**textures;
}				t_cube;

// libft functions in libft_tools.c file
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
int		ft_atoi(const char *nptr);
int		ft_strstrchr(char *str, char *find);

// check_valid_scene.c, check_valid_scene_utils.c, check_valid_scene_utils_X.c
int		check_valid_scene(t_cube *cube, char *argv);
int		check_for(void *dest, char **rawdata, char *ptr, int *arr_pos);
int		verify_path(char *txt, const char *rdata);
int		verify_rgb(int *color, const char *rdata);
int		copy_map(t_cube *cube, char **rawdata);

int		line_is_empty(char *rdata);
int		exist_in_start(char *string, char *word);
void	copy_to_rawdata(char **rawdata, char *tmp);
void	mem_switch(char **rawdata, int flag);
int		valid_middle_map(char *rdata, int *nsew);
int		nsew_val_overflow(int *nsew);
int		wall_char_is_valid(const char *s);
int		no_wrong_element(char **rawdata, int arr_pos);
int		valid_top_bottom_map(char *rdata);
int		next_dec_point(const char *rdata);
int		valid_walls(char **rawdata, int max_array);
int		valid_surround(char **rawdata, int i, int j);
int		map_chars(char c);
int		map_is_valid(t_cube *cube, char **rawdata);
int		scene_is_valid(t_cube *cube, char **rawdata);
int		data_from_infile(t_cube *cube, char **rawdata, int fd);

// All run_cube_X files
void	run_cube(t_cube *cube);
void	orientation_init(t_cube *cube);
void	raycast_init(t_cube *cube);
void	raycast(t_cube *cube);
void	texture_init(t_cube *cube);
void	preset_init(t_cube *cube);
void	preset_init_0(t_cube *cube);
void	load_texture(t_cube *cube);
void	load_image(t_cube *cube, int *texture, char *path, t_img *img);
size_t	rgb_to_hex(int *rgb);
int		main_loop(t_cube *cube);
int		close_cube(t_cube *cube);
void	render_minimap(t_cube *cube);
int		key_press(int key, t_cube *cube);
void	calc(t_cube *cube);
void	draw(t_cube *cube);
void	compute_ray_color(t_cube *cube, int x);
void	texture_calc(t_cube *cube);
void	select_texture(t_cube *cube);
void	render_bg(t_cube *cube);
void	render_window(t_cube *cube);
void	free_texture(t_cube *cube);
void	destroy_map(t_cube *cube);

#endif
