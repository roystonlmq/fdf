/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:10:10 by sgoffaux          #+#    #+#             */
/*   Updated: 2024/01/20 16:42:02 by roylee           ###   ########.fr       */
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

typedef struct	s_map
{
	t_point **coord;
	double	max_x;
	double	max_y;
	double	min_x;
	double	min_y;
}	t_map;

typedef struct	s_df
{
	int		x;
	int		y;
	int		width;
	int		height;
	double	zoom;
	double	h_view;
	double	h_move;
	double	v_move;
	t_map	*t_map;
}	t_df;

typedef struct	s_prog
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		bpp;
	int		length;
	int		endian;
	t_df	*df;
}	t_prog;

/*
error.c 
*/
void	exception(int errnum, const char *msg);

/*
init.c
*/
t_prog	*init_prog(void);
t_df	*init_df(void);
void	map_init(t_df *df);
t_point	**init_coord(int width, int height);

/*
next_line.c
*/
int	ft_next_line(int fd, char **line);
int	ft_splitlen(char **split);

/*
parser.c
*/
void	parse_df(t_df *df, char *file);

/*
utils.c
*/
void	ft_free_strarr(char **str);
int		find_max(int num1, int num2);
int		find_min(int num1, int num2);
int		find_mod(int num);
double	find_dmin(double num1, double num2);

/*
draw.c
*/
int		fade(int z);
void	transform_point(t_point *p1, t_point *p2, t_df *df);
void	draw_line(t_prog *app, t_point *p1, t_point *p2);
void	draw_loop(t_prog *app, t_df *df);

/*
keys.c
*/
void	key_hook(int keycode, t_prog *prog);
int	ft_close_win(t_prog *prog);

#endif
