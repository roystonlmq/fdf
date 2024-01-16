/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:54:51 by decortejohn       #+#    #+#             */
/*   Updated: 2024/01/16 22:06:51 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fade(int h)
{
	if (h > 100)
		return (0xFFDF8D);
	if (h > 75)
		return (0xFFDE7A);
	if (h > 50)
		return (0xFFC568);
	if (h > 25)
		return (0xFD996B);
	if (h > 15)
		return (0xF7856C);
	if (h > 10)
		return (0xF06E6C);
	if (h > 5)
		return (0xD9576B);
	if (h > 0)
		return (0xA44369);
	if (h > -10)
		return (0x833F68);
	if (h > -20)
		return (0x833F68);
	if (h > -50)
		return (0x5E3C65);
	return (0x3F3A63);
}

/*
transform_point:

Takes a point of coord(x, y, z) and transforms into a new point 
of coord(x, y) using isometric projection 
*/
void	transform_point(t_point *p, t_df *df)
{
	int	previous_x;
	int	previous_y;

	previous_x = p->x * df->zoom;
	previous_y = p->y * df->zoom;
	p->x = (previous_x - previous_y) * cos(0.523599) + df->h_move;
	p->y = -p->z + (previous_x + previous_y) * sin(0.523599) + df->v_move;
}

void	ft_put_pixel(t_prog *app, int x, int y, int color)
{
	int		i;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	i = (x * app->bpp / 8) + (y * app->length);
	app->data[i] = color;
	app->data[++i] = color >> 8;
	app->data[++i] = color >> 16;
}

void	draw_line(t_prog *app, t_point p1, t_point p2, int color)
{
	double	deltaX;
	double	deltaY;
	int		pixels;
	double	pixelX;
	double	pixelY;
	
	transform_point(&p1, app->df);
	transform_point(&p2, app->df);
	deltaX = p2.x - p1.x;
	deltaY = p2.y - p1.y;
	pixels = sqrt(deltaX * deltaX + deltaY * deltaY);
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = p1.x;
	pixelY = p1.y;
	printf("%f %f \n ", pixelX, pixelY);
	while (pixels)
	{
		ft_put_pixel(app, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		pixels--;
	}
}

void	draw_loop(t_prog *app, t_df *df)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;

	// ft_bzero(app->data, WIN_WIDTH * WIN_HEIGHT * (app->bpp / 8));
	y = 0;
	while (y < df->height)
	{
		x = 0;
		while (x < df->width)
		{
			p1.x = x * df->zoom + df->h_move;
			p1.y = y * df->zoom + df->v_move;
			p1.z = df->map[y][x] * df->h_view;
			p1.color = fade(p1.z);
			if (x < df->width - 1)
			{
				p2.x = (x + 1) * df->zoom + df->h_move;
				p2.y = y * df->zoom + df->v_move;
				p2.z = df->map[y][x + 1] * df->h_view;
				p2.color = fade(p2.z);
				draw_line(app, p1, p2, p1.color);
			}
			if (y < df->height - 1)
			{
				p2.x = x * df->zoom + df->h_move;
				p2.y = (y + 1) * df->zoom + df->v_move;
				p2.z = df->map[y + 1][x] * df->h_view;
				p2.color = fade(p2.z);
				draw_line(app, p1, p2, p1.color);
			}
			x++;
		}
		y++;
	}
	// mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
}

