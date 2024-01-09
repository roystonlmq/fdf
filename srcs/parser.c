/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:37:59 by roylee            #+#    #+#             */
/*   Updated: 2024/01/09 21:38:43 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	parse_df(t_df *df, char *file)
{
	int		fd;
	char	*line;
	char	**split;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exception(1, "Failed to open file");
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		if (i == 0)
			df->width = ft_splitlen(split);
		else if (df->width != ft_splitlen(split))
			exception(1, "Found wrong line length. Exiting.");
		df->height++;
		i++;
	}
	close(fd);
}