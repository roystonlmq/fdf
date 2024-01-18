/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:54:51 by decortejohn       #+#    #+#             */
/*   Updated: 2024/01/18 22:39:11 by roylee           ###   ########.fr       */
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
void	transform_point(t_point *p1, t_point *p2, t_df *df)
{
	int		previous_x1;
	int		previous_y1;
	int		previous_x2;
	int		previous_y2;

	if (p1)
	{
		previous_x1 = p1->x;
		previous_y1 = p1->y;
		p1->x = (previous_x1 - previous_y1) * cos(0.523599) + find_mod(df->t_map->min_x);
		p1->y = -p1->z + (previous_x1 + previous_y1) * sin(0.523599) + find_mod(df->t_map->min_y);
		// printf("p1: %f %f \n", p1->x, p1->y);
	}
	if (p2)
	{
		previous_x2 = p2->x;
		previous_y2 = p2->y;
		p2->x = (previous_x2 - previous_y2) * cos(0.523599) + find_mod(df->t_map->min_x);
		// printf("p2: %f %f \n", p2->x, p2->y);
		p2->y = -p2->z + (previous_x2 + previous_y2) * sin(0.523599) + find_mod(df->t_map->min_y);
	}
	// printf("%f %f \n ", p1->x, p1->y);
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

void	draw_line(t_prog *app, t_point *p1, t_point *p2)
{
	double	deltaX;
	double	deltaY;
	int		pixels;
	double	pixelX;
	double	pixelY;
	
	// transform_point(&p1, &p2, app->df);
	deltaX = p2->x - p1->x;
	deltaY = p2->y - p1->y;
	pixels = sqrt(deltaX * deltaX + deltaY * deltaY);
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = p1->x;
	pixelY = p1->y;
	// printf("%f %f \n ", pixelX, pixelY);
	while (pixels)
	{
		ft_put_pixel(app, pixelX, pixelY, fade(find_max(p1->z, p2->z)));
		pixelX += deltaX;
		pixelY += deltaY;
		pixels--;
	}
}

// Old draw_loop that uses old map
// void	draw_loop(t_prog *app, t_df *df)
// {
// 	t_point	p1;
// 	t_point	p2;

// 	df->y = 0;
// 	while (df->y < df->height)
// 	{
// 		df->x = 0;
// 		while (df->x < df->width)
// 		{
// 			p1.x = df->x * df->zoom + df->h_move;
// 			p1.y = df->y * df->zoom + df->v_move;
// 			p1.z = df->map[df->y][df->x] * df->h_view;
// 			if (df->x < df->width - 1)
// 			{
// 				p2.x = (df->x + 1) * df->zoom + df->h_move;
// 				p2.y = df->y * df->zoom + df->v_move;
// 				p2.z = df->map[df->y][df->x + 1] * df->h_view;
// 				draw_line(app, p1, p2);
// 			}
// 			if (df->y < df->height - 1)
// 			{
// 				p2.x = df->x * df->zoom + df->h_move;
// 				p2.y = (df->y + 1) * df->zoom + df->v_move;
// 				p2.z = df->map[df->y + 1][df->x] * df->h_view;
// 				draw_line(app, p1, p2);
// 			}
// 			df->x++;
// 		}
// 		df->y++;
// 	}
// }

void	draw_loop(t_prog *app, t_df *df)
{
	t_point	*p1;
	t_point	*p2;

	p1 = (t_point *)malloc(sizeof(t_point));
	p2 = (t_point *)malloc(sizeof(t_point));
	if (!p1 || !p2)
		exception(1, "Failed to allocate memory for points");

	df->y = 0;
	while (df->y < df->height)
	{
		df->x = 0;
		while (df->x < df->width)
		{
			p1->x = df->t_map->coord[df->y][df->x].x * df->zoom + find_mod(df->t_map->min_x);
			p1->y = df->t_map->coord[df->y][df->x].y * df->zoom + find_mod(df->t_map->min_y);
			p1->z = df->t_map->coord[df->y][df->x].z * df->h_view;
			// printf("p1: %f %f %f \n", p1->x, p1->y, p1->z);
			if (df->x < df->width - 1)
			{
				p2->x = df->t_map->coord[df->y][df->x + 1].x * df->zoom + find_mod(df->t_map->min_x);
				p2->y = df->t_map->coord[df->y][df->x + 1].y * df->zoom + find_mod(df->t_map->min_y);
				p2->z = df->t_map->coord[df->y][df->x + 1].z * df->h_view;
				draw_line(app, p1, p2);
			}
			if (df->y < df->height - 1)
			{
				p2->x = df->t_map->coord[df->y + 1][df->x].x * df->zoom + find_mod(df->t_map->min_x);
				p2->y = df->t_map->coord[df->y + 1][df->x].y * df->zoom + find_mod(df->t_map->min_y);
				p2->z = df->t_map->coord[df->y + 1][df->x].z * df->h_view;
				draw_line(app, p1, p2);
			}
			df->x++;
		}
		df->y++;
	}
	free(p1);
	free(p2);
}