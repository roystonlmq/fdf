/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:04:05 by roylee            #+#    #+#             */
/*   Updated: 2024/01/20 17:15:49 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	ft_transform_map(t_df *df)
{
	int	y;
	int	x;

	y = -1;
	while (++y < df->height)
	{
		x = -1;
		while (++x < df->width)
		{
			transform_point(&df->t_map->coord[y][x], 0);
			update_minmax(df, y, x);
		}
	}
}

/*
transform_point:

Takes a point of coord(x, y, z) and transforms into a new point 
of coord(x, y) using isometric projection 
*/
void	transform_point(t_point *p1, t_point *p2)
{
	int	previous_x1;
	int	previous_y1;
	int	previous_x2;
	int	previous_y2;

	if (p1)
	{
		previous_x1 = p1->x;
		previous_y1 = p1->y;
		p1->x = (previous_x1 - previous_y1) * cos(0.523599);
		p1->y = -p1->z + (previous_x1 + previous_y1) * sin(0.523599);
	}
	if (p2)
	{
		previous_x2 = p2->x;
		previous_y2 = p2->y;
		p2->x = (previous_x2 - previous_y2) * cos(0.523599);
		p2->y = -p2->z + (previous_x2 + previous_y2) * sin(0.523599);
	}
}
