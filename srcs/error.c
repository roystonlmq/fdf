/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:30:51 by roylee            #+#    #+#             */
/*   Updated: 2024/01/20 17:46:53 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exception(int errnum, const char *msg)
{
	int	errno;

	errno = errnum;
	perror(msg);
	exit(EXIT_FAILURE);
}
