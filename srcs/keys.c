/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:07:47 by roylee            #+#    #+#             */
/*   Updated: 2024/01/20 23:27:00 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_coord(t_df *df)
{
	int	i;

	i = -1;
	while (++i < df->height)
		free(df->t_map->coord[i]);
	free(df->t_map->coord);
}

int	ft_close_win(t_prog *prog)
{
	free_coord(prog->df);
	free(prog->df->t_map);
	if (prog->img)
		mlx_destroy_image(prog->mlx, prog->img);
	if (prog->win)
		mlx_destroy_window(prog->mlx, prog->win);
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
	free(prog->df);
	free(prog);
	exit(0);
}

int	key_hook(int keycode, t_prog *prog)
{
	if (keycode == XK_Escape)
		ft_close_win(prog);
	return (0);
}
