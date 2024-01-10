/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:44:46 by roylee            #+#    #+#             */
/*   Updated: 2023/09/10 20:54:43 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	nbr;

	nbr = n;
	if (nbr == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (nbr < 0)
	{
		ft_putstr_fd("-", fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}

/*
int	main(void)
{
	int	test = -2147483647;
	ft_putnbr_fd(test, 1);
}
*/
