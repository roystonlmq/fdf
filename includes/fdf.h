/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:10:10 by sgoffaux          #+#    #+#             */
/*   Updated: 2024/01/13 14:03:43 by roylee           ###   ########.fr       */
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

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TITLE "FdF"

typedef struct	s_df
{
	float	x_tmp;
	float	y_tmp;
	int		width;
	int		height;
	int		**map;
}	t_df;

typedef struct	s_prog
{
	void	*mlx_ptr;
	int		width;
	int		height;
	void	*mlx_win;
	void	*mlx_img;
	char	*mlx_data;
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
int		ft_abs(int a);

/*
draw.c
*/
void	draw_line(int x, int y, int x1, int y1, t_prog *app);
void	draw(t_df *df, t_prog *app);

#endif