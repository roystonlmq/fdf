/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:06:02 by roylee            #+#    #+#             */
/*   Updated: 2024/01/10 21:22:04 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_next_line(int fd, char **line)
{
	*line = get_next_line(fd);
	if (*line == 0 || **line == 0)
		return (0);
	return (1);
}

static int	ft_splitlen(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}