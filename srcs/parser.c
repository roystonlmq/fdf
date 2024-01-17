/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:37:59 by roylee            #+#    #+#             */
/*   Updated: 2024/01/17 22:15:34 by roylee           ###   ########.fr       */
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

void	map_init(t_df *df)
{
	df->t_map = (t_map *)malloc(sizeof(t_map));
	if (!df->t_map)
		exception(1, "Failed to allocate memory for map");
	df->t_map->coord = NULL;
	df->t_map->max_x = 0;
	df->t_map->max_y = 0;
	df->t_map->min_x = 0;
	df->t_map->min_y = 0;
}

t_point	**init_coord(int width, int height)
{
	t_point	**coords;
	int		i;
	int		j;

	coords = (t_point **)malloc(sizeof(t_point *) * height);
	if (!coords)
		exception(1, "Failed to allocate memory for coords");
	i = 0;
	while (i < width)
	{
		coords[i] = malloc(height * sizeof(t_point));
		if (!coords[i])
			exception(1, "Failed to allocate memory for coords");
		j = 0;
		while (j < height)
		{
			coords[i][j].x = 0;
			coords[i][j].y = 0;
			coords[i][j].z = 0;
			j++;
		}
		i++;
	}
	return (coords);
}
/*
ft_fill_map will first split the line with ' ' and then
check if the split str contains ',', if it does, it will
split the str again with ',' and then convert the str to
int and store it in the map.
*/
static void	ft_fill_map(t_df *df, char *line, int i)
{
	char	**split;
	int		j;
	char	**split2;
	t_point	p;
	
	split = ft_split(line, ' ');
	j = -1;
	while (++j < df->width)
	{
		if (ft_strchr(split[j], ','))
		{
			split2 = ft_split(split[j], ',');
			p.x = j;
			p.y = i;
			p.z = ft_atoi(split2[0]);
			df->map[i][j] = ft_atoi(split2[0]);
			ft_free_strarr(split2);
		}
		else
			df->map[i][j] = ft_atoi(split[j]);
	}
	ft_free_strarr(split);
}

static void	update_minmax(t_df *df, int j, int i)
{
	if (df->t_map->coord[j][i].x > df->t_map->max_x)
		df->t_map->max_x = df->t_map->coord[j][i].x;
	if (df->t_map->coord[j][i].y > df->t_map->max_y)
		df->t_map->max_y = df->t_map->coord[j][i].y;
	if (df->t_map->coord[j][i].x < df->t_map->min_x)
		df->t_map->min_x = df->t_map->coord[j][i].x;
	if (df->t_map->coord[j][i].y < df->t_map->min_y)
		df->t_map->min_y = df->t_map->coord[j][i].y;
}

static void	ft_fill_tmap(t_df *df, char *line, int j)
{
	char	**split;
	int		i;
	char	**split2;
	
	split = ft_split(line, ' ');
	i = -1;
	while (++i < df->width)
	{
		df->t_map->coord[j][i].x = (double)i;
		df->t_map->coord[j][i].y = (double)j;
		update_minmax(df, j, i);
		if (ft_strchr(split[i], ','))
		{
			split2 = ft_split(split[i], ',');
			df->t_map->coord[j][i].z = (double)ft_atoi(split2[0]);
			ft_free_strarr(split2);
		}
		else
			df->t_map->coord[j][i].z = (double)ft_atoi(split[i]);
	}
	ft_free_strarr(split);
}

void	parse_df(t_df *df, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY, 0777);
	if (fd < 0)
		exception(1, "Failed to open file");
	df->height = get_height(file);
	df->width = get_width(file);
	df->t_map->coord = init_coord(df->width, df->height);
	df->map = malloc_map(df);
	i = 0;
	while (ft_next_line(fd, &line) > 0)
	{
		ft_fill_map(df, line, i);
		ft_fill_tmap(df, line, i);
		i++;
	}
	// ft_transform_map(df);
	close(fd);
}
