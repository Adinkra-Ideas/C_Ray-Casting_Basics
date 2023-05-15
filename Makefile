
UNAME := $(shell uname -s)

NAME = cast_rays

SRC = 	app/main.c	app/check_valid_scene.c	app/run_cube.c	\
		assets/check_valid_scene_utils.c	assets/check_valid_scene_utils0.c	\
		assets/check_valid_scene_utils1.c	assets/check_valid_scene_utils2.c	\
		assets/libft_tools.c	assets/libft_tools0.c	\
		assets/run_cube_utils.c	assets/run_cube_utils0.c	\
		assets/run_cube_keys.c	assets/run_cube_raycast.c	assets/run_cube_texture.c	\
		assets/run_cube_render.c	assets/run_cube_minimap.c	\

ifeq ($(UNAME),Linux)
	SRC += assets/close_linux.c
else
	SRC += assets/close_macos.c
endif

OBJ = $(subst .c,.o,$(SRC))

CFLAGS = -Wall	-Werror	-Wextra -ggdb3

VAL			:= valgrind
VAL_FLAGS	:= --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes --log-file=valgrind-out.txt

ARGS =	./forTestingPurpose/test.cub

all: $(NAME)

$(NAME):	$(OBJ)
ifeq ($(UNAME),Linux)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) assets/gcamerli/libmlx.a -L /usr/include/X11/extensions -lX11 -lXext -lm
else
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) assets/gcamerli/libmlx.a -L -lmlx -framework OpenGL -framework AppKit -lm
endif

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

memcheck:	clean all
	clear
	$(VAL) $(VAL_FLAGS) ./$(NAME) $(ARGS)

norm:
	@norminette $(SRC) assets/cub3d.h

.PHONY:	all	clean	fclean	re
