#include "fdf.h"



int	main(int argc, char **argv)
{
	(void) argv;
	(void) argc;
	t_prog	*prog;
	t_point	p1;
	t_point	p2;
	// if (argc != 2)
	// 	exception(1, "Not enough arguments");
	prog = init_prog();
	prog->df = init_df();
	prog->df->h_view = 10;
	prog->df->h_move = 5;
	prog->df->v_move = 0;
	parse_df(prog->df, "test_maps/100-6.fdf");
	prog->df->zoom = find_max(prog->df->width / prog->df->height, 5);
	printf("%f %f\n", prog->df->zoom, prog->df->h_view);
	// adjust_map(prog->df);
	draw_loop(prog, prog->df);
	
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img, 0, 0);
	mlx_loop(prog->mlx);
	return (0);
}
