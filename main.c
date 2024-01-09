#include "fdf.h"

int	main(int argc, char **argv)
{
	(void) argv;
	t_prog	*prog;

	if (argc != 2)
		exception(1, "Not enough arguments");
	prog = init_prog();
	prog->df = init_df(argv[1]);
	parse_df(prog->df, argv[1]);
	printf("Good");
}
