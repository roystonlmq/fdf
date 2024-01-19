/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:37:59 by roylee            #+#    #+#             */
/*   Updated: 2024/01/20 01:08:16 by roylee           ###   ########.fr       */
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
	
	split = ft_split(line, ' ');
	j = -1;
	while (++j < df->width)
	{
		if (ft_strchr(split[j], ','))
		{
			split2 = ft_split(split[j], ',');
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
	// printf("x: %f y: %f \n", df->t_map->coord[j][i].x, df->t_map->coord[j][i].y);
	// printf("current\n");
	// printf("min x: %f min y: %f max x: %f max y: %f \n", df->t_map->min_x, df->t_map->min_y, df->t_map->max_x, df->t_map->max_y);
	// if (df->t_map->coord[j][i].x < 0)
		// printf("found x < 0, x is %f \n", df->t_map->coord[j][i].x);
	if (df->t_map->coord[j][i].x > df->t_map->max_x)
		df->t_map->max_x = df->t_map->coord[j][i].x;
	if (df->t_map->coord[j][i].y > df->t_map->max_y)
		df->t_map->max_y = df->t_map->coord[j][i].y;
	if (df->t_map->coord[j][i].x < df->t_map->min_x)
		df->t_map->min_x = df->t_map->coord[j][i].x;
	if (df->t_map->coord[j][i].y < df->t_map->min_y)
		df->t_map->min_y = df->t_map->coord[j][i].y;
	// printf("after\n");
	// printf("min x: %f min y: %f max x: %f max y: %f \n", df->t_map->min_x, df->t_map->min_y, df->t_map->max_x, df->t_map->max_y);
	// printf("\n");
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
		if (df->t_map->coord[y][x].x < 0)
			printf("while filling tmap, i found x < 0, x is %f \n", df->t_map->coord[y][x].x);
		df->t_map->coord[y][x].y = (double)y;
		if (ft_strchr(split[x], ','))
		{
			split2 = ft_split(split[x], ',');
			df->t_map->coord[y][x].z = (double)ft_atoi(split2[0]);
			ft_free_strarr(split2);
		}
		else
			df->t_map->coord[y][x].z = (double)ft_atoi(split[x]);
		// printf("x: %f y: %f z: %f \n", df->t_map->coord[j][i].x, df->t_map->coord[j][i].y, df->t_map->coord[j][i].z);
		//transform_point(&df->t_map->coord[y][x], 0, df); // doesn't make sense to 
		// transform here cos minmax is still  being updated resulting in inconsistent max and min vals
		// update_minmax(df, y, x);
	}
	ft_free_strarr(split);
}

static void	ft_transform_map(t_df *df)
{
	int	y;
	int	x;
	
	y = -1;
	while (++y < df->height)
	{
		x = -1;
		while (++x < df->width)
		{
			transform_point(&df->t_map->coord[y][x], 0, df);
			update_minmax(df, y, x);
			// printf("x: %f y: %f z: %f \n", df->t_map->coord[y][x].x, df->t_map->coord[y][x].y, df->t_map->coord[y][x].z);
		}
	}			
}

static void	ft_update_minmax_with_zoom(t_df *df)
{
	df->zoom = find_min(WIN_WIDTH / (df->t_map->max_x / 2),
	(WIN_HEIGHT / df->t_map->max_y / 2));
	df->t_map->max_x *= df->zoom;
	df->t_map->max_y *= df->zoom;
	df->t_map->min_x *= df->zoom;
	df->t_map->min_y *= df->zoom;
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
	// df->map = malloc_map(df);
	i = 0;
	while (ft_next_line(fd, &line) > 0)
	{
		// ft_fill_map(df, line, i);
		ft_fill_tmap(df, line, i);
		i++;
	}
	ft_transform_map(df);
	ft_update_minmax_with_zoom(df);
	close(fd);
}
