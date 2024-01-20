/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:10:10 by sgoffaux          #+#    #+#             */
/*   Updated: 2024/01/20 23:54:03 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TITLE "fdf"

# define ESC 53

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

typedef struct s_map
{
	t_point	**coord;
	double	max_x;
	double	max_y;
	double	min_x;
	double	min_y;
}	t_map;

typedef struct s_df
{
	double	zoom;
	double	h_view;
	double	h_move;
	double	v_move;
	t_map	*t_map;
	int		x;
	int		y;
	int		width;
	int		height;
}	t_df;

typedef struct s_prog
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		length;
	int		endian;
	t_df	*df;
}	t_prog;

/*
error.c
*/
void	exception(int errnum, const char *msg);
int		check_fdf(t_prog *prog, char *file);

/*
init.c
*/
t_prog	*init_prog(void);
t_df	*init_df(void);
void	map_init(t_df *df);
t_point	**init_coord(int width, int height);
void	init_mlx(t_prog *prog);

/*
next_line.c
*/
int		ft_next_line(int fd, char **line);
int		ft_splitlen(char **split);

/*
parser.c
*/
void	parse_df(t_prog *df, char *file);

/*
utils.c
*/
void	ft_free_strarr(char **str);
int		find_max(int num1, int num2);
int		find_min(int num1, int num2);
int		find_mod(int num);

/*
project.c
*/
void	transform_point(t_point *p1, t_point *p2);\
void	ft_update_minmax_with_zoom(t_df *df);
void	ft_transform_map(t_df *df);

/*
draw.c
*/
int		fade(int z);

void	draw_line(t_prog *app, t_point *p1, t_point *p2);
void	draw_loop(t_prog *app, t_df *df);

/*
keys.c
*/
int		key_hook(int keycode, t_prog *prog);
int		ft_close_win(t_prog *prog);

#endif
