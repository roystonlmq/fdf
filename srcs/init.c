/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:43:30 by roylee            #+#    #+#             */
/*   Updated: 2024/01/20 17:45:56 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_prog	*init_prog(void)
{
	t_prog	*app;

	app = (t_prog *)malloc(sizeof(t_prog));
	if (!app)
		exception(1, "Failed to allocate memory for app");
	app->df = NULL;
	return (app);
}

void	init_mlx(t_prog *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		exception(1, "Failed to initialise MLX");
	mlx_get_screen_size(app->mlx, &app->width, &app->height);
	app->img = mlx_new_image(app->mlx, app->width, app->height);
	if (!app->img)
		exception(1, "Failed to create new image");
	app->data = mlx_get_data_addr(app->img, &app->bpp, &app->length, 
			&app->endian);
	if (!app->data)
		exception(1, "Failed to get data address");
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
	while (i < height)
	{
		coords[i] = malloc(width * sizeof(t_point));
		if (!coords[i])
			exception(1, "Failed to allocate memory for coords");
		j = 0;
		while (j < width)
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

t_df	*init_df(void)
{
	t_df	*df;

	df = (t_df *)malloc(sizeof(t_df));
	if (!df)
		exception(1, "Failed to allocate memory for df");
	df->t_map = NULL;
	df->width = 0;
	df->height = 0;
	df->h_view = 10;
	df->h_move = WIN_WIDTH / 2;
	df->v_move = WIN_HEIGHT / 2;
	df->zoom = 1;
	map_init(df);
	return (df);
}
