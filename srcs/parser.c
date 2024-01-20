/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:37:59 by roylee            #+#    #+#             */
/*   Updated: 2024/01/20 23:54:24 by roylee           ###   ########.fr       */
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
	}
	free(line);
	while (ft_next_line(fd, &line) > 0)
		free(line);
	if (close(fd) < 0)
		exception(1, "Failed to close file");
	ft_free_strarr(split);
	return (width);
}

static void	ft_fill_tmap(t_df *df, char *line, int y)
{
	char	**split;
	int		x;
	char	**split2;

	split = ft_split(line, ' ');
	x = -1;
	while (++x < df->width)
	{
		df->t_map->coord[y][x].x = (double)x;
		df->t_map->coord[y][x].y = (double)y;
		if (ft_strchr(split[x], ','))
		{
			split2 = ft_split(split[x], ',');
			df->t_map->coord[y][x].z = (double)ft_atoi(split2[0]);
			ft_free_strarr(split2);
		}
		else
			df->t_map->coord[y][x].z = (double)ft_atoi(split[x]);
	}
	ft_free_strarr(split);
}

void	parse_df(t_prog *prog, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = check_fdf(prog, file);
	prog->df->height = get_height(file);
	prog->df->width = get_width(file);
	prog->df->t_map->coord = init_coord(prog->df->width, prog->df->height);
	i = 0;
	while (ft_next_line(fd, &line) > 0)
	{
		ft_fill_tmap(prog->df, line, i);
		free(line);
		i++;
	}
	ft_transform_map(prog->df);
	ft_update_minmax_with_zoom(prog->df);
	close(fd);
}
