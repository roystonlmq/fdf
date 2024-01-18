/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:43:30 by roylee            #+#    #+#             */
/*   Updated: 2024/01/18 20:13:49 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_prog	*init_prog(void)
{
	t_prog	*app;

	app = (t_prog *)malloc(sizeof(t_prog));
	if (!app)
		exception(1, "Failed to allocate memory for app");
	app->mlx = mlx_init();
	if (!app->mlx)
		exception(1, "Failed to initialise MLX");
	mlx_get_screen_size(app->mlx, &app->width, &app->height);
	app->win = mlx_new_window(app->mlx, app->width, app->height, TITLE);
	if (!app->win)
		exception(1, "Failed to create new window");
	app->img = mlx_new_image(app->mlx, app->width, app->height);
	if (!app->img)
		exception(1, "Failed to create new image");
	app->data = mlx_get_data_addr(app->img, &app->bpp, &app->length, 
					&app->endian);
	if (!app->data)
		exception(1, "Failed to get data address");
	app->df = NULL;
	return (app);
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

t_df	*init_df(void)
{
	t_df	*df;

	df = (t_df *)malloc(sizeof(t_df));
	if (!df)
		exception(1, "Failed to allocate memory for df");
	df->map = NULL;
	df->width = 0;
	df->height = 0;
	map_init(df);
	return (df);
}

