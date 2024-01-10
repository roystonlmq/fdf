#include "fdf.h"

// int	main(int argc, char **argv)
// {
// 	(void) argv;
// 	t_prog	*prog;

// 	if (argc != 2)
// 		exception(1, "Not enough arguments");
// 	prog = init_prog();
// 	prog->df = init_df(argv[1]);
// 	parse_df(prog->df, argv[1]);
// 	printf("Good");
// }



int	main(void)
{
	int		fd;
	// int		i = 0;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	
	if (fd < 0)
		exception(1, "Failed to open file");
	line = 0;
	
	while (ft_next_line(fd, &line) > 0)
	{
		
		printf("%s\n", line);
		free(line)
	}

}