/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:10:10 by sgoffaux          #+#    #+#             */
/*   Updated: 2024/01/10 21:33:05 by roylee           ###   ########.fr       */
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

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
}	t_point;

typedef struct	s_df
{
	int			width;
	int			height;
	int			z_max;
	int			z_min;
	int			***map;
}	t_df;

typedef struct	s_cam
{
	
}	t_cam;
typedef struct	s_prog
{
	void	*mlx_ptr;
	int		width;
	int		height;
	void	*mlx_win;
	void	*mlx_img;
	char	*mlx_data;
	int		bpp;
	int		sz_ln;
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
static int	ft_splitlen(char **split);

/*
parser.c
*/
void	parse_df(t_df *df, char *file);
static int	ft_get_width(char *file);
static int	ft_get_height(char *file);



#endif