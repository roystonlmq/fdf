/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:43:30 by roylee            #+#    #+#             */
/*   Updated: 2024/01/09 21:37:21 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_prog	*init_prog(void)
{
	t_prog	*app;

	app = (t_prog *)malloc(sizeof(t_prog));
	if (!app)
		exception(1, "Failed to allocate memory for app");
	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
		exception(1, "Failed to initialise MLX");
	mlx_get_screen_size(app->mlx_ptr, &app->width, &app->height);
	app->mlx_win = mlx_new_window(app->mlx_ptr, app->width, app->height, TITLE);
	if (!app->mlx_win)
		exception(1, "Failed to create new window");
	app->mlx_img = mlx_new_image(app->mlx_ptr, app->width, app->height);
	if (!app->mlx_img)
		exception(1, "Failed to create new image");
	app->mlx_data = mlx_get_data_addr(app->mlx_img, &app->bpp, &app->sz_ln, 
					&app->endian);
	if (!app->mlx_data)
		exception(1, "Failed to get data address");
	app->df = NULL;
	return (app);
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
	df->z_max = 0;
	df->z_min = 0;
	return (df);
}

