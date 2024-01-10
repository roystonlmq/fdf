/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:37:59 by roylee            #+#    #+#             */
/*   Updated: 2024/01/10 21:24:03 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static int	ft_get_height(char *file)
{
	int		fd;
	char	*line;
	int		height;

	height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exception(1, "Failed to open file");
	while (ft_next_line(fd, &line) > 0)
	{
		height++;
		free(line);
	}	
	if (close(fd) < 0)
		exception(1, "Failed to close file");
	return (height);
}

static int	ft_get_width(char *file)
{
	int		fd;
	char	*line;
	char	**split;
	int		width;

	width = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exception(1, "Failed to open file");
	if (ft_next_line(fd, &line) > 0)
	{
		split = ft_split(line, ' ');
		width = ft_splitlen(split);
		free(line);
	}
	if (close(fd) < 0)
		exception(1, "Failed to close file");
	return (width);
}

void	parse_df(t_df *df, char *file)
{
	int		fd;
	char	*line;
	char	**split;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exception(1, "Failed to open file");
	df->height = ft_get_height(file);
	df->width = ft_get_width(file);
	
	close(fd);
}