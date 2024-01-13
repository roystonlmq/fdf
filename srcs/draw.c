/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:34:33 by roylee            #+#    #+#             */
/*   Updated: 2024/01/13 14:03:24 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fade(int h)
{
	if (h > 100)
		return (0x00FF40);
	if (h > 75)
		return (0x12FF4E);
	if (h > 50)
		return (0x2EFF63);
	if (h > 25)
		return (0x4CFF79);
	if (h > 15)
		return (0x61FF89);
	if (h > 10)
		return (0x7BFF9C);
	if (h > 5)
		return (0x82DD99);
	if (h > 0)
		return (0x66B479);
	if (h > -10)
		return (0x4A7C57);
	if (h > -20)
		return (0x6F8775);
	if (h > -50)
		return (0x8B9D8F);
	return (0xAED6B6);
}

void	pixel_put(t_prog *app, int x, int y, int color)
{
	int	i;

	i = (y * app->length + x * (app->bpp / 8));

	app->mlx_data[i] = color;
	app->mlx_data[++i] = color >> 8;
	app->mlx_data[++i] = color >> 16;
}

void	isometric_projection(t_df *df)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	while (i < df->height)
	{
		j = 0;
		while (j < df->width)
		{
			x = (j - i) * cos(0.523599);
			y = (j + i) * sin(0.523599) - df->map[i][j];
			df->map[i][j] = x;
			df->map[i][j + 1] = y;
			j += 2;
		}
		i++;
	}
}
void	draw_line(int x, int y, int x1, int y1, t_prog *app)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	dx = abs(x1 - x);
	dy = abs(y1 - y);
	sx = x < x1 ? 1 : -1;
	sy = y < y1 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		pixel_put(app, x, y, fade(y1 - y));
		if (x == x1 && y == y1)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y += sy;
		}
	}
}

void	draw(t_df *df, t_prog *app)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	while (i < df->height)
	{
		j = 0;
		while (j < df->width)
		{
			x = df->map[i][j];
			y = df->map[i][j + 1];
			if (j + 2 < df->width)
				draw_line(x, y, df->map[i][j + 2], df->map[i][j + 3], app);
			if (i + 1 < df->height)
				draw_line(x, y, df->map[i + 1][j], df->map[i + 1][j + 1], app);
			j += 2;
		}
		i++;
	}
}
