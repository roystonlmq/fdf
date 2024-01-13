/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:37:59 by roylee            #+#    #+#             */
/*   Updated: 2024/01/13 11:29:03 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_height(char *file)
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

static int	get_width(char *file)
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

static int	**malloc_map(t_df *df)
{
	int		**map;
	int		i;

	map = (int **)malloc(sizeof(int *) * df->height);
	i = -1;
	while (i++ < df->height)
		map[i] = (int *)malloc(sizeof(int) * df->width);
	return (map);
}

void	parse_df(t_df *df, char *file)
{
	int		fd;
	char	*line;
	char	**split;
	int		i;
	int		j;

	fd = open(file, O_RDONLY, 0777);
	if (fd < 0)
		exception(1, "Failed to open file");
	df->height = get_height(file);
	df->width = get_width(file);
	df->map = malloc_map(df);
	i = -1;
	while (ft_next_line(fd, &line) > 0)
	{
		split = ft_split(line, ' ');
		j = -1;
		while (j++ < df->width)
			df->map[i][j] = ft_atoi(split[j]);
		i++;
		free(line);
		ft_free_strarr(split);
	}
	close(fd);
}
