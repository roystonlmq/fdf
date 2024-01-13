#include "fdf.h"

int	main(int argc, char **argv)
{
	(void) argv;
	(void) argc;
	t_prog	*prog;

	// if (argc != 2)
	// 	exception(1, "Not enough arguments");
	prog = init_prog();
	prog->df = init_df();
	parse_df(prog->df, "test_maps/42.fdf");
	draw(prog->df, prog);
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->mlx_img, 0, 0);
	mlx_loop(prog->mlx_ptr);
	return (0);
}
