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
	prog->df->h_move = WIN_WIDTH / 2;
	parse_df(prog->df, "test_maps/plat.fdf");
	
	prog->df->zoom = find_min(WIN_WIDTH / prog->df->t_map->max_x 
	/ 2, WIN_HEIGHT / prog->df->t_map->max_y / 2);
	prog->df->v_move = prog->df->t_map->max_y * prog->df->zoom / 2;
	printf("%f %f\n", prog->df->zoom, prog->df->h_view);
	// adjust_map(prog->df);
	draw_loop(prog, prog->df);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img, 0, 0);
	mlx_loop(prog->mlx);
	return (0);
}
