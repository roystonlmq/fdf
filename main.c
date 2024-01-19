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
	parse_df(prog->df, "test_maps/elem-col.fdf");
	// prog->df->zoom = find_min(WIN_WIDTH / (prog->df->t_map->max_x / 2),
	// (WIN_HEIGHT / prog->df->t_map->max_y / 2)); // copied to parser, so it'll be done after finding min_x, etc.
	//prog->df->zoom = 2; // comment out if not using normal fill map
	// printf("%f", prog->df->zoom);
	// if (prog->df->zoom < 4)
	// 	prog->df->zoom = 2;
	// else
	// 	prog->df->zoom /= 2;
	// adjust_map(prog->df);
	draw_loop(prog, prog->df);
	printf("min x: %f min y: %f max x: %f max y: %f \n", 
	prog->df->t_map->min_x, prog->df->t_map->min_y, prog->df->t_map->max_x,
	prog->df->t_map->max_y);
	// printf("%f %f\n", prog->df->zoom, prog->df->h_view);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img, 0, 0);
	mlx_loop(prog->mlx);
	return (0);
}
