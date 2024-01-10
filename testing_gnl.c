#include "fdf.h"

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