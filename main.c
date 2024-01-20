/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:03:39 by roylee            #+#    #+#             */
/*   Updated: 2024/01/20 17:22:53 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	double	minx;
	double	miny;
	double	maxx;
	double	maxy;
	t_prog	*prog;

	if (argc != 2)
		exception(1, "Not enough arguments");
	prog = init_prog();
	prog->df = init_df();
	parse_df(prog->df, argv[1]);
	draw_loop(prog, prog->df);
	minx = prog->df->t_map->min_x;
	miny = prog->df->t_map->min_y;
	maxx = prog->df->t_map->max_x;
	maxy = prog->df->t_map->max_y;
	prog->win = mlx_new_window(prog->mlx, (maxx - minx), (maxy - miny), TITLE);
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img, 0, 0);
	mlx_key_hook(prog->win, &key_hook, prog);
	mlx_hook(prog->win, 17, 1L << 17, &ft_close_win, prog);
	mlx_loop(prog->mlx);
	return (0);
}
