/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:30:51 by roylee            #+#    #+#             */
/*   Updated: 2024/01/20 23:53:19 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
check_fdf:

Validation:
- file is of .fdf extension
- file is not empty
- file exists

Returns (fd)
*/
int	check_fdf(t_prog *prog, char *file)
{
	int	strlen;
	int	fd;

	strlen = ft_strlen(file);
	if (ft_strncmp(&file[strlen - 4], ".fdf", 4) != 0)
		return (-1);
	if (ft_strlen(file) == 0)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(prog->df->t_map);
		free(prog->df);
		free(prog);
		exception(1, "Failed to open file");
	}
	return (fd);
}

void	exception(int errnum, const char *msg)
{
	int	errno;

	errno = errnum;
	perror(msg);
	exit(EXIT_FAILURE);
}
